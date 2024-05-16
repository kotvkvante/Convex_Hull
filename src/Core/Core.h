#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#define True 1
#define False 0

#include <glad/glad.h>
#ifdef __unix__
    #include <SDL2/SDL.h>
    #include <GL/glu.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <SDL.h>
    #include <GL/glu.h>
#endif

#include "../SideSrc/stb_easy_font.h"

#include <stdio.h>
#include <sys/time.h>

#define SHADER_FOLDER "shaders/"
#define SHADER_VERT ".vert"
#define SHADER_FRAG ".frag"
#define VERT(a) SHADER_FOLDER a SHADER_VERT
#define FRAG(a) SHADER_FOLDER a SHADER_FRAG

typedef struct
{
    float x, y;
} TPoint;

typedef struct
{
    GLuint ID;
    GLuint projectionLocation;
    GLuint viewModelLocation;
    GLuint vertexLocation;
    GLuint colorLocation;
} TOpenGLProgram;

typedef struct
{
    TOpenGLProgram program;
    float projectionMatrix[16];
    float viewModelMatrix[16];
    int m_Height, m_Width;
} TGraphics;

typedef struct
{
    int m_Count;
    TPoint* m_Points;
    int* m_CHIndices; // CH Convex Hull
    int m_CHCount;
    int m_CHShow;
    uint64_t m_MicroSeconds;
} TGraph;

typedef struct
{
    int m_IsRunning;
    TGraphics* m_Graphics;
    TGraph* m_Graph;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
} TCore;

int InitCore(TCore*);
int CloseCore(TCore*);

#endif // CORE_H_INCLUDED
