#ifndef GRAHAMALG_H_INCLUDED
#define GRAHAMALG_H_INCLUDED

#ifdef __unix__
  	#include <time.h>
#elif defined(_WIN32) || defined(WIN32)
	#include <sys/time.h>
#endif

#include "../Core/Core.h"
int math_grahmScan(TGraph*);

#endif // GRAHAMALG_H_INCLUDED
