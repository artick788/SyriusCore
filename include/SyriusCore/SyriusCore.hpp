#pragma once

#include "Core/SyriusCoreInclude.hpp"
#include "Core/DebugMessageHandler.hpp"
#include "Utils/Image.hpp"
#include "Window/SyriusWindow.hpp"

#include "Dependencies/imgui/imgui.h"

namespace Syrius {

    void SR_API syriusInit();

    void SR_API syriusTerminate();

    Time SR_API getStartupTime();

    Time SR_API getElapsedTimeSinceStart();

    Image* SR_API createImage(const std::string& fileName, bool flipOnLoad = true);

    Image* SR_API createImage(const ubyte* pixelData, int32 width, int32 height, int32 channelCount);

    Image* SR_API createImage(const std::vector<ubyte>& pixelData, int32 width, int32 height, int32 channelCount);

    SyriusWindow* SR_API createWindow(const WindowDesc& windowDesc);

    void SR_API setDebugMessageCallback(handleDebugMessageFunc callback);

    void SR_API test();

}

