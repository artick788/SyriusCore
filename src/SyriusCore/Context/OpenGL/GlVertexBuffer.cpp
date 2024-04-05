#include "GlVertexBuffer.hpp"

namespace Syrius{

    GlVertexBuffer::GlVertexBuffer(const VertexBufferDesc &desc, const Resource<DeviceLimits>& deviceLimits):
    VertexBuffer(desc, deviceLimits),
    m_BufferID(0){
        createBuffer(desc.data);
    }

    GlVertexBuffer::~GlVertexBuffer() {
        glDeleteBuffers(1, &m_BufferID);
    }

    void GlVertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }

    void GlVertexBuffer::setData(const void *data, uint32 count) {
        SR_CORE_PRECONDITION(m_Usage == SR_BUFFER_USAGE_DYNAMIC, "[VertexBuffer]: Update on buffer object (%p) requested, which has not been created with SR_BUFFER_USAGE_DYNAMIC flag!", this);
        SR_CORE_PRECONDITION(count * m_Layout->getStride() <= m_Size, "[VertexBuffer]: Update on buffer object (%p) requested, which exceeds the current buffer size (%i > %i).", this, count * m_Layout->getStride(), m_Size);

        uint32 copySize = count * m_Layout->getStride();
        m_Count = count;

        auto pBuffer = glMapNamedBuffer(m_BufferID, GL_WRITE_ONLY);
        memcpy(pBuffer, data, copySize);
        auto retVal = glUnmapNamedBuffer(m_BufferID);
        SR_CORE_ASSERT(retVal, "[GlVertexBuffer]: Failed to unmap buffer object (%i)", m_BufferID);
    }

    Resource<ubyte[]> GlVertexBuffer::getData() const {
        Resource<ubyte[]> data(new ubyte[m_Size]);
        auto pBuffer = glMapNamedBuffer(m_BufferID, GL_READ_ONLY);
        memcpy(data.get(), pBuffer, m_Size);
        auto retVal = glUnmapNamedBuffer(m_BufferID);
        SR_CORE_ASSERT(retVal, "[GlVertexBuffer]: Failed to unmap buffer object (%i)", m_BufferID);
        return std::move(data);
    }

    uint64 GlVertexBuffer::getIdentifier() const {
        return m_BufferID;
    }

    void GlVertexBuffer::createBuffer(const void *data) {
        glCreateBuffers(1, &m_BufferID);
        glNamedBufferData(m_BufferID, m_Size, data, getGlBufferType(m_Usage));
    }


}
