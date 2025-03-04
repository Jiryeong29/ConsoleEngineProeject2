#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Map/Map.h"
class Node;
class Player;
class AstarRoute;
class Start;
class Camera;
class GameLevel : public Level
{
    // RTTI 정의.
    RTTI_DECLARATIONS(GameLevel, Level)

public:
    GameLevel();
    virtual ~GameLevel();

    void Draw() override;
    void Update(float deltaTime) override;

    void AddMapActor();

    Vector2 GetPlayerPosition();

    Vector2 GetEndPosition();

    Vector2 GetWorldSize() { return worldSize; }
    Vector2 GetScreenSize() { return screenSize; }

    void SetPlayerPosition(Vector2 newPosition); 
    void SetEndPosition(Vector2 newPosition);

    Vector2 GetCameraTopLeft() { return screenTopLeft; }

    void DeleteAstarRoute();

    void AddAstarRouteActor(std::vector<Node*>);

    void DrawBound();
    // getter//setter

public:
    std::vector<Node*> AstarPath;
    AstarRoute* aStarRoute;
    Map* map;
    bool flagIsPlayerButton = false;
    bool isSpace = false;

private:

private:

    Player* player;
    Start* end;
    Camera* camera;

    // 실제 한 번에 보이는 화면 크기
    Vector2 screenSize;

    // 전체 맵 크기
    Vector2 worldSize;

    Vector2 currentCameraWorldPos;
    Vector2 screenTopLeft;
};
