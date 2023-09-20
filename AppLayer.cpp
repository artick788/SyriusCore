#include <chrono>
#include "AppLayer.hpp"

AppLayer::AppLayer(ResourceView<Context> &context, const Resource<SyriusWindow> &window, EasyIni::Configuration &config):
Layer(context, window, config),
m_DeltaTime(0.0),
m_LastFrameTime(0.0) {

}

AppLayer::~AppLayer() {

}

void AppLayer::onUpdate() {
    updateTime();
    render();
    renderImGui();
}

void AppLayer::onEvent(const Event &event) {

}

void AppLayer::onAttach() {
    m_Window->createImGuiContext();

    auto rectangle = createRectangle();
    m_ShaderProgram = m_ShaderLibrary.loadShader("Basic");
    m_VertexArray = loadMesh(rectangle, m_ShaderProgram);

    SamplerDesc samplerDesc;
    m_Sampler = m_Context->createSampler(samplerDesc);
    auto image = createImage("./Resources/Textures/awesomeface.png");
    Texture2DImageDesc t2dDesc(image);
    m_Texture = m_Context->createTexture2D(t2dDesc);

}

void AppLayer::onDetach() {
    m_Window->destroyImGuiContext();
}

void AppLayer::updateTime() {
    auto currentTime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count());
    m_DeltaTime = currentTime - m_LastFrameTime;
    m_LastFrameTime = currentTime;

}

void AppLayer::render() {
    m_Context->beginRenderPass();

    m_ShaderProgram.shaderProgram->bind();
    m_Sampler->bind(0);
    m_Texture->bind(0);
    m_Context->draw(m_VertexArray);

    m_Context->endRenderPass();
}

void AppLayer::renderImGui() {
    m_Window->onImGuiBegin();

    ImGui::Begin("SyriusCoreDev");
    ImGui::Text("FPS: %.2f", 1000.0 / m_DeltaTime);
    ImGui::ColorPicker3("Background Color", m_Context->getDefaultFrameBuffer()->getColorAttachment(0)->getClearColor());

    ImGui::End();

    m_Window->onImGuiEnd();
}