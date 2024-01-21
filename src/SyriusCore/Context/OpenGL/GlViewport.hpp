#pragma once

#include "../../../../include/SyriusCore/Context/Viewport.hpp"
#include "GlUtils.hpp"

namespace Syrius{

    class GlViewport : public Viewport{
    public:
        GlViewport(const ViewportDesc& desc, const Resource<DeviceLimits>& deviceLimits);

        ~GlViewport() override;

        void bind() override;
    };

}