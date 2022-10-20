#include <SFML/Graphics.hpp>
#include "Framework/Framework.h"

int main()
{
    FRAMEWORK->Init(1280, 720);
    FRAMEWORK->Do();
    FRAMEWORK->~Framework();
    return 0;
}