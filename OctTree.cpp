#include"Octtree.h"

std::vector<int> OctTree::FreeID;
int Node::NumberOfNodes = 0;
std::vector<std::vector<CollisionSphere *>*> OctTree::NodeList;

int RecursionCounter = 0;

Node::Node (Vec3 position, float size, int depth)
    : Position(position),
      Size(size),
      Depth(depth),
      SubNode(),
      ID(NumberOfNodes++),
      IsLeaf(false)
{
    if(Depth <= 0)
    {
        IsLeaf = true;
      return;
    }

    *SubNode = new Node[8];
    for_loop(SubCount, 8){
        SubNode[SubCount] = new Node(GetNewPosition(SubCount, Position),Size * .5, Depth - 1);
        SubNode[SubCount]->ParentNode = this;
        SubNode[SubCount]->Direction = (LocationCode)SubCount;
    }

    OctTree::NodeList.push_back(&Spheres);
}
OctTree::OctTree (Vec3 position, float size, int depth)
{
    Nodes = nullptr;
    Nodes = new Node(position,size,depth);
}


void OctTree::Prune (Node *node){

    if(node != nullptr)
    {
        for_loop(i, 8)
        {
            if(node->SubNode[i] != nullptr) Prune(node->SubNode[i]);
            delete(node->SubNode[i]);
            node->SubNode[i] = nullptr;
        }
    }
}
void OctTree::Init ()
{
    // MUST BUILD THE INITIAL TREE, THIS NEEDS TO BE CALLED AFTER THE CREATION OF THE COLLISION SPHERES
    Print("Init Has Not Been Completed");
   for_loop(counter, MaxObjects){
       FreeID.push_back(counter);
   }


    for_loop(Index, CollisionSphere::Collision_ObjectCount)   
    {
       // Nodes->InitRecursion(Nodes, Collider[Index]);
       Node *N = FindLocation(Nodes, Collider[Index]);
       if(N != nullptr) N->AddSphere(Collider[Index]);
    }

//   static std::vector< CollisionSphere* > Collision_ObjectList;
  
 //  static unsigned int  Collision_ObjectCount;

}




Node* OctTree::FindLocation(Node *node, CollisionSphere *ball)
{
// It is a leaf and see if current ball fits
   for_loop(SubIndex,8){
       if(node->SubNode[SubIndex]->IsLeaf == true)
       {
           if(node->SubNode[SubIndex]->IsContained(ball) == true)
           {
                return node;
           }
       }
       else
       {
           FindLocation(node->SubNode[SubIndex], ball);
       }
   }
   return nullptr;
}




void OctTree::Render (Node *CurrentNode)
{
    if(CurrentNode == nullptr) return;

   
    glTranslatef(Position.x, Position.y, Position.z);
    float size = CurrentNode->Size;
    size /= 2.0f;

    for_loop(Count, 8){
            Vec3 Quadrent;
            Quadrent = CurrentNode->Position;
            glBegin( GL_LINES);

             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z - size); // BACK
             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z - size); // I BELIEVE THIS IS WRONG
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z - size);

             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z - size); // LEFT
             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z - size);

             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z + size);// FRONT
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z + size);

             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z - size);


             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z + size);
                
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z + size); // RIGHT
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z + size);
                        
             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z + size); // TOP
             glVertex3f( Quadrent.x -  size,  Quadrent.y -  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z - size);
             glVertex3f( Quadrent.x +  size,  Quadrent.y -  size,  Quadrent.z + size);
               
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z - size);// BOTTOM
             glVertex3f( Quadrent.x +  size,  Quadrent.y +  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z + size);
             glVertex3f( Quadrent.x -  size,  Quadrent.y +  size,  Quadrent.z - size);
        
            glEnd(); 

        Render(CurrentNode->SubNode[Count]);
    }

}


Vec3 Node::GetNewPosition (int i, const Vec3 pos)
{
    Vec3 newPos = pos;
    if ((i & 4) == 4)
    {
        newPos.y += (Size * .25);
    }
    else
    {
        newPos.y -= (Size * .25);
    }
    if ((i & 2) == 2)
    {
        newPos.x += (Size * .25);
    }
    else
    {
        newPos.x -= (Size * .25);
    }
    if ((i & 1) == 1)
    {
        newPos.z += (Size * .25);
    }
    else
    {
        newPos.z -= (Size * .25);
    }
    return newPos;
}
void Node::SubDivide (int depth)
{
    IsLeaf = false;
   *SubNode = new Node[8];
    for_loop(SubCount, 8){
        SubNode[SubCount] =  new Node(GetNewPosition(SubCount, Position),Size * .5, Depth - 1);
        SubNode[SubCount]->Direction = (LocationCode)SubCount;
        SubNode[SubCount]->Depth = depth;
        if(depth > 0)
        {
            SubNode[SubCount]->IsLeaf = false;
            SubNode[SubCount]->SubDivide(depth - 1);
        }
    }
}
bool Node::IsContained(CollisionSphere *sphere)
{
    return (sphere->Body.Position.x < (Position.x + (Size * .5)) && sphere->Body.Position.x > (Position.x - (Size * .5)) &&
            sphere->Body.Position.y < (Position.y + (Size * .5)) && sphere->Body.Position.y > (Position.y - (Size * .5)) &&
            sphere->Body.Position.z < (Position.z + (Size * .5)) && sphere->Body.Position.z > (Position.z - (Size * .5)));
}

void Node::AddSphere (CollisionSphere *sphere)
{
    sphere->OctTreeNode = this;
    sphere->OctTreeID = Spheres.size();
    Spheres.push_back(sphere);
}
void Node::RemoveSphere (CollisionSphere *sphere)
{
    Print("Node::RemoveSphere  Has not been completed");
}

void Node::PushUp (CollisionSphere *sphere)
{
   sphere->OctTreeNode = sphere->OctTreeNode->Node::ParentNode;
}
void Node::PushDown (LocationCode direction, CollisionSphere *sphere)
{
   sphere->OctTreeNode = sphere->OctTreeNode->SubNode[direction];
}

void Node::Update(Node *node, CollisionSphere *ball)
{
//It is a leaf and see if current ball fits
 for_loop(SubIndex,8){
     if(node->SubNode[SubIndex]->IsLeaf == true)
     {
         if(node->SubNode[SubIndex]->IsContained(ball) == true)
         {
             node->SubNode[SubIndex]->AddSphere(ball);
         }
     }
     else
     {
         Update(node->SubNode[SubIndex], ball);
     }
 }
}








//
//
//
//void Node::InitRecursion(Node *node, CollisionSphere *ball)
//{
//// It is a leaf and see if current ball fits
//   for_loop(SubIndex,8){
//       if(node->SubNode[SubIndex]->IsLeaf == true)
//       {
//           if(node->SubNode[SubIndex]->IsContained(ball) == true)
//           {
//               node->SubNode[SubIndex]->AddSphere(ball);
//           }
//       }else{
//           InitRecursion(node->SubNode[SubIndex], ball);
//       }
//   }
//}
//
//

// for_loop(Index, CollisionSphere::Collision_ObjectCount)
// {
//
//     for_loop(SubIndex,8){
//      //   if(IsLeaf == false)
//      //   {
//         // It is a Leaf Now Check if the Sphere is Contained in it....
//             if(SubNode[SubIndex]->IsContained(Collider[Index]) == true)
//             {
//                 if(Depth != 0){
//                     RecursionCounter++;
//                     InitRecursion(SubNode[SubIndex], Collider[Index]);
//                 }
//                 else
//                 {
//                     SubNode[SubIndex]->AddSphere(Collider[Index]);
//                 }
//             } 
//             
//        // }
//     }
// }