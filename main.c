#include <stdlib.h>
#include <assert.h>

#include "raylib.h"

#define COLLISION_DUMP 1
#define OBJECTS_COUNT 10
#define VELOCITY_X 300
#define VELOCITY_Y 300

Vector2 OBJECT_SIZE = {100, 100};
Vector2 GRAVITY     = {0, 10000};

typedef struct object_t {
    Vector2 position;
    Vector2 velocity;
    Color color;
} object_t;

object_t *create_objects()
{
    object_t *objects = (object_t *)malloc(OBJECTS_COUNT*sizeof(object_t));
    assert(objects != NULL);

    for (int i = 0; i < OBJECTS_COUNT; ++i) {
        Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        objects[i].position.x = GetRandomValue(0, GetScreenWidth());
        objects[i].position.y = GetRandomValue(0, GetScreenHeight());
        objects[i].velocity.x = VELOCITY_X;
        objects[i].velocity.y = VELOCITY_Y;
        objects[i].color      = color;
    }
    return objects;
}

void draw_objects(object_t *objects, float dt)
{
    for (int i = 0; i < OBJECTS_COUNT; i++) {
        objects[i].velocity.x += GRAVITY.x * dt;
        objects[i].velocity.y += GRAVITY.y * dt;

        float nx = objects[i].position.x + objects[i].velocity.x * dt;
        float ny = objects[i].position.y + objects[i].velocity.y * dt;

        if (nx < 0 || nx > GetScreenWidth() - OBJECT_SIZE.x) {
            objects[i].velocity.x *= -COLLISION_DUMP;
            Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
            objects[i].color = color;
        } else {
            objects[i].position.x = nx;
        }
        if (ny < 0 || ny > GetScreenHeight() - OBJECT_SIZE.y) {
            objects[i].velocity.y *= -COLLISION_DUMP;
            Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
            objects[i].color = color;
        } else {
            objects[i].position.y = ny;
        }
        DrawRectangleV(objects[i].position, OBJECT_SIZE, objects[i].color);
    }
}

void game_frame(object_t *objects)
{
    float dt = GetFrameTime();
    BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(100, 100);
        draw_objects(objects, dt);
    EndDrawing();
}
int main(void)
{
    int width  = 1200;
    int height = 800;

    InitWindow(width, height, "Cubes");

    SetTargetFPS(60);
    object_t *objects = create_objects(OBJECTS_COUNT);

    while (!WindowShouldClose()) {
        game_frame(objects);
    }
    CloseWindow();
    return 0;
}
