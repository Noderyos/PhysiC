#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define VECTOR_IMPLEMENTATION
#include "vector.h"

#define WIDTH 800
#define HEIGHT 600

#define GRAVITY 100

#define FPS 50
#define DT (1./FPS)

#define DAMPER 0.9

V2d tail[50] = {0};

void add_to_tail(V2d v){
    memcpy(tail, &tail[1], 49*sizeof(*tail));
    tail[49] = v;
}

int main(){
    InitWindow(WIDTH, HEIGHT, "Physics");
    SetTargetFPS(FPS);
    
    V2d ball = {WIDTH/2, HEIGHT/2};
    V2d velocity = {1000, -5000};

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        
        velocity = v2d_add(velocity, v2d(0, GRAVITY*DT));
        ball = v2d_add(ball, velocity);

        if((ball.y+50) > HEIGHT) {
            ball.y = HEIGHT-50;
            velocity.y = -velocity.y*DAMPER;
        }
        if((ball.y-50) < 0){
            ball.y = 50;
            velocity.y = -velocity.y*DAMPER;
        }
        if((ball.x+50) > WIDTH) {
            ball.x = WIDTH-50;
            velocity.x = -velocity.x*DAMPER;
        }
        if((ball.x-50) < 0){
            ball.x = 50;
            velocity.x = -velocity.x*DAMPER;
        }

        add_to_tail(ball);

        for(int i = 0; i < 50; i++){
            DrawCircle(tail[i].x, tail[i].y, 5, ORANGE);
        }

        DrawCircle(ball.x, ball.y, 50, WHITE);
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}
