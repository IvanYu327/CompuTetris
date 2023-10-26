#include "rotationSystem.h"
#include <map>
#include <vector>
#include <utility>

using namespace std;

SRSRotation::SRSRotation()
{
    Initialize();
}

vector<pair<int, int>> SRSRotation::GetRotationTests(int blockId, int startState, int EndState)
{
    pair<int, int> rotation = make_pair(startState, EndState);

    // I Block
    if (blockId == 1)
    {
        return iWallKickData[rotation];
    }
    else
    {
        return normalWallKickData[rotation];
    }
}

void SRSRotation::Initialize()
{
    normalWallKickData[make_pair(0, 1)] = {{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}};
    normalWallKickData[make_pair(1, 0)] = {{1, 0}, {1, -1}, {0, 2}, {1, 2}};
    normalWallKickData[make_pair(1, 2)] = {{1, 0}, {1, -1}, {0, 2}, {1, 2}};
    normalWallKickData[make_pair(2, 1)] = {{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}};
    normalWallKickData[make_pair(2, 3)] = {{1, 0}, {1, 1}, {0, -2}, {1, -2}};
    normalWallKickData[make_pair(3, 2)] = {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}};
    normalWallKickData[make_pair(3, 0)] = {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}};
    normalWallKickData[make_pair(0, 3)] = {{1, 0}, {1, 1}, {0, -2}, {1, -2}};
    normalWallKickData[make_pair(0, 2)] = {{1, 0}, {2, 0}, {1, 1}, {2, 1}, {-1, 0}, {-2, 0}, {-1, 1}, {-2, 1}, {0, -1}, {3, 0}, {-3, 0}};
    normalWallKickData[make_pair(1, 3)] = {{0, 1}, {0, 2}, {-1, 1}, {-1, 2}, {0, -1}, {0, -2}, {-1, -1}, {-1, -2}, {1, 0}, {0, 3}, {0, -3}};
    normalWallKickData[make_pair(2, 0)] = {{-1, 0}, {-2, 0}, {-1, -1}, {-2, -1}, {1, 0}, {2, 0}, {1, -1}, {2, -1}, {0, 1}, {-3, 0}, {3, 0}};
    normalWallKickData[make_pair(3, 1)] = {{0, 1}, {0, 2}, {1, 1}, {1, 2}, {0, -1}, {0, -2}, {1, -1}, {1, -2}, {-1, 0}, {0, 3}, {0, -3}};

    iWallKickData[make_pair(0, 1)] = {{-2, 0}, {1, 0}, {-2, -1}, {1, 2}};
    iWallKickData[make_pair(1, 0)] = {{2, 0}, {-1, 0}, {2, 1}, {-1, -2}};
    iWallKickData[make_pair(1, 2)] = {{-1, 0}, {2, 0}, {-1, 2}, {2, -1}};
    iWallKickData[make_pair(2, 1)] = {{1, 0}, {-2, 0}, {1, -2}, {-2, 1}};
    iWallKickData[make_pair(2, 3)] = {{2, 0}, {-1, 0}, {2, 1}, {-1, -2}};
    iWallKickData[make_pair(3, 2)] = {{-2, 0}, {1, 0}, {-2, -1}, {1, 2}};
    iWallKickData[make_pair(3, 0)] = {{1, 0}, {-2, 0}, {1, -2}, {-2, 1}};
    iWallKickData[make_pair(0, 3)] = {{-1, 0}, {2, 0}, {-1, 2}, {2, -1}};
    iWallKickData[make_pair(0, 2)] = {{-1, 0}, {-2, 0}, {1, 0}, {2, 0}, {0, 1}};
    iWallKickData[make_pair(1, 3)] = {{0, 1}, {0, 2}, {0, -1}, {0, -2}, {-1, 0}};
    iWallKickData[make_pair(2, 0)] = {{1, 0}, {2, 0}, {-1, 0}, {-2, 0}, {0, -1}};
    iWallKickData[make_pair(3, 1)] = {{0, 1}, {0, 2}, {0, -1}, {0, -2}, {1, 0}};
}
