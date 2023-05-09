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
    bool vulkanCreateInstance();

private:
    // vars
    GLFWwindow *window = nullptr;
    VkInstance instance;
    int width, height;
    const char *title;

private:
    std::vector<const char *> vulkanGetInstanceExt();
} VulkanDemo;
