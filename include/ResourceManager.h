#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

// Simple generic resource manager for SFML resources
// Usage: ResourceManager<sf::Texture> textures; textures.get("path.png");

template <typename Resource>
class ResourceManager {
public:
    std::shared_ptr<Resource> get(const std::string& filename) {
        auto it = resources.find(filename);
        if (it != resources.end())
            return it->second;
        auto res = std::make_shared<Resource>();
        if (!res->loadFromFile(filename))
            throw std::runtime_error("Failed to load resource: " + filename);
        resources[filename] = res;
        return res;
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
};

#endif
