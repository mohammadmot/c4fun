#include "IEngine.h"

class CV8Engine : public IEngine
{
public:
    CV8Engine(std::string strTitle) : IEngine(strTitle)
    {
    }

    void Start() override
    {
        cout << m_strEngineTitle << " Starts Driving...\r\n";
    }
    void Stop() override
    {
        cout << m_strEngineTitle << " Stops Driving...\r\n";
    }
};

class CLexusEngine : public IEngine
{
public:
    CLexusEngine(std::string strTitle) : IEngine(strTitle)
    {
    }
    void Start() override
    {
        cout << m_strEngineTitle << " Starts Driving...\r\n";
    }
    void Stop() override
    {
        cout << m_strEngineTitle << " Stops Driving...\r\n";
    }
};
/*
std::unique_ptr<IEngine> MakeV8Engine()
{
    return std::make_unique<CV8Engine>();
}
IEngine *MakeV8EngineEx()
{
    return (new CV8Engine("V8 Lancrusier"));
}
*/