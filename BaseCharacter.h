#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
#include "raymath.h"
#include "Map.h"
#include "GamingWindow.h"
#include "AnimData.h"
class BaseCharacter
{
protected:
    Vector2 screenPos{0.0f,0.0f};
    Vector2 worldPos{0.0f,0.0f};
    Vector2 worldPosLastFrame{0.0f,0.0f};
    float speed;
    Texture2D tex;
    Texture2D idle_texture;
    Texture2D run_texture;
    float scale;
    int rightLeft{1};
    AnimData animData;
    Map* map;
    float width;
    float height;
    bool alive{true};
    BaseCharacter()
    {
        //default values
        speed = 4;
        scale = 4;
        animData.totalFrame = 6;
        animData.animationDelay = 1.0f/12.0f;
        map = Map::getInstance();
       
    }
public:
    virtual void Tick()
    {
        worldPosLastFrame = worldPos;
    }

    virtual void Draw()
    {
        if(!getAlive())return;
        Rectangle source{animData.currentFrame*width,0.0f,rightLeft*width,height};
        Rectangle dest{screenPos.x,screenPos.y,scale*width,scale*height};
        DrawTexturePro(tex,source,dest,Vector2{},0.0f,WHITE);
        animData.updateAnimData();
    }

    Rectangle getCollisionRec()
    {
        Rectangle rec{
            screenPos.x,
            screenPos.y,
            width*scale,
            height*scale
        };
        return rec;
    } 

    virtual void UndoMovement()
    {
        worldPos = worldPosLastFrame;
    }

    Vector2 getWorldPos()
    {
        return worldPos;
    }

    Vector2 getScreenPos()
    {
        return screenPos;
    }

    void Move(Vector2 &direction)
    {
        if(Vector2Length(direction)!=0.0)
        {
            direction = Vector2Normalize(direction);
            direction = Vector2Scale(direction, speed);
            worldPos = Vector2Add(worldPos,direction);
            direction.x > 0 ? rightLeft=1 : rightLeft=-1;
            tex = run_texture;
        }
        else
        {
            tex = idle_texture;
        }
    }

    bool getAlive() {return alive;};

    void setAlive(bool alive_){alive = alive_;};

};

#endif