#include "GlContext.hpp"

namespace Syrius{

    GlContext::GlContext(const ContextDesc& desc)
    : Context(desc){

    }

    GlContext::~GlContext() {
        delete m_DefaultFrameBuffer;

        CoreCommand::terminateGlad();
    }

    void GlContext::initGl(const FrameBufferDesc& desc) {
        CoreCommand::initGlad();

        m_DefaultFrameBuffer = new GlDefaultFramebuffer(desc);
    }

    std::string GlContext::getAPIVersion() {
        const unsigned char* version = glGetString(GL_VERSION);
        char* temp = (char*) version;
        std::string retVal = temp;
        return retVal;
    }

    std::string GlContext::getDeviceName() {
        const unsigned char* version = glGetString(GL_RENDERER);
        char* temp = (char*) version;
        std::string retVal = temp;
        return retVal;
    }

    std::string GlContext::getShadingLanguageVersion() {
        const unsigned char* version = glGetString(GL_SHADING_LANGUAGE_VERSION);
        char* temp = (char*) version;
        std::string retVal = temp;
        return retVal;
    }

    int32 GlContext::getMaxFramebufferWidth() {
        int32 maxFramebufferWidth;
        glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &maxFramebufferWidth);
        return maxFramebufferWidth;
    }

    int32 GlContext::getMaxFramebufferHeight() {
        int32 maxFramebufferHeight;
        glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &maxFramebufferHeight);
        return maxFramebufferHeight;
    }

    int32 GlContext::getMaxFramebufferTextureAttachments() {
        int32 maxAttach;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
        return maxAttach;
    }

    int32 GlContext::getMaxTextureSlots() {
        int32 maxTextureSlotCount;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSlotCount);
        return maxTextureSlotCount;
    }

    int32 GlContext::getMaxTexture2DSize() {
        int32 maxTextureSize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        return maxTextureSize;
    }

    int32 GlContext::getMaxConstantBufferSize() {
        int32 maxCbufferSize;
        glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxCbufferSize);
        return maxCbufferSize;
    }

    int32 GlContext::getMaxDepthBufferBits() {
        int32 depthBufferBits;
        glGetIntegerv(GL_DEPTH_BITS, &depthBufferBits);
        return depthBufferBits;
    }

    void GlContext::draw(VertexArray *vao) {
        SR_CORE_PRECONDITION(vao != nullptr, "VertexArray is null");

        vao->drawBuffers();
    }

    void GlContext::drawInstanced(VertexArray *vao, uint32 instanceCount) {
        SR_CORE_PRECONDITION(vao != nullptr, "VertexArray is null");

        vao->drawBuffersInstanced(instanceCount);
    }

    void GlContext::onResize(uint32 width, uint32 height) {
        SR_CORE_PRECONDITION(width <= getMaxFramebufferWidth(), "Framebuffer width is too large");
        SR_CORE_PRECONDITION(height <= getMaxFramebufferHeight(), "Framebuffer height is too large");
        m_DefaultFrameBuffer->onResize(width, height);
    }


    ShaderModule *GlContext::createShaderModule(const ShaderModuleDesc &desc) {
        return new GlShaderModule(desc);
    }

    Shader *GlContext::createShader(const ShaderDesc& desc) {
        return new GlShader(desc);
    }

    VertexBuffer *GlContext::createVertexBuffer(const VertexBufferDesc &desc) {
        return new GlVertexBuffer(desc);
    }

    IndexBuffer *GlContext::createIndexBuffer(const IndexBufferDesc &desc) {
        return new GlIndexBuffer(desc);
    }

    VertexArray *GlContext::createVertexArray(const VertexArrayDesc &desc) {
        if (desc.m_IndexBuffer != nullptr) {
            return new GlVertexArrayIndexed(desc);
        }
        else {
            return new GlVertexArray(desc);
        }
    }

    ConstantBuffer *GlContext::createConstantBuffer(const ConstantBufferDesc &desc) {
        SR_CORE_PRECONDITION(desc.m_Size <= getMaxConstantBufferSize(), "Constant buffer size is too large");

        return new GlConstantBuffer(desc);
    }

    FrameBuffer *GlContext::createFrameBuffer(const FrameBufferDesc &desc) {
        SR_CORE_PRECONDITION(!desc.m_ColorAttachments.empty(), "Framebuffer must have at least one color attachment");
        SR_CORE_PRECONDITION(desc.m_Width <= getMaxFramebufferWidth(), "Framebuffer width is too large");
        SR_CORE_PRECONDITION(desc.m_Height <= getMaxFramebufferHeight(), "Framebuffer height is too large");
        SR_CORE_PRECONDITION(desc.m_NumColorAttachments <= getMaxFramebufferTextureAttachments(), "Framebuffer has too many color attachments");

        return new GlFrameBuffer(desc);
    }

    Texture2D *GlContext::createTexture2D(const Texture2DDesc& desc) {
        SR_CORE_PRECONDITION(desc.m_Image != nullptr, "Texture image is null");
        SR_CORE_PRECONDITION(desc.m_Image->getWidth() <= getMaxTexture2DSize(), "Texture width is too large");
        SR_CORE_PRECONDITION(desc.m_Image->getHeight() <= getMaxTexture2DSize(), "Texture height is too large");

        return new GlTexture2D(desc);
    }

}

