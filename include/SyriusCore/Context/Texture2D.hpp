#pragma once

#include "../Utils/Image.hpp"
#include "Utils.hpp"
#include "Sampler.hpp"

namespace Syrius{

    struct SR_CORE_API Texture2DDesc{
        uint32 m_Width          = 0;
        uint32 m_Height         = 0;
        Sampler* m_Sampler      = nullptr;
        SR_TEXTURE_DATA_FORMAT m_Format = SR_TEXTURE_DATA_FORMAT_RGBA_UI8;
        const void* m_Data            = nullptr;

    };

    struct SR_CORE_API Texture2DImageDesc{
        Image* m_Image         = nullptr;
        Sampler* m_Sampler     = nullptr;
    };

    class SR_CORE_API Texture2D{
    public:
        explicit Texture2D(const Texture2DDesc& desc);

        explicit Texture2D(const Texture2DImageDesc& desc);

        virtual ~Texture2D();

        virtual void bind(uint32_t slot) = 0;

        virtual void unbind() = 0;

        virtual void setData(const void* data, uint32 x, uint32 y, uint32 width, uint32 height) = 0;

        inline void setData(Image* img, uint32 x, uint32 y, uint32 width, uint32 height){
            auto* data = reinterpret_cast<const void*>(img->getData().data());
            setData(data, x, y, width, height);
        }

        [[nodiscard]] virtual uint64 getIdentifier() const = 0;

        [[nodiscard]] uint32 getWidth() const;

        [[nodiscard]] uint32 getHeight() const;

        [[nodiscard]] SR_TEXTURE_DATA_FORMAT getFormat() const;

    protected:
        uint32 m_Width;
        uint32 m_Height;
        SR_TEXTURE_DATA_FORMAT m_Format;

    };

}

