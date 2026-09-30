#pragma once
#include <string>
#include <unordered_map>
#include "raylib.h"
#include "ResourceKeys.h"

class ResourceManager {
public:
    static ResourceManager& GetInstance();

    // キーとパスを指定してモデルをロード・登録する
    void LoadModel(const std::string& key, const std::string& path);

    // キーを指定してどこからでもモデルを取得する
    Model GetModel(const std::string& key) const;

    // 全モデルの一括ロード／一括解放
    void LoadAll();
    void UnloadAll();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, Model> models_;
};

// ショートカット関数
inline ResourceManager& RM() {
    return ResourceManager::GetInstance();
}