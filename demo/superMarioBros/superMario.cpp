#include "superMario.h"

using namespace AGE;

int main(int argc, char **argv)
{
    SuperMarioEngine<AGE_ENHANCED_FPS> mario {AGE_ENHANCED_FPS, AGE_DEFAULT_WIN_WIDTH, AGE_DEFAULT_WIN_HEIGHT};
    mario.run();

    
    // std::cout << registry.has<CVelocity>(e0) << std::endl;
    // registry.emplace<CVelocity>(e0, 2.3f, -4.5f);
    // std::cout << registry.has<CVelocity>(e0) << std::endl;
    // registry.emplace<CVelocity>(e0, 4.5f, -2.3f);

    // Entity &e1 = registry.create();
    // registry.emplace<CVelocity>(e1, 0.0f, 0.0f);
    // registry.emplace<CPosition>(e1, 1, 2);
    
    // auto query1 = registry.query<CVelocity>();
    // std::cout << "[query result: CVelocity]" << std::endl;
    // for (auto &group : query1) {
    //     std::cout << "group: " << group->size() << std::endl;
    // }

    // auto query2 = registry.query<CPosition>();
    // std::cout << "[query result: CPosition]" << std::endl;
    // for (auto &group : query2) {
    //     std::cout << "group: " << group->size() << std::endl;
    // }

    // auto query3 = registry.query<CVelocity, CPosition>();
    // std::cout << "[query result: CVelocity CPosition]" << std::endl;
    // for (auto &group : query3) {
    //     std::cout << "group: " << group->size() << std::endl;
    // }

    // registry.remove<CVelocity>(e1);
    // auto query4 = registry.query<CVelocity>();
    // std::cout << "[query result: CVelocity]" << std::endl;
    // for (auto &group : query4) {
    //     std::cout << "group: " << group->size() << std::endl;
    // }

    // registry.destroy(e1);
    // auto query5 = registry.query<CVelocity, CPosition>();
    // std::cout << "[query result: CVelocity]" << std::endl;
    // for (auto &group : query5) {
    //     std::cout << "group: " << group->size() << std::endl;
    // }
}
