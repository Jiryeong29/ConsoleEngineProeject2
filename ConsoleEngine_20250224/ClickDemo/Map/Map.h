#pragma once

#include <iostream>
#include <stdio.h>

#include <vector>
#include <array>
#include <algorithm>
#include "Math/Vector2.h"
#include "Level/Level.h"
#include "Actor/DrawableActor.h"
using namespace std;

class Vector2;
class Map : public DrawableActor
{
    // RTTI ����.
    RTTI_DECLARATIONS(Map, DrawableActor)
public:
    // �̵� ����.
    struct  Direction
    {
        int x;
        int y;
    };

public:
    // ������.
    Map(int worldWidth, int worldHeight);

    vector<vector<char>>GetMaze() { return maze; }




    //virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

public:
    std::vector<std::vector<char>> maze;
private:
    // �� ������ ����
    void GenerateMaze();

    // �̷� �����͸� txt ���Ϸ� ����
    void mapSave(const char* path);

private:

    Vector2 screenSize;
    Vector2 worldSize;
protected:

};

