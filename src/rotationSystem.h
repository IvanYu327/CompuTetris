#pragma once
#include <map>
#include <vector>
#include <utility>

using namespace std;

class SRSRotation
{
public:
    SRSRotation();
    vector<pair<int, int>> GetRotationTests(int block, int start, int end);

private:
    map<pair<int, int>, vector<pair<int, int>>> normalWallKickData;
    map<pair<int, int>, vector<pair<int, int>>> iWallKickData;
    void Initialize();
};
