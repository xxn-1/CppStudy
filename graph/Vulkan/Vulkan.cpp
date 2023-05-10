#include <iostream>
#include "Vulkan.h"
using namespace std;
using count_ = uint32_t;
class CreateInstanceError
{
};
VulkanDemo::VulkanDemo(int _width_, int _height_, const char *_title_) : width(_width_), height(_height_), title(_title_)
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
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Glfw
void VulkanDemo::glfwSetCenter()
{
    GLFWmonitor *moniter = glfwGetPrimaryMonitor();
    const GLFWvidmode *vidmode = glfwGetVideoMode(moniter);
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
}

void VulkanDemo::glfwDealEvents()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

// Vulkan

void VulkanDemo::vulkanDeals()
{
    vulkanCreateInstance();
    vulkanCreatePhysicalDevices();
}

VkBool32 VulkanDemo::vulkanCreateInstance()
{
    count_ version;
    vkEnumerateInstanceVersion(&version);
    std::cout << "Supported Vulkan Version is "
              << VK_VERSION_MAJOR(version) << '.'
              << VK_VERSION_MINOR(version) << '.'
              << VK_VERSION_PATCH(version) << '\n';
    VkApplicationInfo applicationinfo{
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,
        "my Vulkan Demo1",
        VK_MAKE_VERSION(1, 3, 0),
        "no Engine",
        VK_MAKE_VERSION(1, 3, 0),
        VK_MAKE_API_VERSION(0, 1, 3, 0)

    };
    vector<const char *> exts = vulkanGetInstanceExt();
    VkInstanceCreateInfo instanceCreateInfo{
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        nullptr,
        0,
        &applicationinfo,
        0,
        nullptr,
        (count_)exts.size(),
        exts.data()};
    if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw CreateInstanceError();
    }
    return VK_TRUE;
}

VkBool32 VulkanDemo::vulkanCreatePhysicalDevices()
{
    vector<VkPhysicalDevice> pds = vulkanGetPhyDevices();
    VkPhysicalDevice pd = vulkanSelectSuitable(pds);
    if (pd)
    {
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
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    // count_ instanceExtCount = 0;
    // vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtCount, nullptr);
    // static vector<VkExtensionProperties> exts(instanceExtCount);

    // vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtCount, exts.data());
    cout << "检查扩展中" << endl;
    for (const auto &x : extensions)
    {
        cout << x << endl;
    }

    return extensions;
}

vector<VkPhysicalDevice> VulkanDemo::vulkanGetPhyDevices()
{
    count_ phySize = 0;
    vkEnumeratePhysicalDevices(instance, &phySize, nullptr);
    vector<VkPhysicalDevice> phyDevices(phySize);
    if (phySize != 0)
    {
        vkEnumeratePhysicalDevices(instance, &phySize, phyDevices.data());
        cout << "枚举物理设备" << endl;
        for (const auto &x : phyDevices)
        {
            cout << x << endl;
        }
    }
    return phyDevices;
}

VkPhysicalDevice VulkanDemo::vulkanSelectSuitable(const vector<VkPhysicalDevice> &_pds)
{
    VkPhysicalDeviceProperties vkpdPs;
    VkPhysicalDeviceFeatures vkpdFs;
    for (const auto &_pd : _pds)
    {
        vkGetPhysicalDeviceProperties(_pd, &vkpdPs);
        vkGetPhysicalDeviceFeatures(_pd, &vkpdFs);
        if (vkpdPs.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && vkpdFs.geometryShader == VK_TRUE)
        {
            cout << "物理设备名" << endl;
            cout << vkpdPs.deviceName << endl;
            return _pd;
        }
    }
    return VK_NULL_HANDLE;
}