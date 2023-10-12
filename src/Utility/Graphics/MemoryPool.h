#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <vector>
#include <stdexcept>

class DLPipeline;

struct MPBuffer {
	VkBuffer buffer;
	VkDeviceSize size;
	VkDeviceSize memLocation;
	VkBufferUsageFlags usage;
	VkBufferUsageFlags gpuUsage;
private:
	VkDevice device;
public:

	void VKBuffer() {};

	void createNewBuffer(DLPipeline* pipeline, VkDeviceSize size, VkBufferUsageFlags usage, VkBufferUsageFlags gpuUsage = 0);

	VkDeviceSize getBufferOffset()
	{
		VkMemoryRequirements requirements;
		vkGetBufferMemoryRequirements(device, buffer, &requirements);
		return requirements.alignment;
	}

	void destroyBuffer()
	{
		vkDestroyBuffer(device, buffer, nullptr);
	}

	MPBuffer()
	{
		buffer = nullptr;
		size = 0;
		usage = 0;
		gpuUsage = 0;
		device = nullptr;
		memLocation = -1;
	}

	MPBuffer(const MPBuffer& copy)
	{
		buffer = copy.buffer;
		size = copy.size;
		usage = copy.usage;
		gpuUsage = copy.gpuUsage;
		device = copy.device;
		memLocation = copy.memLocation;
	}
};

class MemoryPool {

private:
	DLPipeline* pipeline;
	VkPhysicalDeviceProperties deviceLimits;

	VkDeviceMemory memory;

	std::vector<MPBuffer*> bufferList;

	uint32_t memRequirements;
	VkDeviceSize sizeRequirement;

	bool solid;
	bool mapped;

	void* mapPointer;

	VkDeviceSize roundTo(VkDeviceSize size, VkDeviceSize multiple);

public:
	MemoryPool(DLPipeline* pipeline);
	~MemoryPool();

	void addBuffer(MPBuffer* buffer);
	void copyMemory(void* data_in, MPBuffer* memBuffer, VkDeviceSize dataSize);
	void mapMemory();
	void copyToMappedBuffer(MPBuffer* memBuffer, void* dataIn, VkDeviceSize dataSize);
	void solidifyMemoryPool(VkMemoryPropertyFlags flags);
	void convertStagedMemory(VkMemoryPropertyFlags flags);
	void destroyMemoryPool(bool destroyBuffers=true);

	MPBuffer* getBuffer(int index);
	void removeBuffer(MPBuffer* buffer, bool deleteBuffer=true);
	VkDeviceMemory& getMemory();
};