#pragma once

#include "pch.h" 
#include <iostream>
#include <fstream>
#include <thread>
#include "Graphic_Library.h"

using namespace std;

class Camera {
public:
    COORD CameraPos;

    Camera(Vector2 cameraPos) {
        CameraPos.X = cameraPos.x;
        CameraPos.Y = cameraPos.x;
    }
};

static class ScreenClass {

public:__declspec(dllexport) static int SizeX;
public:__declspec(dllexport) static int SizeY;

public:
    __declspec(dllexport) ScreenClass(int sizeX,int sizeY) {
        ScreenClass::SizeX = sizeX;
        ScreenClass::SizeY = sizeY;
    }
};
int ScreenClass::SizeX;
int ScreenClass::SizeY;

class SpriteObject {
public:   __declspec(dllexport) static vector<SpriteObject*> AllSpriteObjects;
public:   Mesh* Mesh;
public:   Vector2* Position;
public:   char Texture;
public:   DWORD Color;
public:   string Tag = "null";

    SpriteObject() {
        AllSpriteObjects.push_back(this);
    }
};
vector<SpriteObject*> SpriteObject::AllSpriteObjects;

static class ConsoleInfo {
public:
    __declspec(dllexport) static WORD Attributes;
public:
    __declspec(dllexport) static COORD GetConsoleCursorPosition()
    {
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hCon, &csbi))
        {
            return csbi.dwCursorPosition;
        }
        else
        {
            // The function failed. Call GetLastError() for details.
            COORD invalid = { 0, 0 };
            return invalid;
        }
    }

public:
    __declspec(dllexport) static LPTSTR ReadConsoleOut(COORD coord) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        LPTSTR lpCharacter = new TCHAR[1];
        DWORD dwReaden = 0;
        ReadConsoleOutputCharacter(hCon, lpCharacter, 1, GetConsoleCursorPosition(), &dwReaden);
        return lpCharacter;
    }

public:
    __declspec(dllexport) static bool SetCursorPosition(COORD coord) {
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hCon, coord);
        return true;
    }

public:
    __declspec(dllexport) static bool SetConsoleColour(DWORD Colour) {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        SetConsoleTextAttribute(hStdout, Colour);

        return true;
    }

public:
    __declspec(dllexport) static bool ResetConsoleColour() {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        SetConsoleTextAttribute(hStdout, 15);

        return true;
    }

public:
    __declspec(dllexport) static bool SetCharachterSize(int sizeX, int sizeY) {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = sizeX;                   // Width of each character in the font
        cfi.dwFontSize.Y = sizeY;                  // Height
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        return true;
    }

public:
    __declspec(dllexport) static bool ShowConsoleCursor(bool showFlag)
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO     cursorInfo;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);

        return true;
    }
};
WORD ConsoleInfo::Attributes;

static class Draw {
public:
    __declspec(dllexport) static void SetConsoleColour(DWORD Colour)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &Info);
        SetConsoleTextAttribute(hStdout, Colour);
    }

public:
    __declspec(dllexport) static bool RenderFrame(Camera camera) {
        for (size_t y = 0; y <= ScreenClass::SizeY; y++)
        {
            string row;
            Vector2 currentPos;

            for (size_t x = 0; x <= ScreenClass::SizeX; x++)
            {
                bool IsDraw = false;//Костыль

                currentPos.x = x;
                currentPos.y = y;
                
                for (size_t z = 0; z < SpriteObject::AllSpriteObjects.size(); z++)
                {
                    if (IsDraw == true) {
                        break;
                    }
                    for (size_t t = 0; t < SpriteObject::AllSpriteObjects[z]->Mesh->Triangles.size(); t += 3)
                    {
                        Vector2 A = SpriteObject::AllSpriteObjects[z]->Mesh->Triangles[t] + SpriteObject::AllSpriteObjects[z]->Position;
                        Vector2 B = SpriteObject::AllSpriteObjects[z]->Mesh->Triangles[t + 1] + SpriteObject::AllSpriteObjects[z]->Position;
                        Vector2 C = SpriteObject::AllSpriteObjects[z]->Mesh->Triangles[t + 2] + SpriteObject::AllSpriteObjects[z]->Position;
                        Vector2 P = currentPos;

                        float w1 = (A.x*(C.y - A.y)+(P.y - A.y)*(C.x-A.x)-P.x*(C.y-A.y)) / ((B.y - A.y)*(C.x - A.x)-(B.x-A.x)*(C.y-A.y));
                        float w2 = (P.y - A.y - w1 * (B.y - A.y)) / (C.y - A.y);                 

                        if (w1 >= 0 && w2 >= 0 && w1 + w2 <= 1)
                        {
                            IsDraw = true;//Костыль
                            row.push_back(SpriteObject::AllSpriteObjects[z]->Texture);
                            break;
                        }
                    }
                }
                if (IsDraw == false)
                {
                    row.push_back(((char)*" "));
                }
            }
            ConsoleInfo::SetCursorPosition({ static_cast<SHORT>(currentPos.x), static_cast<SHORT>(currentPos.y) });
            fputs(row.c_str(), stdout);
        }
        return true;
    }

public:
    __declspec(dllexport) static bool ClearScreen(char fill = ' ') {
        COORD tl = { 0,0 };
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        SetConsoleCursorPosition(console, tl);
        return true;
    }

public:
    __declspec(dllexport) static void DrawString(string Texture, COORD coord = ConsoleInfo::GetConsoleCursorPosition(), DWORD Color = 0) {
        SetConsoleColour(Color);
        ConsoleInfo::SetCursorPosition(coord);
        printf("%s", Texture.c_str());
    }
public:
    __declspec(dllexport) static void EraseString(COORD StartCoord, COORD EndCoord) {

        for (int i = 0; i < EndCoord.X - StartCoord.X; i++)
        {
            COORD coord;
            coord.X = StartCoord.X + i;
            coord.Y = StartCoord.Y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            printf(" ");
        }
    }
};