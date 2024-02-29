#pragma once

#include <vector>

#include "Allocator.hpp"
#include "Descriptor.hpp"

#include <d3d12.h>
#include <dxgi1_4.h>

#include <wrl.h>

using Microsoft::WRL::ComPtr;

namespace d3d12
{
    static const UINT RENDERER_FRAME_COUNT = 3;
    static const UINT FRAME_COUNT = RENDERER_FRAME_COUNT;

    struct Frame
    {
        ComPtr<ID3D12CommandAllocator> command_allocator;

        ComPtr<ID3D12Resource> render_target;
        DescriptorHandle rtv_handle;

        std::vector<D3D12MA::ResourcePtr> resources_to_release;
        std::vector<DescriptorHandle> handles_to_release;

        UINT64 fence_value = 0;
    };
}
