#pragma once

#include "../Context.hpp"
#include "../Constants.hpp"
#include "../Allocator.hpp"

#include "BottomStructure.hpp"

#include <vector>
#include <memory>
#include <DirectXMath.h>

namespace d3d12
{
namespace raytracing
{
    struct RaytracingUniforms
    {
        DirectX::XMMATRIX Transform;
        DirectX::XMMATRIX Scale;
        DirectX::XMMATRIX Padding1;
        DirectX::XMMATRIX Padding2;
    };

    struct CurrentFrameResources
    {
        ConstantBufferPool<RaytracingUniforms> constant_pool;
        ComPtr<ID3D12Resource> tlas_update_scratch;
    };

    class TopStructure
    {
    private:
        std::shared_ptr<d3d12::Context> context;

        std::array<CurrentFrameResources, FRAME_COUNT> frame_resources;

        CurrentFrameResources& FrameResources()
        {
            return frame_resources[context->frame_index];
        }

        std::vector<std::shared_ptr<BottomStructure>> instance_list;
        ComPtr<ID3D12Resource> instances;
        D3D12_RAYTRACING_INSTANCE_DESC* instance_data = nullptr;

        D3D12MA::ResourcePtr tlas;

        void UpdateTransforms();

    public:
        TopStructure(
            std::shared_ptr<d3d12::Context> context,
            const std::vector<std::shared_ptr<BottomStructure>>& instance_list);
        virtual ~TopStructure();

        void Initialize();

        void Update();
        void Render(
            ComPtr<ID3D12DescriptorHeap>& uav_heap,
            const D3D12_DISPATCH_RAYS_DESC& dispatch_desc);

        void MoveToNextFrame();

        D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress();
    };
}
}