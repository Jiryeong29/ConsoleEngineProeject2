#include "map.h"
#include <vector>
#include <algorithm> // random_shuffle
#include <stack>
#include "Engine/Engine.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>

using namespace std;

Map::Map(int worldWidth, int worldHeight)
    : worldSize(worldWidth, worldHeight),
    screenSize(Engine::Get().ScreenSize().x, Engine::Get().ScreenSize().y)
{
    const char* path = "Map/MapData.txt";

    GenerateMaze();  // 미로 생성
    mapSave(path);   // 미로 저장 (행과 열을 전치하여 저장)
}

void Map::GenerateMaze()
{
    // 기존 저장 방식: 행(row) 기준 (maze[row][col])
    std::vector<std::vector<char>>  temp(worldSize.y, vector<char>(worldSize.x, '#'));

    srand(static_cast<unsigned int>(time(nullptr)));

    // 시작 위치를 홀수 좌표로 결정
    int startX = (rand() % (worldSize.x / 2)) * 2 + 1;
    int startY = (rand() % (worldSize.y / 2)) * 2 + 1;

    temp[startY][startX] = ' ';
    stack<pair<int, int>> st;
    st.push(make_pair(startX, startY));

    while (!st.empty())
    {
        pair<int, int> current = st.top();
        st.pop();

        int x = current.first;
        int y = current.second;

        // 8방향 (2칸씩 이동)
        vector<Direction> directions = {
            {0, -2}, {0, 2}, {-2, 0}, {2, 0},
            {-2, -2}, {-2, 2}, {2, -2}, {2, 2}
        };

        random_shuffle(directions.begin(), directions.end());

        for (auto& dir : directions)
        {
            int dx = dir.x;
            int dy = dir.y;
            int nx = x + dx;
            int ny = y + dy;
            // 두 칸 사이의 중간 위치
            int wx = x + dx / 2;
            int wy = y + dy / 2;

            // 범위 체크 및 다음 위치가 아직 벽('#')인지 확인
            if (nx > 0 && nx < worldSize.x - 1 &&
                ny > 0 && ny < worldSize.y - 1 &&
                temp[ny][nx] == '#')
            {
                // 중간 벽 제거 및 다음 셀을 빈 공간으로 설정
                temp[wy][wx] = ' ';
                temp[ny][nx] = ' ';
                st.push(make_pair(nx, ny));
            }
        }
    }

    maze = temp;/*
    maze.resize(worldSize.y, vector<char>(worldSize.x));

    for (int ix = 0; ix < temp.size();++ix)
    {
        for (int jx = 0; jx < temp[ix].size(); ++ix)
        {
            maze[jx][ix] = temp[ix][jx];
        }
    }*/
}

void Map::mapSave(const char* path)
{
    FILE* file = nullptr;
    fopen_s(&file, path, "w");

    if (file == nullptr)
    {
        cout << "파일을 열지 못했습니다." << endl;
        return;
    }

    if (maze.empty())
    {
        cerr << "에러: 빈 미로 데이터를 저장하려고 합니다!" << endl;
        fclose(file);
        return;
    }

    // 내부 저장이 maze[열][행]이므로, 저장할 때 outer loop를 열(새로운 행) 기준으로 반복하면
    // 출력 파일은 행과 열이 반대로 저장됩니다.
    // 즉, 파일에는 worldSize.x 줄이 생성되고, 각 줄은 worldSize.y 개의 문자를 가집니다.
    for (int x = 0; x < worldSize.x; ++x)
    {
        for (int y = 0; y < worldSize.y; ++y)
        {
            fputc(maze[x][y], file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

//void Map::GenerateMaze() {
//    maze.resize(Engine::Get().ScreenSize().y, vector<char>(Engine::Get().ScreenSize().x, '#'));  // y: 행, x: 열
//    srand(time(0));
//
//    int startX = (rand() % (Engine::Get().ScreenSize().x / 2)) * 2 + 1;
//    int startY = (rand() % (Engine::Get().ScreenSize().y / 2)) * 2 + 1;
//
//    CarvePath(startX, startY);
//}
//
//void Map::CarvePath(int x, int y) 
//{
//
//    maze[y][x] = ' '; // 현재 위치를 빈 공간으로 설정
//    const vector<Direction> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0}, {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };
//    for (size_t i = 0; i < directions.size(); ++i)
//    {
//        int index = rand() % directions.size(); // 랜덤한 인덱스를 선택
//        int dx = directions[index].x;
//        int dy = directions[index].y;
//        int nx = x + dx, ny = y + dy; // 다음 위치 계산
//        int wx = x + dx / 2, wy = y + dy / 2; // 벽을 허물 위치
//
//        if (nx > 0 && nx < screenSize.x - 1 && ny > 0 && ny < screenSize.y- 1 && maze[ny][nx] == '#') {
//            maze[wy][wx] = ' '; // 벽을 허물어 길 만들기
//            CarvePath(nx, ny); // 재귀적으로 다음 경로 탐색
//        }
//    }
//}
//void Map::MapExportElement(FILE*& file)
//{
//    for (int ix = 0; ix < Engine::Get().ScreenSize().y;++ix)
//    {
//        for (int jx = 0; jx < Engine::Get().ScreenSize().x; ++jx)
//        {
//            fputc(maze[ix][jx], file);
//        }
//        fputc('\n', file);
//    }
//}
//
//void Map::MapExport(const char* path) {
//    FILE* file = nullptr;
//
//    // 디버깅: 파일 경로 확인
//    std::cout << "파일 저장 경로: " << path << std::endl;
//
//    // 파일 열기
//    fopen_s(&file, path, "w");
//
//    // 파일이 열리지 않았을 경우
//    if (file == nullptr) {
//        std::cout << "파일이 열리지 못함!\n";
//        return;
//    }
//    
//    // 생성한 맵데이터를  txt로 추출
//    MapExportElement(file);
//
//    // 맵을 생성하지 못하였을 경우.
//    if (maze.empty()) {
//        std::cerr << "에러: 빈 미로 데이터를 저장하려고 합니다!" << std::endl;
//        fclose(file);
//        return;
//    }
//
//    fclose(file);
//}
//
