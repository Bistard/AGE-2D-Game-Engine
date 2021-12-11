#include "superMario.h"

using namespace AGE;

int main(int argc, char **argv)
{
    // SuperMarioEngine<AGE_ENHANCED_FPS> mario {AGE_ENHANCED_FPS, AGE_DEFAULT_WIN_WIDTH, AGE_DEFAULT_WIN_HEIGHT};
    // mario.run();

    Registry registry;
    Entity &player = registry.create();
    
    std::cout << registry.has<CVelocity>(player) << std::endl;
    registry.emplace<CVelocity>(player, 2.3f, -4.5f);
    std::cout << registry.has<CVelocity>(player) << std::endl;
    registry.emplace<CVelocity>(player, 2.3f, -4.5f);

    Entity &e1 = registry.create();
    registry.emplace<CVelocity>(e1, 0.0f, 0.0f);
    registry.emplace<CPosition>(e1, 1, 2);
    
    auto query1 = registry.query<CVelocity>();
    std::cout << "[query result: CVelocity]" << std::endl;
    for (auto &group : query1) {
        std::cout << "group: " << group.size() << std::endl;
    }

    auto query2 = registry.query<CPosition>();
    std::cout << "[query result: CPosition]" << std::endl;
    for (auto &group : query2) {
        std::cout << "group: " << group.size() << std::endl;
    }

    // FIXME
    // auto query3 = registry.query<CVelocity, CPosition>();
    // std::cout << "[query result: CPosition]" << std::endl;
    // for (auto &group : query3) {
    //     std::cout << "group: " << group.size() << std::endl;
    // }

}
