#include "src/Core/Core.h"
#include "src/Graphics/Graphics.h"
#include "src/Input/Input.h"

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <wchar.h>

TCore Core;

int main(int argc, char** argv)
{
    if(InitCore(&Core) < 0)
    {
        printf("Error while init Core\n");
        return -1;
    }
    printf("###\nConvex hull of a shape is the smallest convex set that contains it.\n###\n");


    while (Core.m_IsRunning)
    {
        HandleEvents(&Core);
        RenderFrame(&Core);
    }
    printf(">Thx<\n");
    return 1;
}

