#include "VulkanQueueFamily.hpp"

namespace Syrius{

    bool QueueFamilyIndices::isComplete() {
        return m_GraphicsFamily.has_value();
    }

    QueueFamilyIndices findQueueFamily(VkPhysicalDevice device){
        QueueFamilyIndices indices;

        uint32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

        int32 i = 0;
        for (const auto& queueFamily: queueFamilyProperties){
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
                indices.m_GraphicsFamily = i;
            }

            if (indices.isComplete()){
                break;
            }
            i++;
        }

        return indices;
    }

}
