#include "Partition.h"

// Read using the partition file descriptor API.
ssize_t Partition::read(Partition& partition, void* buf, size_t count) {
  ssize_t bytes_read = -1;

  size_t bytes_to_read = count;
  if (partition.file_position + bytes_to_read > partition.size()) {
    bytes_to_read = partition.size() - partition.file_position;
  }

  if (bytes_to_read > 0) {
    partition.read(partition.file_position, static_cast<uint8_t*>(buf), bytes_to_read);
    bytes_read = bytes_to_read;
    partition.file_position += bytes_read;
  }

  return bytes_read;
}

// Write using the partition file descriptor API.
ssize_t Partition::write(Partition& partition, const void* buf, size_t count) {
  ssize_t bytes_written = -1;

  size_t bytes_to_write = count;
  if (partition.file_position + bytes_to_write > partition.size()) {
    bytes_to_write = partition.size() - partition.file_position;
  }

  if (bytes_to_write > 0) {
    partition.write(partition.file_position, static_cast<const uint8_t*>(buf), bytes_to_write);
    bytes_written = bytes_to_write;
    partition.file_position += bytes_written;
  }

  return bytes_written;
}

// Seek the file pointer using the partition file descriptor API.
ssize_t Partition::seek(Partition& partition, ssize_t offset, int whence) {
  ssize_t fpos = -1;

  switch(whence) {
    case SEEK_SET: {
      if (offset < partition.size()) {
        partition.file_position = offset;
        fpos = partition.file_position;
      }
    } break;

    case SEEK_CUR: {
      if ((partition.file_position + offset) < partition.size()) {
        partition.file_position += offset;
        fpos = partition.file_position;
      }
    } break;

    case SEEK_END: {
      if ((partition.size() + offset) < partition.size()) {
        partition.file_position = (partition.size() + offset);
        fpos = partition.file_position;
      }
    } break;
  }

  return fpos;
}
