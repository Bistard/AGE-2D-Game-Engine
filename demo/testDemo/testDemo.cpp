#include "testDemo.h"

using namespace AGE;

int main(int argc, char **argv)
{
    TestDemo<AGE_ENHANCED_FPS> demo {AGE_ENHANCED_FPS, AGE_DEFAULT_WIN_WIDTH, AGE_DEFAULT_WIN_HEIGHT};
    demo.run();
}
