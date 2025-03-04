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

    GenerateMaze();  // �̷� ����
    mapSave(path);   // �̷� ���� (��� ���� ��ġ�Ͽ� ����)
}

void Map::GenerateMaze()
{
    // ���� ���� ���: ��(row) ���� (maze[row][col])
    std::vector<std::vector<char>>  temp(worldSize.y, vector<char>(worldSize.x, '#'));

    srand(static_cast<unsigned int>(time(nullptr)));

    // ���� ��ġ�� Ȧ�� ��ǥ�� ����
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

        // 8���� (2ĭ�� �̵�)
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
            // �� ĭ ������ �߰� ��ġ
            int wx = x + dx / 2;
            int wy = y + dy / 2;

            // ���� üũ �� ���� ��ġ�� ���� ��('#')���� Ȯ��
            if (nx > 0 && nx < worldSize.x - 1 &&
                ny > 0 && ny < worldSize.y - 1 &&
                temp[ny][nx] == '#')
            {
                // �߰� �� ���� �� ���� ���� �� �������� ����
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
        cout << "������ ���� ���߽��ϴ�." << endl;
        return;
    }

    if (maze.empty())
    {
        cerr << "����: �� �̷� �����͸� �����Ϸ��� �մϴ�!" << endl;
        fclose(file);
        return;
    }

    // ���� ������ maze[��][��]�̹Ƿ�, ������ �� outer loop�� ��(���ο� ��) �������� �ݺ��ϸ�
    // ��� ������ ��� ���� �ݴ�� ����˴ϴ�.
    // ��, ���Ͽ��� worldSize.x ���� �����ǰ�, �� ���� worldSize.y ���� ���ڸ� �����ϴ�.
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
//    maze.resize(Engine::Get().ScreenSize().y, vector<char>(Engine::Get().ScreenSize().x, '#'));  // y: ��, x: ��
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
//    maze[y][x] = ' '; // ���� ��ġ�� �� �������� ����
//    const vector<Direction> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0}, {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };
//    for (size_t i = 0; i < directions.size(); ++i)
//    {
//        int index = rand() % directions.size(); // ������ �ε����� ����
//        int dx = directions[index].x;
//        int dy = directions[index].y;
//        int nx = x + dx, ny = y + dy; // ���� ��ġ ���
//        int wx = x + dx / 2, wy = y + dy / 2; // ���� �㹰 ��ġ
//
//        if (nx > 0 && nx < screenSize.x - 1 && ny > 0 && ny < screenSize.y- 1 && maze[ny][nx] == '#') {
//            maze[wy][wx] = ' '; // ���� �㹰�� �� �����
//            CarvePath(nx, ny); // ��������� ���� ��� Ž��
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
//    // �����: ���� ��� Ȯ��
//    std::cout << "���� ���� ���: " << path << std::endl;
//
//    // ���� ����
//    fopen_s(&file, path, "w");
//
//    // ������ ������ �ʾ��� ���
//    if (file == nullptr) {
//        std::cout << "������ ������ ����!\n";
//        return;
//    }
//    
//    // ������ �ʵ����͸�  txt�� ����
//    MapExportElement(file);
//
//    // ���� �������� ���Ͽ��� ���.
//    if (maze.empty()) {
//        std::cerr << "����: �� �̷� �����͸� �����Ϸ��� �մϴ�!" << std::endl;
//        fclose(file);
//        return;
//    }
//
//    fclose(file);
//}
//
