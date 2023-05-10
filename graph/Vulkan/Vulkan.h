#include <GLFW/glfw3.h>
#include <vulkan/Vulkan.h>
#include <vector>
typedef class VulkanDemo
{
    // Alias
public:
    //
    VulkanDemo(){};
    VulkanDemo(int _width_, int _height_, const char *_title_);
    ~VulkanDemo();

    // glfw
    void glfwSetCenter();
    void glfwDealEvents();

    // Vulkan
    void vulkanDeals();
    VkBool32 vulkanCreateInstance();
    VkBool32 vulkanCreatePhysicalDevices();

private:
    // vars
    GLFWwindow *window = nullptr;
    VkInstance instance;
    int width, height;
    const char *title;
    // std::vector<VkPhysicalDevice> physicalDevices;
    VkPhysicalDevice physicalDevice;

private:
    std::vector<const char *> vulkanGetInstanceExt();
    std::vector<VkPhysicalDevice> vulkanGetPhyDevices();
    VkPhysicalDevice vulkanSelectSuitable(const std::vector<VkPhysicalDevice> &);

} VulkanDemo;
