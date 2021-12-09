#pragma once

#include "pch.h" 
#include "Main_Types.h"
#include "Main_Types.cpp"

using namespace std;

#ifdef PHYSICALLIBRARY_API_EXPORTS
#define PHYSICALLIBRARY_API extern "C" __declspec(dllexport)
#else
#define PHYSICALLIBRARY_API extern "C" __declspec(dllimport)
#endif

/*---------------------------------Struct------------------------------------------------*/



/*---------------------------------Struct------------------------------------------------*/

/*---------------------------------Class------------------------------------------------*/

extern "C" PHYSICALLIBRARY_API class PhysicalObject;

extern "C" PHYSICALLIBRARY_API class UpdatePhysics;

/*---------------------------------Class------------------------------------------------*/

/*---------------------------------Variables------------------------------------------------*/

extern "C" PHYSICALLIBRARY_API vector<PhysicalObject*> AllPhysicalObjects;

/*---------------------------------Variables------------------------------------------------*/