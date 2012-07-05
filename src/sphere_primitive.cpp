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
#include "sphere_primitive.h"
#include "topaz.h"
#include "camera.h"
#include "model.h"

namespace topaz
{
    sphere_primitive::sphere_primitive(sqt* _parent_transform, const vec & _color)
    {
        transform = new sqt(_parent_transform);
        color = _color;
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(sqt* _parent_transform, const vec & _color, int milliseconds)
    {
        transform = new sqt(_parent_transform);
        time_left = milliseconds;
        color = _color;
        add_pre_draw_function(id, std::bind(&topaz::sphere_primitive::update, this, std::placeholders::_1));
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(const point & position, float scale, const vec & _color)
    {
        transform = new sqt();
        transform->translateXYZ(position.x(), position.y(), position.z());
        transform->scale(scale);
        color = _color;
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(const point & position, float scale, const vec & _color, int milliseconds)
    {
        transform = new sqt();
        transform->translateXYZ(position.x(), position.y(), position.z());
        transform->scale(scale);
        color = _color;
        time_left = milliseconds;
        add_pre_draw_function(id, std::bind(&topaz::sphere_primitive::update, this, std::placeholders::_1));
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(sqt* _parent_transform)
    {
        transform = new sqt(_parent_transform);
        color = vec(1.0f, 1.0f, 1.0f, 1.0f);
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(sqt* _parent_transform, float scale, const vec & _color)
    {
        transform = new sqt(_parent_transform);
        color = _color;
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        transform->scale(scale);
    }

    sphere_primitive::sphere_primitive(sqt* _parent_transform, int milliseconds)
    {
        transform = new sqt(_parent_transform);
        time_left = milliseconds;
        color = vec(1.0f, 1.0f, 1.0f, 1.0f);
        add_pre_draw_function(id, std::bind(&topaz::sphere_primitive::update, this, std::placeholders::_1));
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(const point & position, float scale)
    {
        transform = new sqt();
        transform->translateXYZ(position.x(), position.y(), position.z());
        transform->scale(scale);
        color = vec(1.0f, 1.0f, 1.0f, 1.0f);
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    sphere_primitive::sphere_primitive(const point & position, float scale, int milliseconds)
    {
        transform = new sqt();
        transform->translateXYZ(position.x(), position.y(), position.z());
        transform->scale(scale);
        color = vec(1.0f, 1.0f, 1.0f, 1.0f);
        time_left = milliseconds;
        add_pre_draw_function(id, std::bind(&topaz::sphere_primitive::update, this, std::placeholders::_1));
        add_draw_function(id, std::bind(&topaz::sphere_primitive::draw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }



    sphere_primitive::~sphere_primitive()
    {
        delete transform;
    }

    void sphere_primitive::draw(const matrix & V, const matrix & P, camera* C)
    {
        matrix M = transform->to_matrix();
        sphere_model->prep_for_draw(M, V, P, C, sphere_model->model_program, NULL);
        glUniform4fv(sphere_model->model_program->uniform_locations["RGBA"], 1, &(color[0]));
        sphere_model->draw();
    }

    void sphere_primitive::update(int milliseconds)
    {
        time_left -= milliseconds;
        if (time_left <= 0)
            add_to_grim_reaper(this);
    }
}
