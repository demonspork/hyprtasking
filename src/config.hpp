#pragma once

#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprutils/math/Vector2D.hpp>

#include "globals.hpp"

namespace HTConfig {

inline Hyprlang::CConfigValue* get_config_value_compat(const std::string& config) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    auto* value = HyprlandAPI::getConfigValue(PHANDLE, config);
#pragma GCC diagnostic pop
    return value;
}

template<typename T>
concept ptr_type = std::same_as<T, Hyprlang::STRING>;

template<ptr_type T>
inline T value(std::string config) {
    static std::unordered_map<std::string, T const*> cache;

    if (!cache.count(config))
        cache[config] = (T const*)get_config_value_compat("plugin:hyprtasking:" + config)->getDataStaticPtr();
    return *cache[config];
}

template<typename T>
inline T value(std::string config)
    requires(!ptr_type<T>)
{
    static std::unordered_map<std::string, T* const*> cache;

    if (!cache.count(config))
        cache[config] = (T* const*)get_config_value_compat("plugin:hyprtasking:" + config)->getDataStaticPtr();
    return **cache[config];
}

} // namespace HTConfig
