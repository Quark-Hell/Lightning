#pragma once

#include "pch.h" 
#include <limits>
#include <math.h>
#include "Physical_Library.h"

using namespace std;

struct AABB
{
public: Vector2 Max;
public: Vector2 Min;

public:   __declspec(dllexport) AABB(Vector2 max = Vector2(), Vector2 min = Vector2()) {
          Max = max;
          Min = min;
      }
};

class PhysicalObject {
	friend void GravityUpdatePositionObject(int IndexObject);
    friend void SpringAbilityUpdatePositionObject(int IndexObject);
    friend void UpdatePositionObject(int IndexObject);
    friend AABB CreateAABB(int IndexObject);
	friend void CheckOverlapping(int IndexObject);
    friend bool ReturnObject(int IndexObject);
    friend void FinalStage(int IndexObject);

public:   __declspec(dllexport) static vector<PhysicalObject*> AllPhysicalObjects;
#pragma region Received parameters 
public:   bool Static;
public:   Vector2* Position;
public:   Mesh* Mesh;
public:   bool HasGravity;
public:   Vector2 GravityVector;
public:   bool HasCollision;
public:   float Mass;
public:   float Friction;
public:   float Buoyancy;
public:   float SpringAbility;
#pragma endregion

#pragma region Calculated Parameters 
public:   Vector2 CenterMass;
public:   float Velocity;
public:   vector<PhysicalObject*> HasOverlapping;
#pragma endregion

#pragma region Private Parameters
private:   Vector2 MotionVector;
private:   Vector2 OldPosition;
private:   AABB aabb;
#pragma endregion

public:   __declspec(dllexport) PhysicalObject() {
		  AllPhysicalObjects.push_back(this);
	  }
};
vector<PhysicalObject*> PhysicalObject::AllPhysicalObjects;

void GravityUpdatePositionObject(int IndexObject) {
    if (PhysicalObject::AllPhysicalObjects[IndexObject]->HasGravity == true) {
        PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.x -= PhysicalObject::AllPhysicalObjects[IndexObject]->GravityVector.x / Time::DeltaTime;
        PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.y -= (PhysicalObject::AllPhysicalObjects[IndexObject]->GravityVector.y + PhysicalObject::AllPhysicalObjects[IndexObject]->Mass) / Time::DeltaTime;
    }
}

AABB CreateAABB(int IndexObject)
{
    float maxX = FLT_MIN;
    float minX = FLT_MAX;

    float maxY = FLT_MIN;
    float minY = FLT_MAX;

    float maxZ = FLT_MIN;
    float minZ = FLT_MAX;

    for (int i = 0; i < PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices.size(); i++)
    {
#pragma region CalculateX
        if (PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].x > maxX)
        {
            maxX = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].x + PhysicalObject::AllPhysicalObjects[IndexObject]->Position->x;
        }
        if (PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].x < minX)
        {
            minX = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].x + PhysicalObject::AllPhysicalObjects[IndexObject]->Position->x;
        }
#pragma endregion

#pragma region CalculateY
        if (PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].y > maxY)
        {
            maxY = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].y + PhysicalObject::AllPhysicalObjects[IndexObject]->Position->y;
        }
        if (PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].y < minY)
        {
            minY = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].y + PhysicalObject::AllPhysicalObjects[IndexObject]->Position->y;
        }
#pragma endregion
    }
    PhysicalObject::AllPhysicalObjects[IndexObject]->aabb.Min = Vector2(minX, minY);
    PhysicalObject::AllPhysicalObjects[IndexObject]->aabb.Max = Vector2(maxX, maxY);

    return AABB(Vector2(minX, minY), Vector2(maxX, maxY));
}

bool TestAABBOverlap(int IndexObject, int HasOverlappingIndexObject, AABB* a, AABB* b)
{
    float d1x = b->Min.x - a->Max.x;
    float d1y = b->Min.y - a->Max.y;
    float d2x = a->Min.x - b->Max.x;
    float d2y = a->Min.y - b->Max.y;

    if (d1x > 0.0f || d1y > 0.0f)
    {
        return false;
    }
    if (d2x > 0.0f || d2y > 0.0f)
    {
        return false;
    }
    PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping.push_back(PhysicalObject::AllPhysicalObjects[HasOverlappingIndexObject]);
    return true;
}

void SpringAbilityUpdatePositionObject(int IndexObject) {
    if (abs(PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.y) <= abs(PhysicalObject::AllPhysicalObjects[IndexObject]->Mass * 10)) {

        PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.y = 0;
        return;
    }
    PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.y *= -PhysicalObject::AllPhysicalObjects[IndexObject]->SpringAbility;
}

void UpdatePositionObject(int IndexObject) {
    PhysicalObject::AllPhysicalObjects[IndexObject]->Position->x += PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.x;
    PhysicalObject::AllPhysicalObjects[IndexObject]->Position->y += PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.y;
}

bool ReturnObject(int IndexObject) {
    vector<Vector2> points;

    for (size_t i = 0; i < PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices.size(); i++)
    {
        Vector2 P = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i] + PhysicalObject::AllPhysicalObjects[IndexObject]->Position;

        for (size_t Object = 0; Object < PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping.size(); Object++)
        {
            for (size_t t = 0; t < PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Triangles.size(); t += 3)
            {
                Vector2 A = PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Triangles[t] + PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Position;
                Vector2 B = PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Triangles[t + 1] + PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Position;
                Vector2 C = PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Triangles[t + 2] + PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Position;

                float w1 = (A.x * (C.y - A.y) + (P.y - A.y) * (C.x - A.x) - P.x * (C.y - A.y)) / ((B.y - A.y) * (C.x - A.x) - (B.x - A.x) * (C.y - A.y));
                float w2 = (P.y - A.y - w1 * (B.y - A.y)) / (C.y - A.y);

                //If in triangle
                if (w1 >= 0 && w2 >= 0 && w1 + w2 <= 1)
                {
                    //Searching farthest edges
                    for (size_t pOfEdge = 0; pOfEdge < PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Edges.size(); pOfEdge += 2)
                    {
                        Vector2 vec;
                        vec.x = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].x + PhysicalObject::AllPhysicalObjects[IndexObject]->Position->x + PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.x;
                        vec.y = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i].y + PhysicalObject::AllPhysicalObjects[IndexObject]->Position->y + PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector.y;

                        Vector2 edge1[2];
                        edge1[0] = PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Edges[pOfEdge] + PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Position;
                        edge1[1] = PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Mesh->Edges[pOfEdge + 1] + PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping[Object]->Position;

                        Vector2 edge2[2];
                        edge2[0] = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i] + PhysicalObject::AllPhysicalObjects[IndexObject]->Position;
                        edge2[1] = vec;

                        Vector2 intersectPoint;
                        if (Vector2::Intersect(edge1[1], edge1[0], edge2[0],edge2[1], intersectPoint)) {
                            Vector2 subtraction = PhysicalObject::AllPhysicalObjects[IndexObject]->Mesh->Vertices[i] + PhysicalObject::AllPhysicalObjects[IndexObject]->Position;
                            points.push_back(intersectPoint - subtraction);
                        }
                    }
                }
            }
        }
    }
    if (points.size() == 1) {
        PhysicalObject::AllPhysicalObjects[IndexObject]->MotionVector += points[0];

        return true;
    }
    else if (points.size() == 0) {
        return false;
    }
    else
    {
        Vector2 nearthestPoint = Vector2(FLT_MAX, FLT_MAX);
        for (size_t i = 0; i < points.size(); i++)
        {
            if (abs(points[i].x) <= abs(nearthestPoint.x) && abs(points[i].y) <= abs(nearthestPoint.y))
            {
                nearthestPoint = points[i];
            }
        }
        PhysicalObject::AllPhysicalObjects[IndexObject]->Position->x += nearthestPoint.x;
        PhysicalObject::AllPhysicalObjects[IndexObject]->Position->y += nearthestPoint.y ;

        return true;
    }
}

void CheckOverlapping(int IndexObject) {

    for (size_t i = 0; i < PhysicalObject::AllPhysicalObjects.size(); i++)
    {
        CreateAABB(i);
    }

start_check:
    for (int i = 0; i < PhysicalObject::AllPhysicalObjects.size(); i++)
    {
        if (PhysicalObject::AllPhysicalObjects[IndexObject] != PhysicalObject::AllPhysicalObjects[i])
        {
            if (TestAABBOverlap(IndexObject,i,&PhysicalObject::AllPhysicalObjects[IndexObject]->aabb, &PhysicalObject::AllPhysicalObjects[i]->aabb))
            {
                if (ReturnObject(IndexObject)) {
                    SpringAbilityUpdatePositionObject(IndexObject);
                }
            }
        }
    }

	PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping.push_back(PhysicalObject::AllPhysicalObjects[IndexObject]);
}

void FinalStage(int IndexObject) {
    PhysicalObject::AllPhysicalObjects[IndexObject]->HasOverlapping.clear();
}


class UpdatePhysics {
public:   __declspec(dllexport) static bool Update() {
    for (size_t i = 0; i < PhysicalObject::AllPhysicalObjects.size(); i++)
    {
        if (PhysicalObject::AllPhysicalObjects[i]->Static == false) {
            GravityUpdatePositionObject(i);
            if (PhysicalObject::AllPhysicalObjects[i]->HasCollision == true) {
                CheckOverlapping(i);
            }

            UpdatePositionObject(i);
            FinalStage(i);
        }
    }
    return true;
}
};