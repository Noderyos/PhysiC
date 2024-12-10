#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define VECTOR_IMPLEMENTATION
#include "vector.h"

#define WIDTH 800
#define HEIGHT 600

#define GRAVITY 100
#define DAMPER 0.9

#define FPS 60
#define DT (1./FPS)

#define TAIL_SIZE 50

typedef struct {
    int radius;
    Color color;
    V2d position;
    V2d velocity;
    V2d tail[TAIL_SIZE];
} Circle;


void update_tail(Circle *ball){
    memcpy(ball->tail, &ball->tail[1], (TAIL_SIZE-1)*sizeof(*ball->tail));
    ball->tail[TAIL_SIZE-1] = ball->position;
}


void update_position(Circle *ball){
    ball->velocity = v2d_add(ball->velocity, v2d(0, GRAVITY*DT));
    ball->position = v2d_add(ball->position, ball->velocity);
}

void apply_colisions(Circle *b){
    if((b->position.y+b->radius) > HEIGHT) {
        b->position.y = HEIGHT-b->radius;
        b->velocity.y = -b->velocity.y*DAMPER;
    }
    if((b->position.y-b->radius) < 0){
        b->position.y = b->radius;
        b->velocity.y = -b->velocity.y*DAMPER;
    }
    if((b->position.x+b->radius) > WIDTH) {
        b->position.x = WIDTH-b->radius;
        b->velocity.x = -b->velocity.x*DAMPER;
    }
    if((b->position.x-b->radius) < 0){
        b->position.x = b->radius;
        b->velocity.x = -b->velocity.x*DAMPER;
    }
}


Color fade(Color c1, Color c2, double max, double i){
    return (Color){
        c1.r*(1-i/max)+c2.r*(i/max),
        c1.g*(1-i/max)+c2.g*(i/max),
        c1.b*(1-i/max)+c2.b*(i/max),
        c1.a*(1-i/max)+c2.a*(i/max)
    };
}

int main(){
    InitWindow(WIDTH, HEIGHT, "Physics");
    SetTargetFPS(FPS);

    Circle ball = {.radius = 20, .color = BLUE, .position = {WIDTH/2, HEIGHT/2}, .velocity ={1000, -5000}};

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        
        update_position(&ball);
        apply_colisions(&ball);
        update_tail(&ball);

        for(int i = 0; i < TAIL_SIZE; i++){
            DrawCircle(ball.tail[i].x, ball.tail[i].y, ball.radius*i/TAIL_SIZE, fade(BLACK, ball.color, TAIL_SIZE, i));
        }

        DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}
