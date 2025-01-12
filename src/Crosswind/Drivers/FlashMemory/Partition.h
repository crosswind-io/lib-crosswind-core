#pragma once

#include "PartitionType.h"

#include <sys/types.h>
#include <unistd.h>
#include <string>

class Partition {

  public:
    Partition() = default;
    virtual ~Partition() = default;

    virtual std::string name() const = 0;
    virtual uint32_t address() const = 0;
    virtual size_t size() const = 0;
    virtual PartitionType type() const = 0;
    virtual uint32_t number () const = 0;

    // Read multiple bytes from the partition at the specified offset.
    virtual void read(size_t offset, uint8_t* buf, size_t count) const = 0;

    // Write multiple bytes to the partition at the specified offset.
    virtual void write(size_t offset, const uint8_t* buf, size_t count) const = 0;

    // Erase a section of the partition.
    virtual void erase(size_t offset, size_t count) const = 0;

    // Read using the partition file descriptor API.
    static ssize_t read(Partition& partition, void* buf, size_t count);
    // Write using the partition file descriptor API.
    static ssize_t write(Partition& partition, const void* buf, size_t count);
    // Seek the file pointer using the partition file descriptor API.
    static ssize_t seek(Partition& partition, ssize_t offset, int whence);

    // Read an object from the partition at the specified offset.
    template <typename T>
    T& get(size_t offset, T& t) const {
      read(offset, reinterpret_cast<uint8_t*>(&t), sizeof(T));
      return t;
    }

    // Write an object to the partition at the specified offset.
    template <typename T>
    const T& put(size_t offset, const T& t) const {
      write(offset, reinterpret_cast<const uint8_t*>(&t), sizeof(T));
      return t;
    }

  protected:
    size_t file_position = 0;

};
