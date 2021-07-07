#include "Input.h"
#include "../Graph/Graph.h"
#include "../Math/GrahamAlg.h"

void HandleEvents(TCore* Core)
{
    int w, h;
    double ox, oy, oz;
    SDL_Event event;
    while ( SDL_PollEvent(&event) )
    {

        switch(event.type)
        {

        case SDL_QUIT:
            Core->m_IsRunning = False;
            break;

        case SDL_MOUSEBUTTONDOWN:
            w = event.button.x;
            h = event.button.y;

            ClientToOpenGL(Core, w, h, &ox, &oy, &oz);

            AddPoint(Core->m_Graph, (float)ox, (float)oy);
            Core->m_Graph->m_CHShow = False;
            Core->m_Graph->m_MicroSeconds = 0;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Core->m_IsRunning= False;
                break;
            case SDLK_1:
                PrintGraph(Core->m_Graph);
                break;
            case SDLK_2:
                math_grahmScan(Core->m_Graph);
                break;
            case SDLK_r:
                ResetGraph(Core->m_Graph);
                break;
            }
            break;
        }
    }
}


