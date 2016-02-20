#pragma once

#include "vulkan\vk_cpp.h"

class VulkanTest
{
public:
	VulkanTest();
	~VulkanTest();

	vk::ApplicationInfo AppInfo;
	vk::Instance Instance;

	vk::Result InitInstance();
	void DestroyInstance();
};

