#include "SceneManager.h"

int main()
{
    SceneManager::RunConfig cfg{};
#ifdef NDEBUG
    cfg.enableDebugUI = false;
#else
    cfg.enableDebugUI = true;
#endif
    cfg.windowed = true;

    SM().SetRunConfig(cfg);
    SM().Init();
    SM().Run();
    SM().Shutdown();

    return 0;
}