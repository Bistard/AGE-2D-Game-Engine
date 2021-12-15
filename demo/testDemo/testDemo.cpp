#include "testDemo.h"

#include <cstring>

using namespace AGE;

int main(int argc, char *argv[])
{
    if (argc >= 2 && strcmp(argv[1], "enhanced") == 0) {
        TestDemo<AGE_ENHANCED_FPS> demo {AGE_ENHANCED_FPS, 100, 40};
        demo.run();
    } else {
        TestDemo<AGE_DEFAULT_FPS> demo {AGE_DEFAULT_FPS, AGE_DEFAULT_WIN_WIDTH, AGE_DEFAULT_WIN_HEIGHT};
        demo.run();
    }
    
}
