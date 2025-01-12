#pragma once

#include <exception>
#include <string>

class InvalidAlertPriorityException : std::exception {

  public:
    InvalidAlertPriorityException(const std::string& message) : message(message) {}

    virtual char const* what() const noexcept {
      return message.c_str ();
    }

  private:
    std::string message;

};
