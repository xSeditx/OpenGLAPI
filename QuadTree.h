#pragma once
#include"Collision.h"
#include"Vertex.h"
//#include"glm.hpp"
//typedef glm::vec2 Vec2;
//typedef glm::vec3 Vec3;
//typedef glm::vec4 Vec4;
//typedef glm::mat4 Matrix4;
//
enum Direction
{
    NE = 0,
    SE = 1,
    NW = 2,
    SW = 3,
};

class CollisionSphere;
class Node
{
public:
        Node(){}
       ~Node();
        Node(Vec2 Position, Vec2 size);
       
        Vec2 Position;
        Vec2 Size;
       
        Node *SubNodes[4];
       
        int Capacity;
        bool IsLeaf;
        Direction Facing;
       
        std::vector<CollisionSphere *> Entities;
       
        void Subdivide();
        void Render();
        Vec2 NewPos(Vec2 pos, Direction dir);
       
        bool PushDown   (CollisionSphere *Object);
        void Moveup     (CollisionSphere *Object);
       
        bool Insert     (CollisionSphere *object);
        bool IsContained(CollisionSphere *object);
        void Prune(Node *node);

        bool Node::Intersects(Vec2 position, Vec2 size);

std::vector<CollisionSphere*> Node::QueryRange(Vec2 position, Vec2 size);
};


class QT{
public:
        QT(){}
       ~QT(){}
        QT(Vec2 Position, Vec2 size);
        Vec2 Position;
        Vec2 Size;
        Node *RootNode;
        void Init();
        void Update();
};