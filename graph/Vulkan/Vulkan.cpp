#include "Vulkan.h"
#include <iostream>
#include <cstring>
using namespace std;
using count_ = uint32_t;
//#undef NDEBUG
#undef NDEBUG
#ifdef NDEBUG
const VkBool32 enableLayer = VK_FALSE;
#else
const VkBool32 enableLayer = VK_TRUE;
#endif
const std::vector<const char *> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
};

class CreateInstanceError {
};

VulkanDemo::VulkanDemo(int _width_, int _height_, const char *_title_)
		: width(_width_), height(_height_), title(_title_)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(_width_, _height_, _title_, nullptr, nullptr);
	glfwSetCenter();
	vulkanDeals();
	glfwDealEvents();
}

VulkanDemo::~VulkanDemo()
{
	vulkanDestoryCallbackEXT();
	vulkanDestory();

	glfwDestroyWindow(window);
	glfwTerminate();
}

// Glfw
void VulkanDemo::glfwSetCenter()
{
	GLFWmonitor *moniter = glfwGetPrimaryMonitor();
	const GLFWvidmode *vidmode = glfwGetVideoMode(moniter);
	glfwSetWindowPos(window, (vidmode->width - width) / 2,
					 (vidmode->height - height) / 2);
}

void VulkanDemo::glfwDealEvents()
{
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

// Vulkan

void VulkanDemo::vulkanDeals()
{
	vulkanCreateInstance();
	vulkanGetCallbackEXT();
	vulkanCreatePhysicalDevices();

}

void VulkanDemo::vulkanDestory()
{ vkDestroyInstance(instance, nullptr); }

VkBool32 VulkanDemo::vulkanCreateInstance()
{
	count_ version;
	vkEnumerateInstanceVersion(&version);
	std::cout << "Supported Vulkan Version is " << VK_VERSION_MAJOR(version)
			  << '.' << VK_VERSION_MINOR(version) << '.'
			  << VK_VERSION_PATCH(version) << '\n';
	VkApplicationInfo applicationinfo{
			VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "my Vulkan Demo1",
			VK_MAKE_VERSION(1, 3, 0), "no Engine", VK_MAKE_VERSION(1, 3, 0),
			VK_MAKE_API_VERSION(0, 1, 3, 0)

	};
	vector<const char *> exts = vulkanGetInstanceExt();
	VkBool32 layerAvailable = VK_FALSE;
	if (vulkanSelectLayers())layerAvailable = VK_TRUE;
	VkInstanceCreateInfo instanceCreateInfo{
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			nullptr,
			0,
			&applicationinfo,
			static_cast<count_>(layerAvailable ? validationLayers.size() : 0),
			layerAvailable ? validationLayers.data() : nullptr,
			(count_) exts.size(),
			exts.data()};
	if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
		throw CreateInstanceError();
	}
	return VK_TRUE;
}

VkBool32 VulkanDemo::vulkanCreatePhysicalDevices()
{
	vector<VkPhysicalDevice> pds = vulkanGetPhyDevices();
	VkPhysicalDevice pd = vulkanSelectSuitable(pds);
	if (pd) {
		physicalDevice = pd;
		return VK_TRUE;
	}
	return VK_FALSE;
}

vector<const char *> VulkanDemo::vulkanGetInstanceExt()
{
	count_ glfwExtensionCount = 0;
	const char **glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char *> extensions(glfwExtensions,
										 glfwExtensions + glfwExtensionCount);
	// count_ instanceExtCount = 0;
	// vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtCount,
	// nullptr); static vector<VkExtensionProperties> exts(instanceExtCount);

	// vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtCount,
	// exts.data());
	if (enableLayer) {
//		vector<const char *> tmp = vulkanGetMyNeedExtensions();
//		extensions.reserve(glfwExtensionCount + tmp.size());
//		extensions.insert(extensions.begin(), tmp.begin(), tmp.end());
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	cout << "检查扩展中" << endl;
	for (const auto &x: extensions) {
		cout << x << endl;
	}
	cout << "检查结束" << endl;


	return extensions;
}

vector<VkPhysicalDevice> VulkanDemo::vulkanGetPhyDevices()
{
	count_ phySize = 0;
	vkEnumeratePhysicalDevices(instance, &phySize, nullptr);
	vector<VkPhysicalDevice> phyDevices(phySize);
	if (phySize != 0) {
		vkEnumeratePhysicalDevices(instance, &phySize, phyDevices.data());
		cout << "枚举物理设备" << endl;
		for (const auto &x: phyDevices) {
			cout << x << endl;
		}
	}
	cout << "枚举结束" << endl;
	return phyDevices;
}

VkPhysicalDevice
VulkanDemo::vulkanSelectSuitable(const vector<VkPhysicalDevice> &_pds)
{
	VkPhysicalDeviceProperties vkpdPs;
	VkPhysicalDeviceFeatures vkpdFs;
	for (const auto &_pd: _pds) {
		vkGetPhysicalDeviceProperties(_pd, &vkpdPs);
		vkGetPhysicalDeviceFeatures(_pd, &vkpdFs);
		if (vkpdPs.deviceType ==
			VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
			vkpdFs.geometryShader == VK_TRUE && vulkanFindQueueFamily(_pd)) {
			cout << "Physical Device's Name is: " << ends;
			cout << vkpdPs.deviceName << endl;
			return _pd;
		}
	}
	return VK_NULL_HANDLE;
}

bool VulkanDemo::vulkanFindQueueFamily(const VkPhysicalDevice &physicalDevice)
{
	count_ queueCount;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount,
											 nullptr);
	vector<VkQueueFamilyProperties> vkFamily(queueCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount,
											 vkFamily.data());
	for (const auto &x: vkFamily) {
		if (x.queueCount > 0 && x.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			return true;
		}
	}
	return false;
}

bool VulkanDemo::vulkanSelectLayers()
{
//	if (!enableLayer)return false;
	count_ layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	vector<VkLayerProperties> layers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, layers.data());
	for (const auto &x: validationLayers) {
		VkBool32 tmp = VK_FALSE;
		for (const auto &layer: layers) {
			cout << layer.layerName << endl;
			if (strcmp(x, layer.layerName) == 0) {
				tmp = VK_TRUE;
				break;
			}
		}
		if (!tmp)return false;
	}
	cout << "layers available" << endl;
	return true;
}

const char *VulkanDemo::vulkanGetMyNeedExtensions()
{

	return VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
}

void VulkanDemo::vulkanGetCallbackEXT()
{
	if (!enableLayer)return;
	VkDebugReportCallbackCreateInfoEXT callbackCreateInfoExt;
	callbackCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	callbackCreateInfoExt.pNext = nullptr;
	callbackCreateInfoExt.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	callbackCreateInfoExt.pfnCallback = vulkanDebugExtCall;
//	callbackCreateInfoExt.pUserData = ;
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	func(instance, &callbackCreateInfoExt, nullptr, &callbackExt);
}

VKAPI_ATTR VkBool32
VKAPI_CALL VulkanDemo::vulkanDebugExtCall(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
										  size_t location, int32_t code, const char *layerPrefix, const char *msg,
										  void *userData)
{
	std::cerr << "validation layer: " << msg << std::endl;
	return VK_FALSE;
}

void VulkanDemo::vulkanDestoryCallbackEXT()
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
																			"vkDestroyDebugReportCallbackEXT");
	func(instance, callbackExt, nullptr);
}

