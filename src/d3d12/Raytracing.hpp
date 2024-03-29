#pragma once

#include <array>
#include <memory>

#include "Context.hpp"
#include "Constants.hpp"

#include <DirectXMath.h>

namespace d3d12
{
    struct RaytracingUniforms
    {
        DirectX::XMMATRIX Transform;
        DirectX::XMMATRIX Scale;
        DirectX::XMMATRIX Padding1;
        DirectX::XMMATRIX Padding2;
    };

    class Raytracing
    {
    public:
        Raytracing(
            std::shared_ptr<d3d12::Context> context);
        virtual ~Raytracing();

        void Initialize();

        void Render();
        void Resize();

        void MoveToNextFrame();

    private:
        std::shared_ptr<d3d12::Context> context;

        struct CurrentFrameResources
        {
            ConstantBufferPool<RaytracingUniforms> constant_pool;
            ComPtr<ID3D12Resource> tlas_update_scratch;
        };

        std::array<CurrentFrameResources, FRAME_COUNT> frame_resources;

        CurrentFrameResources& FrameResources()
        {
            return frame_resources[context->frame_index];
        }

        D3D12_RAYTRACING_INSTANCE_DESC* instance_data = nullptr;
        ComPtr<ID3D12DescriptorHeap> uav_heap;
        ComPtr<ID3D12Resource> render_target;
        ComPtr<ID3D12Resource> instances;
        ComPtr<ID3D12Resource> tlas;

        ID3D12Resource* quad_blas = nullptr;
        ID3D12Resource* cube_blas = nullptr;

        ID3D12Resource* quad_vb = nullptr;
        ID3D12Resource* cube_vb = nullptr;
        ID3D12Resource* cube_ib = nullptr;

        ID3D12RootSignature* root_signature = nullptr;
        ID3D12StateObject* pso = nullptr;
        ID3D12Resource* shader_ids = nullptr;

        void InitMeshes();
        void InitBottomLevel();
        void InitScene();
        void InitTopLevel();
        void InitRootSignature();
        void InitPipeline();

        void Flush();

        void UpdateTransforms();
        void UpdateScene();

        ID3D12Resource* MakeAccelerationStructure(
            const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS& inputs,
            UINT64* update_scratch_size = nullptr);

        ID3D12Resource* MakeBLAS(
            ID3D12Resource* vertex_buffer,
            UINT vertex_floats,
            ID3D12Resource* index_buffer = nullptr,
            UINT indices = 0);

        ID3D12Resource* MakeTLAS(
            ID3D12Resource* instances,
            UINT num_instances,
            UINT64* update_scratch_size);
    };
}
