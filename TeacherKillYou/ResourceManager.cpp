#include "ResourceManager.h"
#include "raylib.h"

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

// ゲーム全体で使うモデルをキーと一緒に登録しておく
void ResourceManager::LoadAll() {
    LoadModel(ResourceKeys::Model_Player, "Data/Image/greenman.glb");

	LoadModel(ResourceKeys::Model_Stage1, "Data/Image/free_loft_18_mini_office_v.optimization.glb");
    // 他のモデルが増えたらここに追加
    // LoadModel(ResourceKeys::Model_Stage, "Data/Image/stage.glb");
}

void ResourceManager::LoadModel(const std::string& key, const std::string& path) {
    // すでに登録済みならロードしない（二重ロード防止）
    if (models_.find(key) != models_.end()) {
        return;
    }

    Model model = ::LoadModel(path.c_str());
    models_[key] = model;
}

// キーでモデルを取得（どのクラスからでも呼べる）
Model ResourceManager::GetModel(const std::string& key) const {
    auto it = models_.find(key);
    if (it != models_.end()) {
        return it->second;
    }
    return Model{}; // 見つからない場合は空のモデル
}

void ResourceManager::UnloadAll() {
    for (auto& pair : models_) {
        ::UnloadModel(pair.second);
    }
    models_.clear();
}