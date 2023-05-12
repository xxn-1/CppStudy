#include <GLFW/glfw3.h>
#include <vulkan/Vulkan.h>
#include <vector>
#include <iostream>

typedef class VulkanDemo {
	// Alias
public:
	//
	VulkanDemo() = default;

	VulkanDemo(int _width_, int _height_, const char *_title_);

	~VulkanDemo();

	// glfw
	void glfwSetCenter();

	void glfwDealEvents();

	// Vulkan
	void vulkanDeals();

	VkBool32 vulkanCreateInstance();

	VkBool32 vulkanCreatePhysicalDevices();

	void vulkanDestory();

private:
	// vars
	GLFWwindow *window = nullptr;
	VkInstance instance{};
	int width{}, height{};
	const char *title{};
	// std::vector<VkPhysicalDevice> physicalDevices;
	VkPhysicalDevice physicalDevice{};
	VkDebugReportCallbackEXT callbackExt;

private:
	std::vector<const char *> vulkanGetInstanceExt();

	std::vector<VkPhysicalDevice> vulkanGetPhyDevices();

	VkPhysicalDevice vulkanSelectSuitable(const std::vector<VkPhysicalDevice> &);

	bool vulkanFindQueueFamily(const VkPhysicalDevice &);

	bool vulkanSelectLayers();

	const char *vulkanGetMyNeedExtensions();

	void vulkanGetCallbackEXT();

	void vulkanDestoryCallbackEXT();

	// static
	static VkBool32 vulkanDebugExtCall(VkDebugReportFlagsEXT flags,
									   VkDebugReportObjectTypeEXT objType,
									   uint64_t obj,
									   size_t location,
									   int32_t code,
									   const char *layerPrefix,
									   const char *msg,
									   void *userData);
} VulkanDemo;



