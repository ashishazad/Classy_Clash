#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Map.h"
#include "GamingWindow.h"
#include "AnimData.h"
#include "BaseCharacter.h"
#include "Player.h"

class Enemy : public BaseCharacter
{
private:
   Player *player;
   float chaseRadius{25.f};
public:
    Enemy(Vector2 pos, Texture2D idle, Texture2D run, Player* target)
    {
        worldPos = pos;
        idle_texture = idle;
        run_texture = run;
        //override bas class values if needed
        tex = idle_texture;
        width = (float)tex.width/6;
        height = (float)tex.height;
        player = target;
        speed = 3.0f;
    }

    virtual void Tick() override
    {
        if(!getAlive())return;
        BaseCharacter::Tick();

        Vector2 direction = Vector2Subtract(player->getScreenPos(),screenPos);
        if(Vector2Length(direction)<chaseRadius)
        {
            direction = Vector2{};
            tex = idle_texture;
        }
        else
        {
            tex = run_texture;
        }

        BaseCharacter::Move(direction);
        screenPos = Vector2Add(map->GetPos(),worldPos);

        if(CheckCollisionRecs(player->getCollisionRec(),getCollisionRec()))
        {
            player->TakeDamage(50.0f*GetFrameTime());
        }
    }
};