#include "GrahamAlg.h"
#include <sys/time.h>

float math_rotateABC(const TPoint* A, const TPoint* B, const TPoint* C)
{
    return (B->x - A->x) * (C->y - B->y) - (B->y - A->y) * (C->x - B->x);
}

int math_comparePoints(TGraph* m_Graph, const TPoint* a, const TPoint* b)
{
    int tmp;
    //printf("1\n");
    tmp = math_rotateABC(&m_Graph->m_Points[0], a, b);
    if (tmp < 0)
        return 1;
    if (tmp > 0)
        return -1;
    return 0;
}

int math_grahmScan(TGraph* m_Graph)
{
    if(m_Graph->m_Count < 3)
        return -1;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);


    int* p = malloc(sizeof(int) * m_Graph->m_Count);
    for(int i = 0; i < m_Graph->m_Count; i++)
    {
        p[i] = i;
    }

    int tmp = 0;
    for(int i = 1; i < m_Graph->m_Count; i++)
    {
        if(m_Graph->m_Points[p[i]].x < m_Graph->m_Points[p[0]].x )
        {
            tmp = p[i];
            p[i] = p[0];
            p[0] = tmp;
        }
    }


    //qsort_s(p + 2, m_Graph->m_Count - 2, sizeof(TPoint), math_comparePoints, m_Graph);

    int j;
    for(int i = 2; i < m_Graph->m_Count; i++)
    {
        j = i;
        while( (j > 1) && (math_rotateABC(&m_Graph->m_Points[p[0]], &m_Graph->m_Points[p[j - 1] ], &m_Graph->m_Points[p[j] ]) < 0) )
        {
            tmp = p[j];
            p[j] = p[j-1];
            p[j-1] = tmp;
            j-=1;
        }
    }
    m_Graph->m_CHIndices = realloc(m_Graph->m_CHIndices  , sizeof(TPoint) * m_Graph->m_Count);
    for(int i = 0; i < m_Graph->m_Count; i++)
    {
        m_Graph->m_CHIndices[i] = 0;
    }
    m_Graph->m_CHCount = 2;
    m_Graph->m_CHIndices[0] = p[0];
    m_Graph->m_CHIndices[1] = p[1];

    for(int i = 2; i < m_Graph->m_Count; i++)
    {
        while(math_rotateABC(&m_Graph->m_Points[ m_Graph->m_CHIndices[m_Graph->m_CHCount - 2] ] ,
                             &m_Graph->m_Points[ m_Graph->m_CHIndices[m_Graph->m_CHCount - 1] ],
                             &m_Graph->m_Points[ p[i]          ] ) < 0)

        {

            m_Graph->m_CHCount--;
        }
        if( math_rotateABC(&m_Graph->m_Points[ m_Graph->m_CHIndices[m_Graph->m_CHCount - 2] ] ,
                             &m_Graph->m_Points[ m_Graph->m_CHIndices[m_Graph->m_CHCount - 1] ],
                             &m_Graph->m_Points[ p[i]          ]) == 0 )
        {
            m_Graph->m_CHCount--;
        }
        m_Graph->m_CHIndices[m_Graph->m_CHCount] = p[i];
        m_Graph->m_CHCount++;
    }

    m_Graph->m_CHIndices = realloc(m_Graph->m_CHIndices, m_Graph->m_CHCount * sizeof(int));
    m_Graph->m_CHShow = True;


    free(p);

    clock_gettime(CLOCK_MONOTONIC, &end);

    m_Graph->m_MicroSeconds = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    return 1;
}
