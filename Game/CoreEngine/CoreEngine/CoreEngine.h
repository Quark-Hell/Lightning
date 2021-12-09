#pragma once

#include "pch.h" 
#include <vector>
#include "Graphic_Library.h"
#include "Graphic_Library.cpp"
#include "Physical_Library.h"
#include "Physical_Library.cpp"
#include "Main_Types.h"
#include "Main_Types.cpp"

using namespace std;

#ifdef COREENGINE_EXPORTS
#define COREENGINE_API extern "C" __declspec(dllexport)
#else
#define COREENGINE_API extern "C" __declspec(dllimport)
#endif

//---------------------------------Struct------------------------------------------------//



//---------------------------------Struct------------------------------------------------//

//---------------------------------Class------------------------------------------------//

extern "C" COREENGINE_API class GameObject;

//---------------------------------Class------------------------------------------------//

//---------------------------------Variables------------------------------------------------//

extern "C" COREENGINE_API vector<GameObject*> AllGameObjects;

//---------------------------------Variables------------------------------------------------//
