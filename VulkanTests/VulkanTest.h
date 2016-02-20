#pragma once

#define VKCPP_ENHANCED_MODE
#include "vulkan\vk_cpp.h"

class VulkanTest
{
public:
	VulkanTest();
	~VulkanTest();

	vk::ApplicationInfo AppInfo;
	vk::Instance Instance;
	std::vector<vk::PhysicalDevice> GPUs;
	std::vector<vk::QueueFamilyProperties> QueueProperties;
	vk::Device Device;

	vk::Result InitInstance();
	void DestroyInstance();

	vk::Result InitDevice();
	void DestroyDevice();

	bool CheckVulkanError(vk::Result result);
};

