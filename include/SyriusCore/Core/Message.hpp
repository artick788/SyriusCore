#pragma once

#include "SyriusCoreInclude.hpp"

namespace Syrius{

    typedef enum SR_CORE_MESSAGE_SOURCE{
        SR_CORE_MESSAGE                  = 0x00,
        SR_CORE_MESSAGE_OPENGL           = 0x01,
        SR_CORE_MESSAGE_VULKAN           = 0x02,
        SR_CORE_MESSAGE_HRESULT          = 0x03,
        SR_CORE_MESSAGE_D3D11            = 0x04,
        SR_CORE_MESSAGE_DXGI             = 0x05,
        SR_CORE_MESSAGE_PRECONDITION     = 0x11,
        SR_CORE_MESSAGE_POSTCONDITION    = 0x12,
        SR_CORE_MESSAGE_ASSERTION        = 0x13,
    } SR_CORE_MESSAGE_SOURCE;

    typedef enum SR_CORE_MESSAGE_SEVERITY{
        SR_CORE_MESSAGE_SEVERITY_INFO    = 0x00,
        SR_CORE_MESSAGE_SEVERITY_LOW     = 0x01,      // mostly used for messages that are not important
        SR_CORE_MESSAGE_SEVERITY_MEDIUM  = 0x02,      // used for messages that are important, but not critical
        SR_CORE_MESSAGE_SEVERITY_HIGH    = 0x03,      // used for messages that are critical and (usually) results in program termination
    } SR_CORE_MESSAGE_SEVERITY;

    struct Message{
        SR_CORE_MESSAGE_SOURCE m_Type;
        SR_CORE_MESSAGE_SEVERITY m_Severity;
        std::string m_Message;
        std::string m_Function;
        std::string m_File;
        uint32 m_Line;
    };

    typedef void(*handleDebugMessageFunc)(const Message&);

    std::string SR_CORE_API getMessageTypeString(SR_CORE_MESSAGE_SOURCE type);

    std::string SR_CORE_API getMessageSeverityString(SR_CORE_MESSAGE_SEVERITY severity);


}
