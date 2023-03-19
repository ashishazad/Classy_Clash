#include "raylib.h"
#include "Map.h"

class Prop
{
public:
    Prop(Texture2D texture,Vector2 pos):
        tex(texture),
        worldPos(pos)
    {
        map = Map::getInstance();
    }

    void Render()
    {
        Vector2 screenPos = Vector2Add(map->GetPos(),worldPos);
        DrawTextureEx(tex,screenPos,0,scale,WHITE);
    }

    Rectangle getCollisionRec()
    {
        Vector2 screenPos = Vector2Add(map->GetPos(),worldPos);
        Rectangle rec{
            screenPos.x,
            screenPos.y,
            tex.width*scale,
            tex.height*scale
        };
        return rec;
    }
private:
    Map* map;
    Texture2D tex;
    Vector2 worldPos{};
    float scale{4.0f};
};