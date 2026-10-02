#pragma once
#include "Scene.h"

class GameScene final : public Scene
{
public:
    explicit GameScene(GameContext* context) : Scene(context) {}

    void Init() override;
    void Update(float deltaTime) override;
    void Render() const override;
    void End() override;
};