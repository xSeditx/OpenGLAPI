#pragma once


#include "Window.h"


class AABB{
public: 
    AABB(Vec2 points);



    void Merge(AABB other){
	     // const minA:Vector2 = a.m_centre.Sub( a.m_halfExtents );
	     // const maxA:Vector2 = a.m_centre.Add( a.m_halfExtents );
         // 
	     // const minB:Vector2 = b.m_centre.Sub( b.m_halfExtents );
	     // const maxB:Vector2 = b.m_centre.Add( b.m_halfExtents );
         // 
	     // const min:Vector2 = minA.Min(minB);
	     // const max:Vector2 = maxA.Max(maxB);
         // 
	     // const centre:Vector2 = min.Add(max).MulScalar(0.5);
	     // const halfExtents:Vector2 = max.Sub(min).MulScalar(0.5);
         // 
	     // return new AABB( centre, halfExtents );
    }


    static void Merge(AABB first, AABB second);
};