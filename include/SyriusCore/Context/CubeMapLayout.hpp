#pragma once

#include <array>
#include "Utils.hpp"
#include "../Image/ImageFactory.hpp"
#include "DeviceLimits.hpp"

namespace Syrius{

    class SR_CORE_API CubeMapLayout{
    public:
        CubeMapLayout() = delete;

        CubeMapLayout(uint32 width, uint32 height, SR_TEXTURE_FORMAT format, const Resource<DeviceLimits>& deviceLimits);

        ~CubeMapLayout();

        void addFace(SR_CUBEMAP_FACE faceID, Resource<Image>& image);

        void addFaceFromFile(SR_CUBEMAP_FACE faceID, const ImageFileDesc& desc);

        [[nodiscard]] uint32 getWidth() const;

        [[nodiscard]] uint32 getHeight() const;

        [[nodiscard]] SR_TEXTURE_FORMAT getFormat() const;

        [[nodiscard]] const Resource<Image>& getFace(SR_CUBEMAP_FACE faceID) const;

        [[nodiscard]] const std::array<Resource<Image>, 6>& getFaces() const;

    protected:
        const Resource<DeviceLimits>& m_DeviceLimits;

        const uint32 m_Width;
        const uint32 m_Height;
        const SR_TEXTURE_FORMAT m_Format;

        std::array<Resource<Image>, 6> m_Faces;
    };
}
