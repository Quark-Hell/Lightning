#pragma once

#include "pch.h" 
#include "Main_Types.h"
#include "Main_Types.cpp"

using namespace std;

#ifdef GRAPHICLIBRARY_EXPORTS
#define GRAPHICLIBRARY_API extern "C" __declspec(dllexport)
#else
#define GRAPHICLIBRARY_API extern "C" __declspec(dllimport)
#endif

//---------------------------------Struct------------------------------------------------//



//---------------------------------Struct------------------------------------------------//

//---------------------------------Class------------------------------------------------//

extern "C" GRAPHICLIBRARY_API class Mesh;

extern "C" GRAPHICLIBRARY_API class SpriteObject;

extern "C" GRAPHICLIBRARY_API class ScreenClass;

extern "C" GRAPHICLIBRARY_API class ConsoleInfo;

extern "C" GRAPHICLIBRARY_API class Camera;

extern "C" GRAPHICLIBRARY_API class Draw;

//---------------------------------Class------------------------------------------------//

//---------------------------------Variables------------------------------------------------//

#pragma region ConsoleInfo Variables

extern "C" GRAPHICLIBRARY_API WORD Attributes;

#pragma endregion

#pragma region Screen Variables

extern "C" GRAPHICLIBRARY_API int SizeX;

extern "C" GRAPHICLIBRARY_API int SizeY;

#pragma endregion

#pragma region Camera Variables

extern "C" GRAPHICLIBRARY_API Vector2 CameraPos;

#pragma endregion

extern "C" GRAPHICLIBRARY_API vector<SpriteObject*> AllSpriteObjects;

//---------------------------------Variables------------------------------------------------//