#include "../../../../include/SyriusCore/Context/VertexDescription.hpp"
#include "../Core/DebugMacros.hpp"

namespace Syrius{

    VertexAttribute::VertexAttribute(const std::string &name, SR_SCALAR_TYPE type, uint8 size, uint8 elementCount)
    : m_Name(name),
      m_Type(type),
      m_Size(size),
      m_ElementCount(elementCount) {

    }


    VertexDescription::VertexDescription()
    : m_Stride(0) {

    }

    VertexDescription::~VertexDescription() = default;

    void VertexDescription::addAttribute(const std::string &name, SR_SCALAR_TYPE dataType) {
        SR_CORE_PRECONDITION(getScalarComponentCount(dataType) < 5, "Vertex attribute cannot have more than 4 components");
        SR_CORE_PRECONDITION(getScalarComponentCount(dataType) > 0, "Vertex attribute cannot have less than 1 component");

        uint8 elementCount = getScalarComponentCount(dataType);
        uint8 size = getTypeSize(dataType);

        m_Attributes.emplace_back(name, dataType, size, elementCount);
        m_Stride += size;

    }

    uint32 VertexDescription::getStride() const {
        return m_Stride;
    }

    const std::vector<VertexAttribute> &VertexDescription::getAttributes() const {
        return m_Attributes;
    }

}