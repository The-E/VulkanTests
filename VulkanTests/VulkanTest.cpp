#include "VulkanTest.h"
#include <iostream>


VulkanTest::VulkanTest()
{
}


VulkanTest::~VulkanTest()
{
}

vk::Result VulkanTest::InitInstance() {
	vk::InstanceCreateInfo instInfo = {};
	instInfo.sType(vk::StructureType::eInstanceCreateInfo).
		pApplicationInfo(&AppInfo);

	return vk::createInstance(&instInfo, nullptr, &Instance);
}

void VulkanTest::DestroyInstance() {
	vk::destroyInstance(Instance, nullptr);
}