#include "../../../include/SyriusCore/Context/VertexBuffer.hpp"
#include "../Utils/DebugMacros.hpp"

namespace Syrius{

    VertexBuffer::VertexBuffer(const VertexBufferDesc &desc, const Resource<DeviceLimits>& deviceLimits):
    m_DeviceLimits(deviceLimits),
    m_Count(desc.count),
    m_Type(desc.usage),
    m_Size(0),
    m_Layout(desc.layout){

        m_Size = desc.layout->getStride() * desc.count;

    }

    VertexBuffer::~VertexBuffer() {

    }

    uint32 VertexBuffer::getSize() const {
        return m_Size;
    }

    uint32 VertexBuffer::getCount() const {
        return m_Count;
    }

    SR_BUFFER_USAGE VertexBuffer::getUsage() const {
        return m_Type;
    }

    const ResourceView<VertexLayout>& VertexBuffer::getLayout() const {
        return m_Layout;
    }
}