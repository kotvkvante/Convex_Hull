#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "../Core/Core.h"



int InitSDL(TCore*);
int InitOpenGL(TCore*);

int CloseSDL(TCore*);
int CloseOpenGL(TCore*);

void RenderFrame(TCore*);
void DrawString(TGraphics* m_Graphics, float x, float y, char *text, float r, float g, float b);

void UpdateGraphicsWinSize(TCore*);
void ClientToOpenGL(TCore*, int, int, double*, double*, double*);

// Load stuff functions
GLuint LoadShader(char*, GLuint);
GLuint LoadFile(char*, const GLchar**);
int LoadProgram(TOpenGLProgram*, char*, char*);

void InitProgram(TOpenGLProgram*);


#endif // GRAPHICS_H_INCLUDED
