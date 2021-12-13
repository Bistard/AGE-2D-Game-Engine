#include "superMario.h"

using namespace AGE;

int main(int argc, char **argv)
{
    SuperMarioEngine<AGE_ENHANCED_FPS> mario {AGE_ENHANCED_FPS, AGE_DEFAULT_WIN_WIDTH, AGE_DEFAULT_WIN_HEIGHT};
    mario.run();
}
