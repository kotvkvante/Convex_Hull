#include "Graph.h"

void AddPoint(TGraph* m_Graph, float x, float y)
{
    m_Graph->m_Points = realloc(m_Graph->m_Points, (m_Graph->m_Count + 1) * sizeof(TPoint));
    m_Graph->m_Points[m_Graph->m_Count].x = x;
    m_Graph->m_Points[m_Graph->m_Count].y = y;
    m_Graph->m_Count+=1;
}

void InitGraph(TGraph* m_Graph)
{
    m_Graph->m_Points = NULL;
    m_Graph->m_CHIndices = NULL;

    m_Graph->m_Count  = 0;
    m_Graph->m_CHCount = 0;

    m_Graph->m_CHShow = False;
    m_Graph->m_MicroSeconds = 0;
}

void PrintGraph(TGraph* m_Graph)
{
    printf("Graph:\n");
    for(int i = 0; i < m_Graph->m_Count; i++)
    {
        printf("[%d] %5.4f, %5.4f \n",i,  m_Graph->m_Points[i].x, m_Graph->m_Points[i].y);
    }
    printf("#\n");
}

void ResetGraph(TGraph* m_Graph)
{
    free(m_Graph->m_Points);
    free(m_Graph->m_CHIndices);
    m_Graph->m_Points = NULL;
    m_Graph->m_CHIndices = NULL;

    m_Graph->m_Count  = 0;
    m_Graph->m_CHCount = 0;

    m_Graph->m_CHShow = False;
    m_Graph->m_MicroSeconds = 0;
}

void CloseGraph(TCore* Core)
{
    free(Core->m_Graph->m_Points);
    free(Core->m_Graph->m_CHIndices);
    free(Core->m_Graph);
}
