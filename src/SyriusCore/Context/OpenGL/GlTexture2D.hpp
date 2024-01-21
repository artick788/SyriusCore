#pragma once

#include "../../../../include/SyriusCore/Context/Texture2D.hpp"
#include "GlUtils.hpp"

namespace Syrius{

    class GlTexture2D : public Texture2D{
    public:
        GlTexture2D(const Texture2DDesc& desc, const Resource<DeviceLimits>& deviceLimits);

        GlTexture2D(const Texture2DImageDesc& desc, const Resource<DeviceLimits>& deviceLimits);

        ~GlTexture2D() override;

        void bind(uint32_t slot) override;

        void unbind() override;

        void setData(const void* data, uint32 x, uint32 y, uint32 width, uint32 height) override;

        Resource<Image> getData() override;

        [[nodiscard]] uint64 getIdentifier() const override;

    private:

        void createTexture(const void* data);

        void setGlFormats();

    private:
        uint32 m_TextureID;

        GLenum m_GlFormat;
        GLint m_GlInternalFormat;
        GLenum m_GlDataType;
    };
}

