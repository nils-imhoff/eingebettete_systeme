#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H
#include <cstddef>
#include <cstdint>

#define CREATE(varName, blockCount, blockSize) \
  PoolAllocator<blockSize, blockCount> varName

class IHeap {
 public:
  virtual void* Allocate(size_t sizeInBytes) = 0;
  virtual void Deallocate(void*) = 0;
  virtual size_t Available() const = 0;
};

// IMPLEMENTATION
template <size_t blockSize, size_t blockCount>
class PoolAllocator : IHeap {
 public:
  void* Allocate(size_t sizeInBytes) {
    if (sizeInBytes > blockSize) {
      return nullptr;
    }

    for (size_t i = 0; i < blockCount; ++i) {
      if (blocksUsed[i] == false) {
        blocksUsed[i] = true;
        --availableBlocks;
        return static_cast<void*>(data[i]);
      }
    }

    return nullptr;
  }

  void Deallocate(void* deallocateThis) {
    if (deallocateThis == nullptr || deallocateThis < data[0] ||
        deallocateThis >= data[blockCount - 1] ||
        (static_cast<uint8_t*>(deallocateThis) - data[0]) % blockSize != 0) {
      return;
    }

    size_t deallocIndex =
        (static_cast<uint8_t*>(deallocateThis) - data[0]) / blockSize;
    for (size_t i = 0; i < blockSize; ++i) {
      data[deallocIndex][i] = 0;
    }
    blocksUsed[deallocIndex] = false;
    ++availableBlocks;
  }

  size_t Available() const { return availableBlocks * blockSize; }

 private:
  uint8_t data[blockCount][blockSize]{};
  bool blocksUsed[blockCount]{};
  size_t availableBlocks{blockCount};
};
#endif
