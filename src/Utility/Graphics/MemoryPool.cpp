#include "MemoryPool.h"
#include "DLPipeline.h"


void MPBuffer::createNewBuffer(DLPipeline* pipeline, VkDeviceSize size, VkBufferUsageFlags usage, VkBufferUsageFlags gpuUsage)
{
    

    if (buffer != nullptr)
    {
        throw std::runtime_error("Overwriting buffer!");
    }

    this->device = pipeline->device;
    this->size = size;
    this->usage = usage;
    this->gpuUsage = gpuUsage;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = this->size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferInfo.flags = 0; // default

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create buffer!");
    }
}


VkDeviceSize MemoryPool::roundTo(VkDeviceSize size, VkDeviceSize multiple)
{
    VkDeviceSize retSize = size;

    if (retSize % multiple != 0)
    {

        retSize = ((retSize / multiple) + 1) * multiple;
    }
    return retSize;
}

MemoryPool::MemoryPool(DLPipeline* pipeline)
{
    this->pipeline = pipeline;
	bufferList = std::vector<MPBuffer*>();
    solid = false;
    mapped = false;
    memRequirements = 0;
    sizeRequirement = 0;
    vkGetPhysicalDeviceProperties(pipeline->physicalDevice, &deviceLimits);
}

MemoryPool::~MemoryPool()
{

}

void MemoryPool::addBuffer(MPBuffer* buffer)
{
    if (solid)
        throw std::runtime_error("Cannot add buffer to solid memory pool!");


    VkMemoryRequirements requirements;
    vkGetBufferMemoryRequirements(pipeline->device, buffer->buffer, &requirements);

    sizeRequirement += roundTo(buffer->size, buffer->getBufferOffset());

    memRequirements |= requirements.memoryTypeBits;

    bufferList.push_back(buffer);
}

void MemoryPool::solidifyMemoryPool(VkMemoryPropertyFlags flags)
{
    if (solid)
        throw std::runtime_error("Already solid!");

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = sizeRequirement;
    allocInfo.memoryTypeIndex = pipeline->findMemoryType(memRequirements, flags);

    if (vkAllocateMemory(pipeline->device, &allocInfo, nullptr, &memory) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate memory!");
    }

    VkDeviceSize runningSize = 0;

    for (int i = 0; i < bufferList.size(); i++)
    {
        VkBuffer currentBuffer = bufferList[i]->buffer;

        if (vkBindBufferMemory(pipeline->device, currentBuffer, memory, runningSize) != VK_SUCCESS) // last arg is memory offset
        {
            throw std::runtime_error("failed to bind buffer!");
        }

        bufferList[i]->memLocation = runningSize;


        runningSize += roundTo(bufferList.at(i)->size, bufferList[i]->getBufferOffset());
    }

    solid = true;
}

void MemoryPool::copyMemory(void* dataIn, MPBuffer* memBuffer, VkDeviceSize dataSize)
{

    void* memPtr;
    if (vkMapMemory(pipeline->device, memory, memBuffer->memLocation, memBuffer->size, 0, &memPtr) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to map memory!");
    }
    memcpy(memPtr, dataIn, (size_t)dataSize);
    vkUnmapMemory(pipeline->device, memory);
}

void MemoryPool::mapMemory()
{

    if (vkMapMemory(pipeline->device, memory, 0, sizeRequirement, 0, &mapPointer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to map memory!");
    }
    mapped = true;
}

void MemoryPool::copyToMappedBuffer(MPBuffer* memBuffer, void* dataIn, VkDeviceSize dataSize)
{
    if (!mapped)
    {
        throw std::runtime_error("memory must be mapped!");
    }

    memcpy((void*)((uintptr_t)mapPointer + memBuffer->memLocation), dataIn, memBuffer->size);
}

void MemoryPool::convertStagedMemory(VkMemoryPropertyFlags flags)
{

    if (!solid)
        throw std::runtime_error("Memory pool must be solid!");

    //create new buffers and memory object
    VkDeviceMemory finalMemory;
    std::vector<MPBuffer*> finalBufferList = std::vector<MPBuffer*>();

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = sizeRequirement;
    allocInfo.memoryTypeIndex = pipeline->findMemoryType(memRequirements, flags);

    if (vkAllocateMemory(pipeline->device, &allocInfo, nullptr, &finalMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate memory!");
    }

    for (int i = 0; i < bufferList.size(); i++)
    {
        MPBuffer* tempBuffer = new MPBuffer();

        tempBuffer->createNewBuffer(pipeline, bufferList[i]->size, bufferList[i]->gpuUsage, bufferList[i]->gpuUsage);

        finalBufferList.push_back(tempBuffer);
    }

    // bind buffers
    VkDeviceSize runningSize = 0;

    for (int i = 0; i < finalBufferList.size(); i++)
    {

        vkBindBufferMemory(pipeline->device, finalBufferList[i]->buffer, finalMemory, runningSize); // last arg is memory offset

        finalBufferList[i]->memLocation = runningSize;

        runningSize += roundTo(bufferList[i]->size, finalBufferList[i]->getBufferOffset());

    }

    // copy buffers over
    VkCommandBuffer commandBuffer = pipeline->beginSingleTimeCommands();

    for (int i = 0; i < bufferList.size(); i++)
    {
        VkBufferCopy copyRegion{};
        copyRegion.size = bufferList[i]->size;
        vkCmdCopyBuffer(commandBuffer, bufferList.at(i)->buffer, finalBufferList[i]->buffer, 1, &copyRegion); //unsure if you can copy multiple buffers at a time with this

        
    }

    pipeline->endSingleTimeCommands(commandBuffer);

    for (int i = 0; i < bufferList.size(); i++)
    {
        bufferList[i]->destroyBuffer();
        *bufferList[i] = *finalBufferList[i];
        delete finalBufferList[i];
    }

    vkFreeMemory(pipeline->device, memory, nullptr);

    memory = finalMemory;
}

void MemoryPool::destroyMemoryPool(bool destroyBuffers)
{
    if (destroyBuffers)
    {
        for (int i = 0; i < bufferList.size(); i++)
        {
            bufferList[i]->destroyBuffer();
            delete bufferList[i];
        }
    }

	vkFreeMemory(pipeline->device, memory, nullptr);
}

MPBuffer* MemoryPool::getBuffer(int index)
{
    return bufferList.at(index);
}

void MemoryPool::removeBuffer(MPBuffer* buffer, bool deleteBuffer)
{
    for (int i = 0; i < bufferList.size(); i++)
    {
        if (bufferList.at(i) == buffer)
        {
            bufferList.erase(bufferList.begin() + i);
            if (deleteBuffer)
            {
                buffer->destroyBuffer();
                delete buffer;
            }
            return;
        }
    }
}

VkDeviceMemory& MemoryPool::getMemory()
{
    { return memory; }
}

