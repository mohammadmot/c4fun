#include <iostream>
#include "Car.h"
using namespace std;

void CCar::Drive()
{
    m_engine->Start();
    // drive
    m_engine->Stop();

    if (m_pEngine)
    {
        m_pEngine->Start();
        cout << "Car can Drive with V8Engine...\r\n";
        m_pEngine->Start();
    }
}

int main()
{
    CCar m_pCar(MakeV8EngineEx());
    m_pCar.Drive();
    return 0;
}