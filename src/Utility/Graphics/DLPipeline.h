/*
    Followed Vulkan Tutorial more or less verbatim at https://vulkan-tutorial.com/Introduction
*/

#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <map>
#include <set>
#include <cstdint>
#include <limits>
#include <chrono>
#include <unordered_map>

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"
#include "../Math/Pi.h"
#include "Vertex.h"
#include "MemoryPool.h"

#include <ctime>
#include <cstring>

#include <stb_image.h>

#include <tiny_obj_loader.h>

struct SwapChainSupportDetails;

struct UniformBufferObject;

//const std::vector<Vertex> vertices = {
//    
//    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
//    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
//    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
//    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//
//    { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
//    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
//    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
//    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//
//    { {-0.5f, -0.5f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
//    {{0.5f, -0.5f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
//    {{0.5f, 0.5f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
//    {{-0.5f, 0.5f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
//};
//
////use uint32_t for greater than 65535 vertices
//const std::vector<uint16_t> indices = {
//    0, 1, 2, 2, 3, 0,
//    4, 5, 6, 6, 7, 4,
//    8, 9, 10, 10, 11, 8
//};

struct QueueFamilyIndices;

struct SwapchainSupportDetails;

class DLPipeline {
public:

    void run();

    // devices and physical devices
    VkPhysicalDevice physicalDevice;
    VkDevice device; //UPGRADEME should have a getter

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);


private:

    // general objects
    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    
    
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    // swap chain member variables
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews; // this could be combined with swapChainImages in a struct

    // pipeline stuff
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    // frame buffers
    std::vector<VkFramebuffer> swapChainFramebuffers;
    uint32_t currentFrame = 0;
    bool framebufferResized = false;

    // command stuff
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    // Semaphores and Fences
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    // shader buffers
    MPBuffer* vertexBuffer;
    MPBuffer* indexBuffer;
    MemoryPool* vertexAndIndexBufferMemory;

    std::vector<MPBuffer*> uniformBuffers;
    std::vector<void*> uniformBuffersMapped;
    MemoryPool* uniformBufferMemoryPool;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    // Images
    uint32_t mipLevels;
    VkImage textureImage;
    MemoryPool* textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    // Models and Textures
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    //NEXT make some vertexes and indices for text and such

    // Multisampling
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

    long frames_per_second;

    // General Init and main loops
    void initWindow();

    void initVulkan();
    
    void mainLoop();
    
    void cleanup();

    void drawFrame();

    void updateUniformBuffer(uint32_t currentImage);

    // Create Functions

    void createInstance();
    
    void setupDebugMessenger();

    void createSurface();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createSwapChain();

    void createImageViews();

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

    void createRenderPass();

    void createDescriptorPool();

    void createDescriptorSets();

    void createGraphicsPipeline();

    void createFramebuffers();

    void createCommandPool();

    void createVertexAndIndexBuffers();

    void createUniformBuffers();

    void createCommandBuffers();

    void createSyncObjects();
    
    void createDescriptorSetLayout();

    void createTextureImage();

    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling,
        VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    
    void createDepthResources();

    // Validation, Extensions, and Support Verification Util

    std::vector<const char*> getRequiredExtensions();

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice);

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    bool checkValidationLayerSupport();

    int ratePhysicalDevice(VkPhysicalDevice physicalDevice);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);
    

    VkFormat findSupportedFormat(const std::vector<VkFormat>& canidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    VkFormat findDepthFormat();

    bool hasStencilComponent(VkFormat format);

    // Swapchain Util

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    void recreateSwapChain();

    void cleanupSwapChain();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    // Shader Util

    VkShaderModule createShaderModule(const std::vector<char>& code);

    static std::vector<char> readFile(const std::string& filename);

    // Command Buffer Util

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    
    // Texture Util

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

    void createTextureImageView();

    void createTextureSampler();

    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

    // Model Util
    
    void loadModel();

    // Multisampling

    VkSampleCountFlagBits getMaxUsableSampleCount();

    void createColorResources();

    // Misc

};