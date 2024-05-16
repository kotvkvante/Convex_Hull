#include "Graphics.h"
#include "../Math/Matrix.h"

int InitOpenGL(TCore* Core)
{

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to initialize OpenGL context.\n");
        return -1;
    }
    if(!LoadProgram(&Core->m_Graphics->program, FRAG("test"), VERT("test")))
    {
        printf("Failed load program: %s\n", "test");
        return -1;
    }
    InitProgram(&Core->m_Graphics->program);

    matrixOrtho(Core->m_Graphics->projectionMatrix, -1, 1, -1, 1, -5.0f, 5.0f);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, Core->m_Graphics->m_Width, Core->m_Graphics->m_Height);

    return 1;
}

int InitSDL(TCore* Core)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return -1;
    }
    Core->m_Graphics->m_Height = 768;
    Core->m_Graphics->m_Width  = 768;

    Core->m_Window = SDL_CreateWindow("Convex Hull",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      Core->m_Graphics->m_Width, Core->m_Graphics->m_Height,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (Core->m_Window == NULL)
    {
        return -1;
    }
    Core->m_Context = SDL_GL_CreateContext(Core->m_Window);
    if(Core->m_Context == NULL)
    {
        return -1;
    }
    return 1;
}

int CloseOpenGL(TCore* Core)
{
    glDeleteProgram(Core->m_Graphics->program.ID);
    free(Core->m_Graphics);
    return 1;
}

int CloseSDL(TCore* Core)
{
    SDL_GL_DeleteContext(Core->m_Context);
    SDL_DestroyWindow(Core->m_Window);
    SDL_Quit();

    return 1;
}

const float d = 0.02;
float Axis[] =
{
    -1, 0,
    1, 0,
    1, 0,
    1-d, 0+d,
    1, 0,
    1-d, 0-d,
};

void DrawGraphPoints(TCore* Core)
{
    TGraph* gh = Core->m_Graph;
    TGraphics* gs = Core->m_Graphics;

    glUseProgram(gs->program.ID);
    loadIdentity(gs->viewModelMatrix);

    glUniformMatrix4fv(gs->program.projectionLocation, 1, GL_FALSE, gs->projectionMatrix);
    glUniformMatrix4fv(gs->program.viewModelLocation, 1, GL_FALSE, gs->viewModelMatrix);
    glUniform3f(gs->program.colorLocation, 1.0f, 0.5f, 0.3f);

    glVertexAttribPointer(gs->program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , (float*)gh->m_Points);
    glEnableVertexAttribArray(gs->program.vertexLocation);

    glPointSize(4.0f);
    glDrawArrays(GL_POINTS, 0, gh->m_Count);
}

void DrawConvexHull(TCore* Core)
{
    TGraph* gh = Core->m_Graph;
    TGraphics* gs = Core->m_Graphics;
    glUseProgram(gs->program.ID);
    loadIdentity(gs->viewModelMatrix);
    glUniformMatrix4fv(gs->program.projectionLocation, 1, GL_FALSE, gs->projectionMatrix);
    glUniformMatrix4fv(gs->program.viewModelLocation, 1, GL_FALSE, gs->viewModelMatrix);
    glUniform3f(gs->program.colorLocation, 0.0f, 1.0f, 1.0f);

    glVertexAttribPointer(gs->program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , (float*)gh->m_Points);
    glEnableVertexAttribArray(gs->program.vertexLocation);

    glDrawElements(GL_LINE_LOOP, gh->m_CHCount, GL_UNSIGNED_INT, gh->m_CHIndices);

    glUniform3f(gs->program.colorLocation, 1.0f, 1.0f, 1.0f);
    glDrawElements(GL_POINTS, gh->m_CHCount, GL_UNSIGNED_INT, gh->m_CHIndices);
}

void DrawAxis(TGraphics* m_Graphics, float angle)
{
    glUseProgram(m_Graphics->program.ID);

    loadIdentity(m_Graphics->viewModelMatrix);
    matrixRotateZ(m_Graphics->viewModelMatrix, angle);

    glUniformMatrix4fv(m_Graphics->program.projectionLocation, 1, GL_FALSE, m_Graphics->projectionMatrix);
    glUniformMatrix4fv(m_Graphics->program.viewModelLocation, 1, GL_FALSE, m_Graphics->viewModelMatrix);
    glUniform3f(m_Graphics->program.colorLocation, 1.0f, 1.0f, 1.0f);

    glVertexAttribPointer(m_Graphics->program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , Axis);

    glEnableVertexAttribArray(m_Graphics->program.vertexLocation);
    glDrawArrays(GL_LINES, 0, 6);
}

void RenderFrame(TCore* Core)
{
    glClearColor ( 0.15f , 0.01f , 0.0f , 1.0f );
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    char us_c[16];
    // sprintf (us_c, "us: %I64u" , Core->m_Graph->m_MicroSeconds );
    sprintf (us_c, "us: %lu" , Core->m_Graph->m_MicroSeconds );
    DrawString(Core->m_Graphics, 0, 0, us_c, .6f, .6f, 1.0f);

    DrawAxis(Core->m_Graphics, 90);
    DrawAxis(Core->m_Graphics, 0);


    if(Core->m_Graph->m_CHShow)
        DrawConvexHull(Core);

    DrawGraphPoints(Core);


    SDL_GL_SwapWindow(Core->m_Window);
}



GLuint LoadFile(char* FileName, const GLchar** t)
{
    int len = 8000;
    const GLchar* text = malloc(len);
    memset( (char*)text, 0, len);

    FILE *f;
    f = fopen(FileName, "rb");
    if (!f)
    {
        printf("Error load file:\n%s\n", FileName);
        return -1;
    }
    fread( (char*)text, 1, 8000, f);
    *t = text;
    fclose(f);
    return 1;

}

GLuint LoadShader(char *FileName, GLuint type)
{
    const GLchar* text = NULL;

    if (LoadFile(FileName, &text) < 0)
        return -1;

    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &text, NULL);
    glCompileShader(shader);
    GLint ok;
    GLchar log[2000];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        glGetShaderInfoLog(shader, 2000, NULL, log);
        printf("Program log: %s\n", log);
    }

    free((char*)text);
    return shader;
}



int LoadProgram(TOpenGLProgram* program, char* frag, char* vert)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;
    // Load the vertex/fragment shaders


    vertexShader = LoadShader(vert, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(frag, GL_FRAGMENT_SHADER);
    // Create the program object
    program->ID = glCreateProgram();
    if(program->ID == 0)
        return -1;
    glAttachShader(program->ID, vertexShader);
    glAttachShader(program->ID, fragmentShader);

    // Link the program
    glLinkProgram(program->ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Check the link status
    glGetProgramiv(program->ID, GL_LINK_STATUS, &linked);
    if(!linked)
	{
	    GLint infoLen = 0;
	    glGetProgramiv(program->ID, GL_INFO_LOG_LENGTH, &infoLen);
	    if(infoLen > 1)
		{
		    char* infoLog = malloc(sizeof(char) * infoLen);
		    glGetProgramInfoLog(program->ID, infoLen, NULL, infoLog);
		    fprintf(stderr, "Error linking program:\n%s\n", infoLog);
		    free(infoLog);
		}

	    glDeleteProgram(program->ID);
	    return -1;
	}

	return 1;
}

void InitProgram(TOpenGLProgram* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->viewModelLocation = glGetUniformLocation(program->ID, "viewModel");
    program->colorLocation = glGetUniformLocation(program->ID, "color");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");
}

void ClientToOpenGL(TCore* Core, int x, int y, double *ox, double *oy, double *oz)
{
    int vp[4];
    double pMatrix[16];
    double mMatrix[16];

    //loadIdentity(mMatrix);
    float z;

    glGetIntegerv(GL_VIEWPORT, vp);
    y = vp[3] - y - 1;

    glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, pMatrix);

    copyMatrix_fd(Core->m_Graphics->projectionMatrix, pMatrix); // need? ...
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
    gluUnProject(x, y, z, mMatrix, pMatrix, vp, ox, oy, oz);
}
void DrawString(TGraphics* m_Graphics, float x, float y, char *text, float r, float g, float b)
{
    static char buffer[99999];
    int num_quads;

    num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));
    glUseProgram(m_Graphics->program.ID);

    loadIdentity(m_Graphics->viewModelMatrix);
    matrixScale(m_Graphics->viewModelMatrix, 0.015f, -0.015f, 1.0f);
    matrixTranslate(m_Graphics->viewModelMatrix, -1, 1, 0);

    glUniformMatrix4fv(m_Graphics->program.projectionLocation, 1, GL_FALSE, m_Graphics->projectionMatrix);
    glUniformMatrix4fv(m_Graphics->program.viewModelLocation, 1, GL_FALSE, m_Graphics->viewModelMatrix);
    glUniform3f(m_Graphics->program.colorLocation, r, g, b);

    glVertexAttribPointer(m_Graphics->program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 16 , buffer);

    glEnableVertexAttribArray(m_Graphics->program.vertexLocation);
    glDrawArrays(GL_QUADS, 0, num_quads*4);
}
