#pragma once
#include "V8Engine.h"

class CCar
{
public:
    CCar(std::unique_ptr<IEngine> &&engine)
        : m_engine(std::move(engine))
    {
        m_pEngine = NULL;
    }

    CCar(IEngine *pEngine) : m_pEngine(std::move(pEngine)){};
    void Drive();

private:
    std::unique_ptr<IEngine> m_engine;
    IEngine *m_pEngine;
};
