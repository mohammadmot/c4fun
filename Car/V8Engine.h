#include "IEngine.h"

class CV8Engine : public IEngine
{
public:
    void Start() override
    { /* start the engine */
    }
    void Stop() override
    { /* stop the engine */
    }
};

std::unique_ptr<IEngine> MakeV8Engine()
{
    return std::make_unique<CV8Engine>();
}
IEngine *MakeV8EngineEx()
{
    return (new CV8Engine());
}
