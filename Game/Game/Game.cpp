#include <iostream>
#include "Game.h"
#include "CoreEngine.h"
#include "CoreEngine.cpp"

using namespace std;

class Game {
public:
    void InitializeObjects() {
        class CreateObject {
        public: void CreateObject1() {
            Vector2 positionObject;
            positionObject.x = 10;
            positionObject.y = 10;

#pragma region Initialize Mesh
            Mesh mesh;

            Vector2 vertices1;
            vertices1.x = -4;
            vertices1.y = 4;

            Vector2 vertices2;
            vertices2.x = 4;
            vertices2.y = 4;

            Vector2 vertices3;
            vertices3.x = -4;
            vertices3.y = -4;

            Vector2 vertices4;
            vertices4.x = 4;
            vertices4.y = -4;

            mesh.Triangles.push_back(vertices1);
            mesh.Triangles.push_back(vertices2);
            mesh.Triangles.push_back(vertices3);

            mesh.Triangles.push_back(vertices2);
            mesh.Triangles.push_back(vertices3);
            mesh.Triangles.push_back(vertices4);

            mesh.Vertices.push_back(vertices1);
            mesh.Vertices.push_back(vertices2);
            mesh.Vertices.push_back(vertices3);
            mesh.Vertices.push_back(vertices4);

            mesh.GenerateEdges();
#pragma endregion

            GameObject* cube = new GameObject(mesh,positionObject);
            cube->AddGraphics('#', FOREGROUND_RED);
            cube->AddPhisics(false, true, Vector2(0, -1), true, 0.1, 1, 1, 0.5);
        }
        public: void CreateObject2() {
            Vector2 positionObject;
            positionObject.x = 10;
            positionObject.y = 40;

#pragma region Initialize Mesh
            Mesh mesh;

            Vector2 vertices1;
            vertices1.x = -4;
            vertices1.y = 2;

            Vector2 vertices2;
            vertices2.x = 60;
            vertices2.y = 2;

            Vector2 vertices3;
            vertices3.x = -4;
            vertices3.y = -2;

            Vector2 vertices4;
            vertices4.x = 60;
            vertices4.y = -2;

            mesh.Triangles.push_back(vertices1);
            mesh.Triangles.push_back(vertices2);
            mesh.Triangles.push_back(vertices3);

            mesh.Triangles.push_back(vertices2);
            mesh.Triangles.push_back(vertices3);
            mesh.Triangles.push_back(vertices4);

            mesh.Vertices.push_back(vertices1);
            mesh.Vertices.push_back(vertices2);
            mesh.Vertices.push_back(vertices3);
            mesh.Vertices.push_back(vertices4);

            mesh.GenerateEdges();
#pragma endregion

            GameObject* terrain = new GameObject(mesh,positionObject);
            terrain->AddGraphics('#', FOREGROUND_RED);
            terrain->AddPhisics(true, false, Vector2(0, -1), true, 1, 1, 1, 0);
        }
        };
        CreateObject* createObject = new CreateObject;
        createObject->CreateObject1();
        createObject->CreateObject2();
    }
};

int main()
{
    ConsoleInfo::SetCharachterSize(20,20);
    ConsoleInfo::ShowConsoleCursor(false);
    ConsoleInfo::ResetConsoleColour();
    SpriteObject::AllSpriteObjects.clear();
    PhysicalObject::AllPhysicalObjects.clear();

    Camera camera(Vector2(80,80));

    int SizeX = 80;
    int SizeY = 40;
    ScreenClass(SizeX,SizeY);

    Game *game = new Game;
    game->InitializeObjects();

    ConsoleInfo::ShowConsoleCursor(false);

    while (true)
    {
        Time::UpdateDeltaTime();
        UpdatePhysics::Update();
        Draw::RenderFrame(camera);
    }
}
