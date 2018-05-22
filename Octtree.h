#pragma once
#include"Collision.h"
 
// 0 Front Right Top
// 1 Front left  top
// 2 Back  Right Top
// 3 back  left  Top
// 4 Front right bottom
// 5 Front Left  Bottom
// 6 Back  right bottom
// 7 Back  left  bottom

enum LocationCode{
    bottomleftfront  = 5,   // (000),
    bottomrightfront = 4,   // (001), 
    bottomleftback   = 7,   // (010), 
    bottomrightback  = 6,   // (011),
                            //
    topleftfront     = 1,   // (100),
    toprightfront    = 0,   // (101),
    topleftback      = 3,   // (110),
    toprightback     = 2,   // (111).
};                          //

class CollisionSphere;

class Node{
public:
        Node(){}
        Node(Vec3 position, float size, int depth);
        
        Vec3  Position; // Position
        float Size;     // Dimensions
        int   Depth;    // How many subdivisions deep does this node go
        
        
        int  ID;      // possible future use
        bool IsLeaf; //  TRUE if Subnodes = nullptr 
        
        
        Node *ParentNode;
        Node *SubNode[8];  // ! FIND OUT HOW TO VIEW DYNAMIC ARRAYS IN DEBUGGER
        
        
        LocationCode Direction;
        std::vector<CollisionSphere *> Spheres;
        void Update(Node *node, CollisionSphere *ball);        
        bool IsContained     (CollisionSphere *sphere);
        void SubDivide       (int depth);
        void AddSphere       (CollisionSphere *Sphere);
        void RemoveSphere    (CollisionSphere *Sphere);
        void PushUp          (CollisionSphere *sphere);
        void PushDown        (LocationCode Direction,  CollisionSphere *sphere);
        Vec3 GetNewPosition  (int i, Vec3 Position);

 void InitRecursion(Node *node, CollisionSphere *ball);

static  int NumberOfNodes;
};


class OctTree{
public:
        OctTree(Vec3 position, float size, int depth);
        
        Vec3  Position;
        float Size;
        int   Depth;
        
        Node *Nodes;
        
        void Render(Node *CurrentNode);
        void Prune(Node* node);
        void Init();

static  std::vector<int> FreeID;


static Node* FindLocation(Node *node, CollisionSphere *ball);

static std::vector<std::vector<CollisionSphere *>*> NodeList;
};
