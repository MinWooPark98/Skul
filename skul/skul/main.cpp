#include <SFML/Graphics.hpp>
#include "Framework/Framework.h"

int main()
{
    Framework framework(1920, 1080);
    framework.Init();
    framework.Do();
    return 0;
}