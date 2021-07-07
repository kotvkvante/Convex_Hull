#include "Core.h"
#include "../Graphics/Graphics.h"
#include "../Graph/Graph.h"

int InitCore(TCore* Core)
{
    Core->m_IsRunning = False;

    Core->m_Graphics = malloc(sizeof(TGraphics));
    if(InitSDL(Core) < 0)
    {
        printf("Error while init SDL\n");
        return -1;
    }

    if(InitOpenGL(Core) < 0)
    {
        printf("Error while init Open GL\n");
        return -1;
    }
    Core->m_Graph = malloc(sizeof(TGraph));

    InitGraph(Core->m_Graph);


    Core->m_IsRunning = True;
    return 1;
}


int CloseCore(TCore* Core)
{
    CloseGraph(Core);

    if(CloseOpenGL(Core) < 0)
    {
        printf("Failed to close OpenGL\n");
        return -1;
    }
    if(CloseSDL(Core) < 0)
    {
        printf("Failed to close SDL\n");
        return -1;
    }

    return 1;

}
