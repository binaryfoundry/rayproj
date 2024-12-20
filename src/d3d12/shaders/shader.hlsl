struct Payload
{
    float3 color;
    bool allowReflection;
    bool missed;
};

cbuffer Uniforms : register(b0)
{
    float4 Position;
    float TMin;
    float TMax;
    float Aspect;
    float Zoom;
    float4 Padding1;
    float4 Padding2;
    matrix View;
    matrix Padding4;
    matrix Padding5;
};

RaytracingAccelerationStructure scene : register(t0);

RWTexture2D<float4> uav : register(u0);

static const float3 light = float3(0, 200, 200);
static const float3 skyTop = float3(0.24, 0.44, 0.72);
static const float3 skyBottom = float3(0.75, 0.86, 0.93);

float3 Ray_screen(float2 coords) {
    coords = float2(coords.x, 1.0 - coords.y);

    float size = 1.0 / Zoom;

    float4 h = float4(size * 2.0, 0.0, 0.0, 1.0);
    float4 v = float4(0.0, size * 2.0 * Aspect, 0.0, 1.0);
    float4 c = float4(-size, -size * Aspect, -1.5, 1.0);

    h = mul(h, View);
    v = mul(v, View);
    c = mul(c, View);

    float3 direction = normalize(
        (c + coords.x * h + coords.y * v).xyz);

    return direction;
}


[shader("raygeneration")]
void RayGeneration()
{
    float3 origin = Position.xyz;

    uint2 idx = DispatchRaysIndex().xy;
    float2 size = DispatchRaysDimensions().xy;

    float2 uv = idx / size;

    RayDesc ray;
    ray.Origin = origin;
    ray.Direction = Ray_screen(uv);
    ray.TMin = TMin; // 0.001;
    ray.TMax = TMax; // 1000;

    Payload payload;
    payload.allowReflection = true;
    payload.missed = false;

    TraceRay(scene, RAY_FLAG_NONE, 0xFF, 0, 0, 0, ray, payload);

    uav[idx] = float4(payload.color, 1);
}

[shader("miss")]
void Miss(inout Payload payload)
{

    float slope = normalize(WorldRayDirection()).y;
    float t = saturate(slope * 5 + 0.5);
    payload.color = lerp(skyBottom, skyTop, t);

    payload.missed = true;
}

void HitCube(inout Payload payload, float2 uv);
void HitMirror(inout Payload payload, float2 uv);
void HitFloor(inout Payload payload, float2 uv);

[shader("closesthit")]
void ClosestHit(inout Payload payload,
                BuiltInTriangleIntersectionAttributes attrib)
{

    switch (InstanceID())
    {
        case 0: HitFloor(payload, attrib.barycentrics); break;
        case 1: HitCube(payload, attrib.barycentrics); break;
        case 2: HitMirror(payload, attrib.barycentrics); break;

        default: payload.color = float3(1, 0, 1); break;
    }
}

void HitCube(inout Payload payload, float2 uv)
{
    uint tri = PrimitiveIndex();

    tri /= 2;
    float3 normal = (tri.xxx % 3 == uint3(0, 1, 2)) * (tri < 3 ? -1 : 1);

    float3 worldNormal = normalize(mul(normal, (float3x3)ObjectToWorld4x3()));

    float3 color = float3(1, 1, 1);

    color *= saturate(dot(worldNormal, normalize(light))) + 0.33;
    payload.color = color;
}

void HitMirror(inout Payload payload, float2 uv)
{
    if (!payload.allowReflection)
        return;

    float3 pos = WorldRayOrigin() + WorldRayDirection() * RayTCurrent();
    float3 normal = normalize(mul(float3(0, 1, 0), (float3x3)ObjectToWorld4x3()));
    float3 reflected = reflect(normalize(WorldRayDirection()), normal);

    RayDesc mirrorRay;
    mirrorRay.Origin = pos;
    mirrorRay.Direction = reflected;
    mirrorRay.TMin = 0.001;
    mirrorRay.TMax = 1000;

    payload.allowReflection=false;
    TraceRay(scene, RAY_FLAG_NONE, 0xFF, 0, 0, 0, mirrorRay, payload);

}

void HitFloor(inout Payload payload, float2 uv)
{
    float3 pos = WorldRayOrigin() + WorldRayDirection() * RayTCurrent();

    bool2 pattern = frac(pos.xz) > 0.5;
    payload.color = pattern.x ^ pattern.y ? 0.6.xxx : 0.4.xxx;

    RayDesc shadowRay;
    shadowRay.Origin = pos;
    shadowRay.Direction = light - pos;
    shadowRay.TMin = 0.001;
    shadowRay.TMax = 1;

    Payload shadow;
    shadow.allowReflection = false;
    shadow.missed = false;
    TraceRay(scene, RAY_FLAG_NONE, 0xFF, 0, 0, 0, shadowRay, shadow);

    if (!shadow.missed)
        payload.color /= 2;
}
