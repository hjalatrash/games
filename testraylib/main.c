#include "raylib.h"

int main(void)
{
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "My Raylib Window");
    
    // Set target frames-per-second
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        // Draw
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            DrawText("Welcome to Raylib!", 190, 200, 20, BLACK);
            
        EndDrawing();
    }
    
    // De-Initialization
    CloseWindow();        // Close window and OpenGL context
    
    return 0;
} 