#pragma once
#include <memory>

class IEngine
{
public:
    IEngine(){};
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual ~IEngine() = default;
};

std::unique_ptr<IEngine> MakeV8Engine();