/*
 * Copyright (c) 2012 Tom Alexander
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */
#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include "def.h"
#include "topaz.h"
#include "collider.h"
#include "sphere_primitive.h"
#include "sqt.h"

namespace topaz
{
    class aabb_collider;
    class sphere_collider : public collider
    {
      public:
        sphere_collider(sqt* _parent_transform, const vec & _offset, float _radius);
        ~sphere_collider();

        virtual point* is_colliding_with(collider* other);
        void set_visible(bool _visible);
        point get_world_position();
        
        #if DRAW_COLLISION_SOLIDS == 1
        virtual void display_as_colliding(bool colliding);
        #endif

      private:
        point* sphere_collision(sphere_collider* other);
        point* AABB_collision(aabb_collider* other);
        float radius;
        bool visible;
        sphere_primitive* draw_sphere;
        sqt* transform;
    };
}

#endif
