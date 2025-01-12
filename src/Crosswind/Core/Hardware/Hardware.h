#pragma once

class Hardware {

  public:
    Hardware() = default;
    virtual ~Hardware() = default;

    virtual void init() = 0;
    virtual void loop() = 0;

};
