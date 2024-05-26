#include "raylib.h"

// Definición de estados del juego
typedef enum PantallaJuego { MENU = 0, NIVELES, SALIR } PantallaJuego;

// Declaraciones de funciones
void ActualizarMenu(PantallaJuego *pantallaActual, Font font, Sound sound2);
void DibujarMenu(Font font);
void DibujarNiveles(PantallaJuego *pantallaActual, Font font, Sound sound2);
void sonido2(Sound *sound2);
void limpiarRecursos(Texture2D texture, Texture2D texture2, Texture2D texture3, Font font, Sound sound, Sound sound2);

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "JUEGO PRUEBA");

    // Variables del programa
    Image image = LoadImage("logo2.png");
    Font font = LoadFont("C:\\Users\\maxye\\Desktop\\Programacion-estructurada\\Juego\\fuente\\The_Last_Shuriken.otf");

    // Escalar la imagen al tamaño de la ventana
    const float scaleFactor = 0.5f;
    ImageResize(&image, (int)(image.width * scaleFactor), (int)(image.height * scaleFactor));

    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    float alpha = 0.0f;
    const float fadeSpeed = 1.0f / (12.0f * 60.0f);  // 12 segundos de desvanecimiento a 60 FPS

    InitAudioDevice();

    Sound sound = LoadSound("imu.wav");
    
    PlaySound(sound);

    PantallaJuego pantallaActual = MENU; 

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
    Sound sound2;
    sonido2(&sound2);

    // Mostrar "Cargando..." en un fondo negro
    float loadingTime = 6.0f;  // 6 segundos de pantalla de carga
    double startTime = GetTime();
    while ((GetTime() - startTime < loadingTime) && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, "C a r g a n d o . . .", (Vector2){ screenWidth / 2 - MeasureTextEx(font, "C a r g a n d o . . .", 50, 0).x / 2, screenHeight / 2 - 10 }, 50, 0, WHITE);
        EndDrawing();
    }

    // Cargar la textura para "menu.png"
    Image image2 = LoadImage("menu.png");
    Texture2D texture2 = LoadTextureFromImage(image2);
    UnloadImage(image2);

    // Carga la textura para "Niveles"
    Image image3 = LoadImage("Niveles.png");
    int nuevaAncho=1000, nuevoAltura=500;
    ImageResize(&image3, nuevaAncho, nuevoAltura);
    Texture2D texture3 = LoadTextureFromImage(image3);
    UnloadImage(image3);

    // Mostrar la imagen "menu.png" en toda la pantalla
    while (pantallaActual != SALIR && !WindowShouldClose())
    {
        if (pantallaActual == MENU)
        {
            ActualizarMenu(&pantallaActual, font, sound2);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (pantallaActual == MENU)
        {
            DrawTexture(texture2, 0, 0, WHITE);  // Dibujar el fondo del menú
            DibujarMenu(font);  // Dibujar los elementos del menú
        }
        else if (pantallaActual == NIVELES)
        {
            DrawTexture(texture3, 0, 0, WHITE);  // Dibujar el fondo de los niveles
            DibujarNiveles(&pantallaActual, font, sound2);
        
        }

        EndDrawing();
    }

    // Liberar recursos
    limpiarRecursos(texture, texture2, texture3, font, sound, sound2);
    
    return 0;
}

void ActualizarMenu(PantallaJuego *pantallaActual, Font font, Sound sound2)
{
    Vector2 mousePoint = GetMousePosition();
    Rectangle botonNIVELES = { 400, 220, 200, 50 };
    Rectangle botonSalir = { 400, 300, 200, 50 };

    if (CheckCollisionPointRec(mousePoint, botonNIVELES) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        sonido2(&sound2);
        *pantallaActual = NIVELES;  // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePoint, botonSalir) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        sonido2(&sound2);
        *pantallaActual = SALIR;  // Cambia al estado de salir
    }
}

void DibujarMenu(Font font)
{
    int outlineThickness = 1;
    DrawTextEx(font, "N O M B R E  D E L  J U E G O", (Vector2){ 230, 100 }, 35, 0, BLACK);

    // Dibujar botón "JUGAR"
    for (int i = -outlineThickness; i <= outlineThickness; i++) 
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++) 
        {
            if (i != 0 || j != 0) 
            {
                DrawRectangle(400 + i, 220 + j, 200 + i, 50 + j, BLACK);
            }
        }
    }
    DrawRectangle(400, 220, 200, 50, LIGHTGRAY);

    // Dibujar texto con contorno
    for (int i = -outlineThickness; i <= outlineThickness; i++) 
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++) 
        {
            if (i != 0 || j != 0) 
            {
                DrawTextEx(font, "J U G A R", (Vector2){455 + i, 235 + j}, 20, 0, BLACK);
            }
        }
    }
    DrawTextEx(font, "J U G A R", (Vector2){ 455, 235 }, 20, 0, GRAY);

    // Dibujar botón "Salir"
    for (int i = -outlineThickness; i <= outlineThickness; i++) 
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++) 
        {
            if (i != 0 || j != 0) 
            {
                DrawRectangle(400 + i, 300 + j, 200 + i, 50 + j, BLACK);
            }
        }
    }
    DrawRectangle(400, 300, 200, 50, LIGHTGRAY);
    
    // Dibujar texto con contorno
    for (int i = -outlineThickness; i <= outlineThickness; i++) 
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++) 
        {
            if (i != 0 || j != 0) 
            {
                DrawTextEx(font, "S A L I R", (Vector2){455 + i, 318 + j}, 20, 0, BLACK);
            }
        }
    }
    // Dibujar botón "Salir"
    DrawTextEx(font, "S A L I R", (Vector2){ 455, 318 }, 20, 0, GRAY);
}
    Color cafeOscuro={139, 69, 19, 255};
    Color cafeOscuroB={121, 55, 8, 255};
    Color Rojos={192, 6, 4, 255};
void DibujarNiveles(PantallaJuego *pantallaActual, Font font, Sound sound2)
{
    
    DrawTextEx(font, "EASY", (Vector2){ 700, 70 }, 30, 5, cafeOscuro);
    DrawTextEx(font, "NORMAL", (Vector2){ 670, 175 }, 30, 5, cafeOscuro);
    DrawTextEx(font, "HARD", (Vector2){ 690, 280 }, 30, 5, cafeOscuroB);
    DrawTextEx(font, "REGRESAR",(Vector2){ 645, 375}, 30, 5, Rojos);

    Vector2 mousePosicion = GetMousePosition();
    Rectangle botonEASY = { 700, 70, 100, 30 };
    Rectangle botonNORMAL = { 670, 175, 160, 30 };
    Rectangle botonHARD = { 690, 280, 110, 30 };
    Rectangle botonREGRESAR = { 645, 375, 225, 30 };

    if (CheckCollisionPointRec(mousePosicion, botonEASY) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        sonido2(&sound2);
        *pantallaActual = MENU;  // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePosicion, botonNORMAL) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        sonido2(&sound2);
        *pantallaActual = MENU;  // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePosicion, botonHARD) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        sonido2(&sound2);
        *pantallaActual = MENU;  // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePosicion, botonREGRESAR) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        sonido2(&sound2);
        *pantallaActual = MENU;  // Cambia al estado de juego
    }
    
}

void sonido2(Sound *sound2)
{
    *sound2 = LoadSound("carga.wav");
    PlaySound(*sound2);
}

void limpiarRecursos(Texture2D texture, Texture2D texture2, Texture2D texture3, Font font, Sound sound, Sound sound2)
{
    UnloadSound(sound);
    UnloadSound(sound2);
    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadTexture(texture3);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();
}
