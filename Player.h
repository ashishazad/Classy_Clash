#pragma once
#include "BaseCharacter.h"

class Player : public BaseCharacter
{
private:
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec;
    float health{100.f};
public:
    Player()
    {
        idle_texture = LoadTexture("characters/knight_idle_spritesheet.png");
        run_texture = LoadTexture("characters/knight_run_spritesheet.png");
        tex = idle_texture;
        width = (float)tex.width/6;
        height = (float)tex.height;

        screenPos.x = GamingWindow::width/2-scale*0.5*width;
        screenPos.y = GamingWindow::height/2-scale*0.5*height;
    }

    virtual void Tick() override
    {
       if(!getAlive()) return;

        BaseCharacter::Tick();

        Vector2 direction{0.0f,0.0f};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        BaseCharacter::Move(direction);

        if(Vector2Length(direction)!=0.0)
        {
            map->Move(Vector2Scale(worldPos,-1.0f));
        }
    }

    virtual void UndoMovement() override
    {
        BaseCharacter::UndoMovement();
        map->Move(Vector2Scale(worldPos,-1.0f));
    }

    virtual void Draw() override
    {
        BaseCharacter::Draw();
        DrawWeapon();
    }

    void DrawWeapon()
    {
        if(!getAlive()) return;
        Vector2 origin;
        Vector2 offset;

        float rotation;

        if(rightLeft >0)
        {
            origin = {0.0f, scale*static_cast<float>(weapon.height)};
            offset = {35.f,55.f};
            weaponCollisionRec = Rectangle{
                screenPos.x+offset.x,
                screenPos.y+offset.y-scale*weapon.height,
                scale*weapon.width,
                scale*weapon.height
            };
            rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
        }
        else
        {
            origin = {scale * static_cast<float>(weapon.width), scale*static_cast<float>(weapon.height)};
            offset = {35.f,55.f};
            weaponCollisionRec = Rectangle{
                screenPos.x+offset.x-scale*weapon.width,
                screenPos.y+offset.y-scale*weapon.height,
                scale*weapon.width,
                scale*weapon.height
            };
            rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
        }
        Rectangle source{0.0f,0.0f,rightLeft * static_cast<float>(weapon.width),static_cast<float>(weapon.height)};
        Rectangle dest{screenPos.x+offset.x,screenPos.y+offset.y,scale*static_cast<float>(weapon.width),scale*static_cast<float>(weapon.height)};
        DrawTexturePro(weapon,source,dest,origin,rotation,WHITE);

        DrawRectangleLines(
            weaponCollisionRec.x,weaponCollisionRec.y,weaponCollisionRec.width,weaponCollisionRec.height
        ,RED);
    }

    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;};

    float getHealth() {return health;};

    // string getHealthString() {};
    void TakeDamage(float damage)
    {
        health -= damage;
        if(health<=0)
        {
            setAlive(false);
        }
    }
};