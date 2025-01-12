#pragma once

#include <exception>
#include <string>

class PartitionWriteException : std::exception {

  public:
    PartitionWriteException(const std::string& message) : message(message) {}

    virtual char const* what() const noexcept {
      return message.c_str ();
    }

  private:
    std::string message;

};
