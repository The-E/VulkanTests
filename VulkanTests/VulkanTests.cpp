// VulkanTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#define VKCPP_ENHANCED_MODE
#include "vulkan\vk_cpp.h"
#include "VulkanTest.h"

#define APP_SHORT_NAME "VulkanTest"



int main()
{
	VulkanTest vkT;
	
	vkT.AppInfo = {};
	vkT.AppInfo.sType(vk::StructureType::eApplicationInfo).
		pApplicationName(APP_SHORT_NAME).
		applicationVersion(1).
		pEngineName(APP_SHORT_NAME).
		engineVersion(1).
		apiVersion(VK_API_VERSION);

	if (!vkT.CheckVulkanError(vkT.InitInstance()))
		exit(-1);
	
	if (!vkT.CheckVulkanError(vkT.InitDevice()))
		exit(-1);

	vkT.DestroyDevice();

	vkT.DestroyInstance();

	return 0;
}

