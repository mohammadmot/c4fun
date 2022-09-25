#pragma once
#include <memory>
#include <iostream>
using namespace std;
class IEngine
{
public:
    IEngine(std::string strTitle)
    {
        m_strEngineTitle = strTitle;
    };
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual ~IEngine() = default;
    std::string GetTitle() { return m_strEngineTitle; }

protected:
    std::string m_strEngineTitle;
};

// std::unique_ptr<IEngine> MakeV8Engine();