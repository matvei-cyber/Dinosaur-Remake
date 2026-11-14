#pragma once
#include "raylib.h"
#include <cmath>


struct Vec2
{
    float x, y;


    Vec2 () : x (0.0f), y (0.0f) {}
    Vec2 (float x, float y) : x (x), y (y) {}


    Vec2 operator+ (const Vec2& other) const
    {
        return Vec2 {x + other.x, y + other.y};
    }


    void operator+= (const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }


    Vec2 operator- (const Vec2& other) const
    {
        return Vec2 {x - other.x, y - other.y};
    }


    void operator-= (const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
    }


    Vec2 operator* (const float num) const
    {
        return Vec2 {x * num, y * num};
    }


    void operator*= (const float num)
    {
        x *= num;
        y *= num;
    }


    float length () const
    {
        return sqrtf ((x * x) + (y * y));
    }


    Vec2 normalize () const
    {
        float len = length ();

        if (len == 0.0f)
        {
            return Vec2 {0.0f, 0.0f};

        } else
        {
            return Vec2 {x / len, y / len};
        }
    }


    void normalize_strict ()
    {
        float len = length ();

        if (len == 0.0f)
        {
            x = 0.0f;
            y = 0.0f;

        } else
        {
            x /= len;
            y /= len;
        }
    }
};


namespace Engine
{
    struct Player
    {
        Vec2 position;
        float speed_y = 0.0f;
        float speed_x;
        float jump_force;
        float size;


        Player () : position (0.0f, 0.0f), speed_x (0.0f), jump_force (0.0f), size (0.0f) {}
        Player (const Vec2& position, const float speed_x, const float jump_force, const float size) : position (position), speed_x (speed_x), jump_force (jump_force), size (size) {}


        void draw (const Color& player_color)
        {
            DrawRectangleV (Vector2 {position.x, position.y}, Vector2 {size, size}, player_color);
        }
    };


    struct Ground
    {
        float height;


        Ground () : height (0.0f) {}
        Ground (float height) : height (height) {}


        void draw (const Vec2& screen, const Color& ground_color) const
        {
            DrawRectangleV (Vector2 {0, screen.y - height}, Vector2 {screen.x, height}, ground_color);
        }
    };


    namespace Physics
    {
        inline void move_player (const Vec2& screen_size, const float& ground_height, const float& gravity, Vec2& position, const float& player_size, const float& speed_x, float& speed_y, const float& jump_force)
        {
            float dt = GetFrameTime ();
            float ground_level = screen_size.y - ground_height - player_size;
            speed_y += gravity * dt;


            if (IsKeyDown (KEY_A))
            {
                position.x -= speed_x * dt;
            }

            if (IsKeyDown (KEY_D))
            {
                position.x += speed_x * dt;
            }


            if (position.y == ground_level)
            {
                if (IsKeyPressed (KEY_SPACE))
                {
                    speed_y -= jump_force;
                }
            }


            position.y += speed_y * dt;

            
            if (position.x < 0.0f)
            {
                position.x = 0.0f;
            }

            if (position.x > (screen_size.x - player_size))
            {
                position.x = screen_size.x - player_size;
            }

            if (position.y < 0.0f)
            {
                position.y = 0.0f;
                speed_y = 0.0f;
            }

            if (position.y > ground_level)
            {
                position.y = ground_level;
                speed_y = 0.0f;
            }
        }
    }


    namespace Graphics
    {
        inline void start_game (const Vec2& screen)
        {
            SetConfigFlags (FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
            InitWindow (screen.x, screen.y, "My game");
        }


        inline void end_game ()
        {
            CloseWindow ();
        }
    }
}