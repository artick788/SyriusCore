#include "D3D11Texture2D.hpp"

#if defined(SR_CORE_PLATFORM_WIN64)

namespace Syrius{

    D3D11Texture2D::D3D11Texture2D(const Texture2DDesc &desc, const Resource<DeviceLimits>& deviceLimits, ID3D11Device *device, ID3D11DeviceContext *context):
    Texture2D(desc, deviceLimits),
    m_Device(device),
    m_Context(context),
    m_Texture(nullptr),
    m_TextureView(nullptr){
        createResources(desc.data);
    }

    D3D11Texture2D::D3D11Texture2D(const Texture2DImageDesc &desc, const Resource<DeviceLimits>& deviceLimits, ID3D11Device *device, ID3D11DeviceContext *context):
    Texture2D(desc, deviceLimits),
    m_Device(device),
    m_Context(context),
    m_Texture(nullptr),
    m_TextureView(nullptr){
        createResources(desc.image->getData());
    }

    D3D11Texture2D::~D3D11Texture2D() {
        if (m_TextureView) {
            m_TextureView->Release();
        }
        if (m_Texture) {
            m_Texture->Release();
        }

    }

    void D3D11Texture2D::bind() {
        // D3D11 doesn't have a bind function
    }

    void D3D11Texture2D::bindShaderResource(uint32_t slot) {
        SR_CORE_PRECONDITION(slot < m_DeviceLimits->getMaxTextureSlots(), "[Texture2D]: Supplied slot (%i) is greater than the device number of texture slots (%i)", slot, m_DeviceLimits->getMaxTextureSlots());

        m_Context->PSSetShaderResources(slot, 1, &m_TextureView);
    }

    void D3D11Texture2D::unbind() {

    }

    void D3D11Texture2D::setData(const void *data, uint32 x, uint32 y, uint32 width, uint32 height) {
        // TODO: Test this code because dont know if it works
        auto channelCount = getTextureChannelCount(m_Format);
        D3D11_BOX box = { 0 };
        box.left = x;
        box.right = x + width;
        box.top = y;
        box.bottom = y + height;
        box.front = 0;
        box.back = 1;

        m_Context->UpdateSubresource(m_Texture, 0, &box, data, width * (sizeof(ubyte) * channelCount), 0);
    }

    Resource<Image> D3D11Texture2D::getData() {
        // we use a staging texture to copy the data back to the CPU as a texture cannot be mapped
        D3D11_TEXTURE2D_DESC desc;
        m_Texture->GetDesc(&desc);
        desc.Usage = D3D11_USAGE_STAGING;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        desc.BindFlags = 0;
        desc.MiscFlags = 0;
        ID3D11Texture2D* stagingTexture = nullptr;
        SR_CORE_D3D11_CALL(m_Device->CreateTexture2D(&desc, nullptr, &stagingTexture));

        m_Context->CopyResource(stagingTexture, m_Texture);

        D3D11_MAPPED_SUBRESOURCE mappedResource;
        SR_CORE_D3D11_CALL(m_Context->Map(stagingTexture, 0, D3D11_MAP_READ, 0, &mappedResource));

        BYTE* data = static_cast<BYTE*>(mappedResource.pData);
        ImageUI8Desc imgDesc;
        imgDesc.width = desc.Width;
        imgDesc.height = desc.Height;
        imgDesc.format = m_Format;
        imgDesc.data = data;
        auto img = createImageUI8(imgDesc);
        m_Context->Unmap(stagingTexture, 0);
        stagingTexture->Release();
        return std::move(img);
    }

    uint64 D3D11Texture2D::getIdentifier() const {
        return reinterpret_cast<uint64>(m_Texture);
    }

    void D3D11Texture2D::createResources(const void *data) {

        D3D11_TEXTURE2D_DESC textureDesc = { 0 };
        textureDesc.Width = m_Width;
        textureDesc.Height = m_Height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = getD3d11TextureFormat(m_Format);
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        auto dataType = getTextureDataType(m_Format);
        auto channelCount = getTextureChannelCount(m_Format);

        if (channelCount == 3){
            SR_CORE_EXCEPTION("Supplied texture format has 3 channels which is not supported by D3D11");
        }

        D3D11_SUBRESOURCE_DATA subresourceData = { 0 };
        subresourceData.SysMemPitch = m_Width * (getTypeSize(dataType) * channelCount);
        subresourceData.pSysMem = data;

        SR_CORE_D3D11_CALL(m_Device->CreateTexture2D(&textureDesc, &subresourceData, &m_Texture));

        D3D11_SHADER_RESOURCE_VIEW_DESC textureViewDesc = {  };
        textureViewDesc.Format = textureDesc.Format;
        textureViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        textureViewDesc.Texture2D.MipLevels = 1;
        textureViewDesc.Texture2D.MostDetailedMip = 0;

        SR_CORE_D3D11_CALL(m_Device->CreateShaderResourceView(m_Texture, &textureViewDesc, &m_TextureView));
    }


}

#endif
