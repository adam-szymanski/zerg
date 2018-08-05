#pragma once

namespace Zerg {

template<typename Entity>
class NopCrosser {
public:
    Entity cross(const Entity& a, const Entity& b) {
        return a;
    }
};

}