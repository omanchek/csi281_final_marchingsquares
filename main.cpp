#include <raylib.h>
#include <cstdint>

void DrawPolgyonFromVertices(const Vector2 vertices[], const int numVertices)
{
   //for each vertex in shape
   for (int i = 0; i < numVertices; i++)
   {
      //draw a line from this index to the next, and wrap if on the last index
      DrawLineV(vertices[i], vertices[(i + 1) % numVertices], WHITE);
   }
}

Vector2 shape1[] = 
{
   Vector2(50, 50),
   Vector2(100, 200),
   Vector2(400, 250),
   Vector2(600, 200),
   Vector2(500, 150)
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int imgWidth = 400;
    const int imgHeight = 400;

    InitWindow(screenWidth, screenHeight, "Pixel Manipulation");

    SetTargetFPS(60);

    Image img = GenImageColor(imgHeight, imgHeight, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto pixels = (Color*)img.data;
    Texture tex = LoadTextureFromImage(img);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //// your update logic goes here
        //for(int row = 0; row < imgHeight; row++)
        //{
        //    for(int col = 0; col < imgWidth; col++)
        //    {
        //        pixels[row * imgWidth + col] = (Color) {
        //            (uint8_t)(GetRandomValue(0, 255)),
        //            (uint8_t)(GetRandomValue(0, 255)),
        //            (uint8_t)(GetRandomValue(0, 255)),
        //            255
        //        };
        //    }
        //}
        UpdateTexture(tex, pixels);

        // drawing logic goes here
        BeginDrawing();
        ClearBackground(BLACK);
        
        Vector2 point1 = Vector2(100, 100);
        Vector2 point2 = Vector2(400, 200);
        Vector2 point3 = Vector2(800, 0);

        //DrawTriangleLines(point1, point2, point3, WHITE);

        DrawPolgyonFromVertices(shape1, 5);

        EndDrawing();
    }

    UnloadTexture(tex);

    CloseWindow();
    return 0;
}