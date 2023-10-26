#pragma once
#include <map>
#include <vector>
#include <utility>

using namespace std;

class RotationSystem
{
public:
    RotationSystem();
    vector<pair<int, int>> GetRotationTests(int block, int start, int end);

private:
    map<pair<int, int>, vector<pair<int, int>>> SRS_JLSZTO_WallKickData;
    map<pair<int, int>, vector<pair<int, int>>> SRS_I_WallKickData;
    void Initialize();
};
