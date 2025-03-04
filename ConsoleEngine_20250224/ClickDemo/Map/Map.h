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
    // RTTI 정의.
    RTTI_DECLARATIONS(Map, DrawableActor)
public:
    // 이동 방향.
    struct  Direction
    {
        int x;
        int y;
    };

public:
    // 생성자.
    Map(int worldWidth, int worldHeight);

    vector<vector<char>>GetMaze() { return maze; }




    //virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

public:
    std::vector<std::vector<char>> maze;
private:
    // 맵 데이터 생성
    void GenerateMaze();

    // 미로 데이터를 txt 파일로 저장
    void mapSave(const char* path);

private:

    Vector2 screenSize;
    Vector2 worldSize;
protected:

};

