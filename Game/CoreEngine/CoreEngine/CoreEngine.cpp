#pragma once

#include "pch.h" 
#include "CoreEngine.h"


using namespace std;

class GameObject {
	//------------------------------General Variables-----------------------------//
public:	Vector2 Position;
public:  Mesh MeshObject;
public:	string Tag;

	//------------------------------General Variables-----------------------------//

	//------------------------------Other Variables-----------------------------//
public:   __declspec(dllexport) static vector<GameObject*> AllGameObjects;
public:   SpriteObject* SpritePart;
public:   PhysicalObject* PhysicalPart;
	//------------------------------Other Variables-----------------------------//

	  __declspec(dllexport) void AddGraphics(
		  char texture = '#',
		  DWORD color = 15
	  ) {
		  //Initialization graphical part
		  SpritePart = new SpriteObject();
		  SpritePart->Texture = texture;
		  SpritePart->Color = color;
		  SpritePart->Mesh = &MeshObject;
		  SpritePart->Position = &Position;
	  }

	  __declspec(dllexport) void AddPhisics(
		  bool staticObject = false,
		  bool hasGravity = true,
		  Vector2 gravityVector = Vector2(0, -1),
		  bool hasCollision = true,
		  float mass = 0,
		  float friction = 1,
		  float buoyancy = 1,
		  float springAbility = 0) {
		  //Initialization physical part
		  PhysicalPart = new PhysicalObject();
		  PhysicalPart->Static = staticObject;
		  PhysicalPart->HasGravity = hasGravity;
		  PhysicalPart->GravityVector = gravityVector;
		  PhysicalPart->HasCollision = hasCollision;
		  PhysicalPart->Mass = mass;
		  PhysicalPart->Friction = friction;
		  PhysicalPart->Buoyancy = buoyancy;
		  PhysicalPart->SpringAbility = springAbility;
		  PhysicalPart->Mesh = &MeshObject;
		  PhysicalPart->Position = &Position;
	  }
	  GameObject(Mesh mesh = Mesh(),Vector2 positionObject = Vector2(0,0), string tag = "null") {
		  AllGameObjects.push_back(this);
		  MeshObject = mesh;
		  Position = positionObject;
		  Tag = tag;
	  }
};
vector<GameObject*> GameObject::AllGameObjects;
