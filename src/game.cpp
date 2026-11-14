#include "engine.h"

const Vec2 screen_size = {1250, 600};
const float player_size = 20.0f;
const float player_speed = 500.0f;
const float player_jump_force = 500.0f;
const Vec2 player_start_pos = {(screen_size.x / 2) - (player_size / 2), (screen_size.y / 2) - (player_size / 2)};

const float ground_height = 100.0f;
const float gravity = 1000.0f;

const Color background_color = {10, 10, 20, 255};
const Color ground_color = {50, 50, 50, 255};
const Color player_color = {255, 255, 50, 255};

int main ()
{
    Engine::Player player = {player_start_pos, player_speed, player_jump_force, player_size};
    Engine::Ground ground = {ground_height};

    Engine::Graphics::start_game (screen_size);
        while (!WindowShouldClose ())
        {
            Engine::Physics::move_player (screen_size, ground_height, gravity, player.position, player_size, player.speed_x, player.speed_y, player_jump_force);
            BeginDrawing ();

                ClearBackground (background_color);
                ground.draw (screen_size, ground_color);
                player.draw (player_color);

                #ifdef DEBUG
                    DrawFPS (20, 20);
                #endif

            EndDrawing ();
        }
    Engine::Graphics::end_game ();

    return 0;
}