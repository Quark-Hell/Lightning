#pragma once

#include "pch.h" 
#include <cmath>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

#ifdef MAINTYPES_API_EXPORTS
#define MAINTYPES_API extern "C" __declspec(dllexport)
#else
#define MAINTYPES_API extern "C" __declspec(dllimport)
#endif

//---------------------------------Struct------------------------------------------------//



//---------------------------------Struct------------------------------------------------//

//---------------------------------Class------------------------------------------------//

extern "C" MAINTYPES_API class Vector2;

extern "C" MAINTYPES_API class Mesh;

extern "C" MAINTYPES_API class Time;

//---------------------------------Class------------------------------------------------//

//---------------------------------Variables------------------------------------------------//



//---------------------------------Variables------------------------------------------------//
