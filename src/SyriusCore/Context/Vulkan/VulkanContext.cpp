#include "VulkanContext.hpp"

namespace Syrius{

    VulkanContext::VulkanContext(const ContextDesc& desc)
    : Context(desc),
    m_Surface(nullptr),
    m_Instance(nullptr),
    m_PhysicalDevice(nullptr),
    m_Device(nullptr){
        CoreCommand::initVulkan();

        m_Instance = CoreCommand::getVulkanInstance()->getInstance();

    }

    VulkanContext::~VulkanContext() {
        if (m_Surface != nullptr){
            vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        }

        delete m_SwapChain;
        delete m_Device;
        delete m_PhysicalDevice;

        CoreCommand::terminateVulkan();
    }

    void VulkanContext::createDevicesAndSwapChain() {
        /// ALWAYS CALL THIS FUNCTION IN THE CONSTRUCTOR OF THE CHILD CLASS

        m_PhysicalDevice = new VulkanPhysicalDevice(m_Instance, m_Surface);
        m_Device = new VulkanLogicalDevice(m_PhysicalDevice, m_Surface);
        m_SwapChain = new VulkanSwapChain(m_PhysicalDevice, m_Device, m_Surface, getFramebufferSize());
    }

    std::string VulkanContext::getAPIVersion() {
        return std::to_string(m_PhysicalDevice->getDeviceProperties().apiVersion);
    }

    std::string VulkanContext::getDeviceName() {
        return m_PhysicalDevice->getDeviceProperties().deviceName;
    }

    std::string VulkanContext::getShadingLanguageVersion() {
        return {};
    }

    int32 VulkanContext::getMaxFramebufferWidth() {
        return m_PhysicalDevice->getDeviceProperties().limits.maxFramebufferWidth;
    }

    int32 VulkanContext::getMaxFramebufferHeight() {
        return m_PhysicalDevice->getDeviceProperties().limits.maxFramebufferHeight;
    }

    int32 VulkanContext::getMaxFramebufferTextureAttachments() {
        return m_PhysicalDevice->getDeviceProperties().limits.maxColorAttachments;
    }

    int32 VulkanContext::getMaxTextureSlots() {
        return m_PhysicalDevice->getDeviceProperties().limits.maxPerStageDescriptorSampledImages;
    }

    int32 VulkanContext::getMaxTexture2DSize() {
        return m_PhysicalDevice->getDeviceProperties().limits.maxImageDimension2D;
    }

    int32 VulkanContext::getMaxConstantBufferSize() {
        return m_PhysicalDevice->getDeviceProperties().limits.maxUniformBufferRange;
    }

    int32 VulkanContext::getMaxDepthBufferBits() {
        return 0;
    }

    ShaderModule *VulkanContext::createShaderModule(const ShaderModuleDesc &desc) {
        return new VulkanShaderModule(desc, m_Device);
    }

    Shader *VulkanContext::createShader(const ShaderDesc& desc) {
        return nullptr;
    }

    VertexBuffer *VulkanContext::createVertexBuffer(const VertexBufferDesc &desc) {
        return nullptr;
    }

    IndexBuffer *VulkanContext::createIndexBuffer(const IndexBufferDesc &desc) {
        return nullptr;
    }

    VertexArray *VulkanContext::createVertexArray(const VertexArrayDesc &desc) {
        return nullptr;
    }

    ConstantBuffer *VulkanContext::createConstantBuffer(const ConstantBufferDesc &desc) {
        return nullptr;
    }

    FrameBuffer *VulkanContext::createFrameBuffer(const FrameBufferDesc &desc) {
        return nullptr;
    }

    Texture2D *VulkanContext::createTexture2D(const Texture2DDesc& desc) {
        return nullptr;
    }

    Sampler2D *VulkanContext::createSampler2D(const Sampler2DDesc &desc) {
        return nullptr;
    }

}

