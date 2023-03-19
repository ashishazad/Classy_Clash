#include "raylib.h"
#include "GamingWindow.h"
#include "Map.h"
#include "Player.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // GamingWindow* gameWindow = 
    GamingWindow::getInstance();
    Map *map = Map::getInstance();
    Player player;

    Prop props[]{
        Prop(LoadTexture("nature_tileset/Rock.png"),Vector2{600,300}),
        Prop(LoadTexture("nature_tileset/Log.png"),Vector2{400,500}),
    };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
        &player
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        &player
    };

    Enemy * enemies[]{
        &goblin,
        &slime
    };

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        map->Draw();

        if(!player.getAlive())
        {
            DrawText("GAME OVER!!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        // else
        // {
        //     
        // }
        player.Tick();
        for(auto enemy : enemies)
        {
            enemy->Tick();
        }
       
        for(auto prop : props)
        {
            if(CheckCollisionRecs(prop.getCollisionRec(),player.getCollisionRec()))
            {
                player.UndoMovement();
            }
            
        }

        for(auto prop : props)
        {// this loop logic should be added in above loop but doing so shows weird error of not rendering player
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(prop.getCollisionRec(),enemy->getCollisionRec()))
                {
                    enemy->UndoMovement();
                }
            }
        }

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(player.getWeaponCollisionRec(),enemy->getCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        
        //somehow tht append was causing texture issue
        std::string health = "Health: ";
        float x = player.getHealth();
        std::string x1 = std::to_string(x).substr(0,5);
        health += x1;
        DrawText(health.c_str(), 55.f, 45.f, 40, RED);

        for(auto prop : props)
            prop.Render();
        for(auto enemy : enemies)
        {
            enemy->Draw();
        }
        player.Draw();

        EndDrawing();
    }
    return 0;
}