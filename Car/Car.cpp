#include "Car.h"

void CCar::Drive()
{
    if (m_engine)
    {
        m_engine->Start();
        cout << "Car with " << m_engine->GetTitle() << " Engine Moves ...\r\n";
        m_engine->Stop();
    }

    if (m_pEngine)
    {
        m_pEngine->Start();
        cout << "Car with " << m_pEngine->GetTitle() << " Engine Moves ...\r\n";
        m_pEngine->Stop();
    }
}

int main()
{
    /*
    CCar m_pV8Car(new CV8Engine("V8"));
    m_pV8Car.Drive();
    cout << "------------------" << endl;
    CCar m_pLexus(new CLexusEngine("Lexus"));
    m_pLexus.Drive();
    */
    CCar m_pV8(std::make_unique<CV8Engine>("V8"));
    m_pV8.Drive();
    CCar m_pLexus(std::make_unique<CLexusEngine>("Lexus"));
    m_pLexus.Drive();
    return 0;
}