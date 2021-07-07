#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "../Core/Core.h"

void InitGraph(TGraph*);
void CloseGraph(TCore*);
void AddPoint(TGraph*, float , float);
void PrintGraph(TGraph*);
void ResetGraph(TGraph*);
#endif // GRAPH_H_INCLUDED
