#pragma once

#include <set>
#include <string>

class Service {
  
  public:
    Service() = default;
    virtual ~Service() = default;

    virtual std::string name() = 0;

    virtual std::set<std::string> dependsOn() {
      return std::set<std::string>();
    }

    virtual void init() = 0;
    virtual void loop() = 0;

};

#define GET_SERVICE_NAME(SVC) SVC::SERVICE_NAME
