#include "VulkanTest.h"
#include <iostream>


using namespace vk;

VulkanTest::VulkanTest()
{
}


VulkanTest::~VulkanTest()
{
}

Result VulkanTest::InitInstance() {
	vk::InstanceCreateInfo instInfo = {};
	instInfo.sType(StructureType::eInstanceCreateInfo).
		pApplicationInfo(&AppInfo);

	return createInstance(&instInfo, nullptr, &Instance);
}

void VulkanTest::DestroyInstance() {
	destroyInstance(Instance, nullptr);
}

Result VulkanTest::InitDevice() {
	auto result = enumeratePhysicalDevices(Instance, GPUs);

	if (!CheckVulkanError(result))
		return result;

	QueueProperties = getPhysicalDeviceQueueFamilyProperties(GPUs[0]);

	bool foundGraphicsQueue = false;
	for each (auto queueProperty in QueueProperties) {
		if (queueProperty.queueFlags() & QueueFlagBits::eGraphics) {
			foundGraphicsQueue = true;
			break;
		}
	}

	if (!foundGraphicsQueue) {
		return Result::eVkErrorInitializationFailed;
	}

	float queuePriorities[1] = { 0.0 };
	DeviceQueueCreateInfo queueInfo = {};
	queueInfo.sType(StructureType::eDeviceQueueCreateInfo).
		queueCount(1).
		pQueuePriorities(queuePriorities);

	DeviceCreateInfo deviceInfo = {};
	deviceInfo.sType(StructureType::eDeviceCreateInfo).
		queueCreateInfoCount(1).
		pQueueCreateInfos(&queueInfo);

	return createDevice(GPUs[0], &deviceInfo, nullptr, &Device);
}

void VulkanTest::DestroyDevice() {
	destroyDevice(Device, nullptr);
}

bool VulkanTest::CheckVulkanError(Result result) {
	switch (result) {
	case Result::eVkErrorDeviceLost:
		std::cout << "Vulkan Error: Device Lost\n";
		return false;
	case Result::eVkErrorExtensionNotPresent:
		std::cout << "Vulkan Error: Extension not present\n";
		return false;
	case Result::eVkErrorFeatureNotPresent:
		std::cout << "Vulkan Error: Feature not present\n";
		return false;
	case Result::eVkErrorFormatNotSupported:
		std::cout << "Vulkan Error: Format not supported\n";
		return false;
	case Result::eVkErrorIncompatibleDriver:
		std::cout << "Vulkan Error: Incompatible Driver\n";
		return false;
	case Result::eVkErrorInitializationFailed:
		std::cout << "Vulkan Error: Initialization failed\n";
		return false;
	case Result::eVkErrorLayerNotPresent:
		std::cout << "Vulkan Error: Layer not present\n";
		return false;
	case Result::eVkErrorMemoryMapFailed:
		std::cout << "Vulkan Error: Memory map failed\n";
		return false;
	case Result::eVkErrorOutOfDeviceMemory:
		std::cout << "Vulkan Error: Out of device memory\n";
		return false;
		break;
	case Result::eVkErrorOutOfHostMemory:
		std::cout << "Vulkan Error: Out of host memory\n";
		return false;
	case Result::eVkErrorTooManyObjects:
		std::cout << "Vulkan Error: Too many objects\n";
		return false;
	case Result::eVkEventReset:
		std::cout << "Vulkan Event: Reset\n";
		return true;
	case Result::eVkEventSet:
		std::cout << "Vulkan Event: Set\n";
		return true;
	case Result::eVkIncomplete:
		std::cout << "Vulkan Result: Incomplete\n";
		return true;
	case Result::eVkNotReady:
		std::cout << "Vulkan Result: Not ready\n";
		return true;
	case Result::eVkSuccess:
		std::cout << "Vulkan Result: Success\n";
		return true;
	case Result::eVkTimeout:
		std::cout << "Vulkan Result: Timeout\n";
		return true;
	default:
		std::cout << "Unknown return value in vk::Result\n";
		return false;
	}
}