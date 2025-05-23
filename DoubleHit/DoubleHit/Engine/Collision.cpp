/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Collision.h"
#include "GameObject.h"


CS230::RectCollision::RectCollision(Math::irect boundary, GameObject* object) :
    boundary(boundary),
    object(object)
{ }

Math::rect CS230::RectCollision::WorldBoundary() {
    return {
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point_1),
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point_2)
    };
}

void CS230::RectCollision::Draw(Math::TransformationMatrix display_matrix) {
    const double render_height = rlGetFramebufferHeight();

    Math::rect world_boundary = WorldBoundary();

    Math::vec2 bottom_left = display_matrix * Math::vec2{ world_boundary.Left(), world_boundary.Bottom() };
    Math::vec2 bottom_right = display_matrix * Math::vec2{ world_boundary.Right(), world_boundary.Bottom() };
    Math::vec2 top_left = display_matrix * Math::vec2{ world_boundary.Left(), world_boundary.Top() };
    Math::vec2 top_right = display_matrix * Math::vec2{ world_boundary.Right(), world_boundary.Top() };

    bottom_left.y = bottom_left.y * -1 + render_height;
    bottom_right.y = bottom_right.y * -1 + render_height;
    top_left.y = top_left.y * -1 + render_height;
    top_right.y = top_right.y * -1 + render_height;

    DrawLine(int(top_left.x), int(top_left.y), int(top_right.x), int(top_right.y), WHITE);
    DrawLine(int(bottom_right.x), int(bottom_right.y), int(top_right.x), int(top_right.y), WHITE);
    DrawLine(int(bottom_right.x), int(bottom_right.y), int(bottom_left.x), int(bottom_left.y), WHITE);
    DrawLine(int(top_left.x), int(top_left.y), int(bottom_left.x), int(bottom_left.y), WHITE);
}

bool CS230::RectCollision::IsCollidingWith(GameObject* other_object) {
    Collision* other_collider = other_object->GetGOComponent<Collision>();


    if (other_collider == nullptr) {
        return false;
    }

    Math::rect rectangle_1 = WorldBoundary();

    //rect collides with circle
    if (other_collider->Shape() == CollisionShape::Circle) {
        Math::vec2 circle_position = dynamic_cast<CircleCollision*>(other_collider)->ChangeCollision();
        return IsCollidingWith(circle_position);
    }

    Math::rect rectangle_2 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();

    if (rectangle_1.Right() >= rectangle_2.Left() &&
        rectangle_1.Left() <= rectangle_2.Right() &&
        rectangle_1.Top() >= rectangle_2.Bottom() &&
        rectangle_1.Bottom() <= rectangle_2.Top()) {
        return true;
    }
    return false;
}

bool CS230::RectCollision::IsCollidingWith(Math::vec2 point)
{
    Math::rect rectangle_1 = WorldBoundary();

    if (rectangle_1.Right() >= point.x &&
        rectangle_1.Left() <= point.x &&
        rectangle_1.Top() >= point.y &&
        rectangle_1.Bottom() <= point.y) {
        return true;
    }
    return false;
}


double CS230::RectCollision::ChangeCollision()
{
    Math::rect rectangle_1 = WorldBoundary();

    return (rectangle_1.Right() - rectangle_1.Left()) / 2;
}


CS230::CircleCollision::CircleCollision(double radius, GameObject* object) :
    radius(radius),
    object(object)
{ }

double CS230::CircleCollision::GetRadius()
{
    Math::TransformationMatrix matrix = object->GetMatrix();

    double scaleX = std::sqrt(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1]);
    double scaleY = std::sqrt(matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1]);

    double avgScale = (scaleX + scaleY) / 2.0;

    return radius * avgScale;
}

Math::vec2 CS230::CircleCollision::ChangeCollision()
{
    return Math::vec2(object->GetPosition());
}

void CS230::CircleCollision::Draw(Math::TransformationMatrix display_matrix) {
    const double render_height = rlGetFramebufferHeight();
    Math::vec2 transformed_position = display_matrix * object->GetPosition();
    transformed_position.y = transformed_position.y * -1 + render_height;
    const int num_segments = 36;
    Math::vec2 previous_vertex;
    for (int i = 0; i <= num_segments + 1; i++) {
        double theta = 2.0 * PI * static_cast<double>(i) / static_cast<double>(num_segments);
        Math::vec2 vertex = {
            transformed_position.x + GetRadius() * std::cos(theta),
            transformed_position.y + GetRadius() * std::sin(theta)
        };
        if (i > 0) {
            DrawLine(int(vertex.x), int(vertex.y), int(previous_vertex.x), int(previous_vertex.y), WHITE);
        }
        previous_vertex = vertex;
    }
}

bool CS230::CircleCollision::IsCollidingWith(GameObject* other_object)
{
    Collision* other_collider = other_object->GetGOComponent<Collision>();
    double radi;
    double dx;
    double dy;

    if (other_collider == nullptr) {
        return false;
    }
    if (other_collider->Shape() != CollisionShape::Circle) {

        //Engine::GetLogger().LogError("c");
        //radi = dynamic_cast<RectCollision*>(other_object->GetGOComponent<Collision>())->ChangeCollision();
        dx = object->GetPosition().x - other_object->GetPosition().x;
        dy = object->GetPosition().y - (other_object->GetPosition().y + other_object->GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2);

        //circle collides with rect
        if (other_collider->Shape() == CollisionShape::Rect) {
            Math::rect rectangle_1 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();

            //distance between boundary and circle position
            dx = std::max(rectangle_1.Left(), std::min(rectangle_1.Right(), object->GetPosition().x));
            dy = std::max(rectangle_1.Bottom(), std::min(rectangle_1.Top(), object->GetPosition().y));

            float distanceX = object->GetPosition().x - dx;
            float distanceY = object->GetPosition().y - dy;

            double distance = distanceX * distanceX + distanceY * distanceY;

            double sum_of_squared_radii = (GetRadius()) * (GetRadius());

            return distance <= sum_of_squared_radii;
        }
    }
    else {
        radi = dynamic_cast<CircleCollision*>(other_object->GetGOComponent<Collision>())->GetRadius();
        dx = object->GetPosition().x - other_object->GetPosition().x;
        dy = object->GetPosition().y - other_object->GetPosition().y;
    }

    double distance = dx * dx + dy * dy;

    double sum_of_squared_radii = (GetRadius() + radi) * (GetRadius() + radi);

    return distance <= sum_of_squared_radii;
}


bool CS230::CircleCollision::IsCollidingWith(Math::vec2 point)
{
    double dx = object->GetPosition().x - point.x;
    double dy = object->GetPosition().y - point.y;
    double distance = dx * dx + dy * dy;

    return distance <= GetRadius();
}
