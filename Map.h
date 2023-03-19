#pragma once
#include "raylib.h"
#include "GamingWindow.h"

class Map
{
private:
    Texture2D tex;
    Vector2 pos;
    float scale;
    Map()
    {
        tex = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
        pos.x = 0.0;
        pos.y = 0.0;
        scale = 4.0;
    }
    ~Map(){}
    Map(Map &other) = delete;
    Map operator=(Map& other) = delete;

    static Map* instance;
public:
    
    static Map* getInstance()
    {
        if(!instance)
        {
            instance = new Map();
        }
        return instance;
    }
    void Draw()
    {
        DrawTextureEx(tex,pos,0.0,scale,WHITE);
    }

    void Move(Vector2 newPos)
    {
        if(newPos.x > 0)
        {
            newPos.x = 0;
        }
        else if(tex.width*scale + newPos.x <= GamingWindow::width)
        {
            newPos.x = pos.x;
        }

        if(newPos.y > 0)
        {
            newPos.y = 0;
        }
        else if(tex.height*scale + newPos.y <= GamingWindow::height)
        {
            newPos.y = pos.y;
        }

        pos = newPos;
    }

    Vector2 GetPos()
    {
        return pos;
    }
};

Map* Map::instance = nullptr;