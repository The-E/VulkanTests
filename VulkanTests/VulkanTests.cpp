// VulkanTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "vulkan\vk_cpp.h"

#define APP_SHORT_NAME "VulkanTest"

int main()
{
	vk::ApplicationInfo appInfo = {};
	appInfo.sType(vk::StructureType::eApplicationInfo).
		pNext(nullptr).
		pApplicationName(APP_SHORT_NAME).
		applicationVersion(1).
		pEngineName(APP_SHORT_NAME).
		engineVersion(1).
		apiVersion(VK_API_VERSION);

	vk::InstanceCreateInfo instInfo = {};
	instInfo.sType(vk::StructureType::eInstanceCreateInfo).
		pNext(nullptr).
		flags(0).
		pApplicationInfo(&appInfo);

	vk::Instance inst;

	auto res = vk::createInstance(&instInfo, nullptr, &inst);

	if (res == vk::Result::eVkErrorIncompatibleDriver) {
		std::cout << "cannot find a compatible Vulkan ICD\n";
		exit(-1);
	} else if (res != vk::Result::eVkSuccess) {
		std::cout << "unknown error\n";
		exit(-1);
	}

	vk::destroyInstance(inst, nullptr);

	return 0;
}

