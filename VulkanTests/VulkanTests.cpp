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

	auto resInit = vkT.InitInstance();

	if (resInit == vk::Result::eVkErrorIncompatibleDriver) {
		std::cout << "cannot find a compatible Vulkan ICD\n";
		exit(-1);
	} else if (resInit != vk::Result::eVkSuccess) {
		std::cout << "unknown error\n";
		exit(-1);
	}


	std::vector<vk::PhysicalDevice> gpus;
	auto resEnDevice = vk::enumeratePhysicalDevices(vkT.Instance, gpus);

	auto queue_properties = vk::getPhysicalDeviceQueueFamilyProperties(gpus[0]);

	bool foundGraphicsQueue = false;

	for each (auto queue_property in queue_properties)
	{
		if (queue_property.queueFlags() & vk::QueueFlagBits::eGraphics) {
			foundGraphicsQueue = true;
		}
	}

	if (!foundGraphicsQueue) {
		std::cout << "no graphics queue\n";
		exit(-1);
	}

	float queue_priorities[1] = { 0.0 };
	vk::DeviceQueueCreateInfo queueInfo = {};
	queueInfo.sType(vk::StructureType::eDeviceQueueCreateInfo).
		queueCount(1).
		pQueuePriorities(queue_priorities);

	vk::DeviceCreateInfo deviceInfo = {};
	deviceInfo.sType(vk::StructureType::eDeviceCreateInfo).
		queueCreateInfoCount(1).
		pQueueCreateInfos(&queueInfo);

	vk::Device device;

	auto resCreateDevice = vk::createDevice(gpus[0], &deviceInfo, nullptr, &device);

	vk::destroyDevice(device, nullptr);

	vkT.DestroyInstance();

	return 0;
}

