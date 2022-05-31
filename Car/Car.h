#pragma once
#include "V8Engine.h"

class CCar
{
public:
    CCar(std::unique_ptr<IEngine> &&engine)
        : m_engine(std::move(engine))
    {
    }
    CCar(IEngine *pEngine)
    {
        m_pEngine = pEngine;
    }

    void Drive();

private:
    std::unique_ptr<IEngine> m_engine;
    IEngine *m_pEngine;
};
