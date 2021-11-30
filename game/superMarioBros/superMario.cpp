#include "superMario.h"

int main(int argc, char **argv)
{
    AGE::SuperMarioEngine<AGE_ENHANCED_FPS> mario {AGE_ENHANCED_FPS, AGE_DEFAULT_WIN_WIDTH, AGE_DEFAULT_WIN_HEIGHT};
    mario.run();
}
