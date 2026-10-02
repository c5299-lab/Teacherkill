#pragma once
#include "raylib.h"

class GameContext;

class Scene
{
public:
    explicit Scene(GameContext* context) : gameContext(context) {}
    virtual ~Scene() = default;

    // ライフサイクル
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() const = 0;
    virtual void End() = 0;

    // 遷移管理
    bool IsFinished() const { return finished; }
    Scene* GetNextScene() const { return nextScene; }
    void SetNextScene(Scene* scene) { nextScene = scene; finished = true; }

    void SetGameContext(GameContext* context) { gameContext = context; }

protected:
    GameContext* gameContext = nullptr;
    Scene* nextScene = nullptr;
    bool finished = false;
};