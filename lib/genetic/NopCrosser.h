#ifndef LIB_GENETIC_NOP_CROSSER_H
#define LIB_GENETIC_NOP_CROSSER_H

namespace Zerg {

template<typename Entity>
class NopCrosser {
public:
    Entity cross(const Entity& a, const Entity& b) {
        return a;
    }
};

}

#endif