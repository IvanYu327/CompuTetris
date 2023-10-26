#include "rotationSystem.h"
#include <map>
#include <vector>
#include <utility>

using namespace std;

RotationSystem::RotationSystem()
{
    Initialize();
}

vector<pair<int, int>> RotationSystem::GetRotationTests(int blockId, int startState, int EndState)
{
    pair<int, int> rotation = make_pair(startState, EndState);

    // I Block
    if (blockId == 1)
    {
        return SRS_I_WallKickData[rotation];
    }
    else
    {
        return SRS_JLSZTO_WallKickData[rotation];
    }
}

void RotationSystem::Initialize()
{
    SRS_JLSZTO_WallKickData[make_pair(0, 1)] = {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}};
    SRS_JLSZTO_WallKickData[make_pair(1, 0)] = {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}};
    SRS_JLSZTO_WallKickData[make_pair(1, 2)] = {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}};
    SRS_JLSZTO_WallKickData[make_pair(2, 1)] = {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}};
    SRS_JLSZTO_WallKickData[make_pair(2, 3)] = {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}};
    SRS_JLSZTO_WallKickData[make_pair(3, 2)] = {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}};
    SRS_JLSZTO_WallKickData[make_pair(3, 0)] = {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}};
    SRS_JLSZTO_WallKickData[make_pair(0, 3)] = {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}};
    // 180
    SRS_JLSZTO_WallKickData[make_pair(0, 2)] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}, {2, 1}, {-1, 0}, {-2, 0}, {-1, 1}, {-2, 1}, {0, -1}, {3, 0}, {-3, 0}};
    SRS_JLSZTO_WallKickData[make_pair(1, 3)] = {{0, 0}, {0, 1}, {0, 2}, {-1, 1}, {-1, 2}, {0, -1}, {0, -2}, {-1, -1}, {-1, -2}, {1, 0}, {0, 3}, {0, -3}};
    SRS_JLSZTO_WallKickData[make_pair(2, 0)] = {{0, 0}, {-1, 0}, {-2, 0}, {-1, -1}, {-2, -1}, {1, 0}, {2, 0}, {1, -1}, {2, -1}, {0, 1}, {-3, 0}, {3, 0}};
    SRS_JLSZTO_WallKickData[make_pair(3, 1)] = {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {0, -1}, {0, -2}, {1, -1}, {1, -2}, {-1, 0}, {0, 3}, {0, -3}};

    SRS_I_WallKickData[make_pair(0, 1)] = {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}};
    SRS_I_WallKickData[make_pair(1, 0)] = {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}};
    SRS_I_WallKickData[make_pair(1, 2)] = {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}};
    SRS_I_WallKickData[make_pair(2, 1)] = {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}};
    SRS_I_WallKickData[make_pair(2, 3)] = {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}};
    SRS_I_WallKickData[make_pair(3, 2)] = {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}};
    SRS_I_WallKickData[make_pair(3, 0)] = {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}};
    SRS_I_WallKickData[make_pair(0, 3)] = {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}};
    // 180
    SRS_I_WallKickData[make_pair(0, 2)] = {{0, 0}, {-1, 0}, {-2, 0}, {1, 0}, {2, 0}, {0, 1}};
    SRS_I_WallKickData[make_pair(1, 3)] = {{0, 0}, {0, 1}, {0, 2}, {0, -1}, {0, -2}, {-1, 0}};
    SRS_I_WallKickData[make_pair(2, 0)] = {{0, 0}, {1, 0}, {2, 0}, {-1, 0}, {-2, 0}, {0, -1}};
    SRS_I_WallKickData[make_pair(3, 1)] = {{0, 0}, {0, 1}, {0, 2}, {0, -1}, {0, -2}, {1, 0}};
}
