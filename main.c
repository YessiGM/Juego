//Juego PE
#include "raylib.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "JUEGO PRUEBA");

    //Variables del programa
    Image image = LoadImage("logo2.png");
    Font font = LoadFont("C:\\Users\\maxye\\OneDrive\\Escritorio\\Programacion estructurada\\Juego\\fuente");

    // Escalar la imagen  al tamaño de la ventana
    const float scaleFactor = 0.5f;
    ImageResize(&image, (int)(image.width * scaleFactor), (int)(image.height * scaleFactor));

    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    float alpha = 0.0f;
    const float fadeSpeed = 1.0f / (12.0f * 60.0f);  // 12 segundos de desvanecimiento a 60 FPS

    InitAudioDevice();

    Sound sound = LoadSound("imu.wav");
    Sound sound2 = LoadSound("carga.wav");
    PlaySound(sound);

    // Animación de desvanecimiento al inicio de la aplicación
    while (alpha < 1.0f && !WindowShouldClose())
    {
        alpha += fadeSpeed;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
        DrawTexturePro(texture, (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
                       (Rectangle){ screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2,
                       (float)texture.width, (float)texture.height }, (Vector2){ 0, 0 }, 0.0f, Fade(WHITE, alpha));
        EndDrawing();
    }

    // Esperar 2 segundos antes de hacer que la imagen desaparezca
    WaitTime(2.0f);

    // Animación de desvanecimiento para hacer que la imagen desaparezca
    while (alpha > 0.0f && !WindowShouldClose())
    {
        alpha -= fadeSpeed;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
        DrawTexturePro(texture, (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
                       (Rectangle){ screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2,
                       (float)texture.width, (float)texture.height }, (Vector2){ 0, 0 }, 0.0f, Fade(WHITE, alpha));
        EndDrawing();
    }

    // Reproducir sonido de carga
    PlaySound(sound2);

    // Mostrar "Cargando..." en un fondo negro
    float loadingTime = 6.0f;  // 6 segundos de pantalla de carga
    double startTime = GetTime();
    while ((GetTime() - startTime < loadingTime) && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, "C a r g a n d o . . .", (Vector2){ screenWidth / 2 - MeasureTextEx(font, "Cargando...", 50, 0).x / 2, screenHeight / 2 - 10 }, 50, 0, WHITE);
        EndDrawing();
    }

    // Cargar la textura para "menu.png"
    Image image2 = LoadImage("menu.png");
    Texture2D texture2 = LoadTextureFromImage(image2);
    UnloadImage(image2);

    // Mostrar la imagen "menu.png" en toda la pantalla
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexturePro(texture2, (Rectangle){ 0.0f, 0.0f, (float)texture2.width, (float)texture2.height },
                       (Rectangle){ 0, 0, screenWidth, screenHeight }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }

    // Liberar recursos
    UnloadSound(sound);
    UnloadSound(sound2);
    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
