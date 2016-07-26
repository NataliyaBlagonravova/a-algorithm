#ifndef _PATH
#define _PATH

#include "graph.h"
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

static const uint64_t HAS_NOT_PARENT = -1;

class TPathContainer
{
private:
    map <uint64_t, uint64_t> Parents;
    vector<uint64_t> Path;

    uint64_t StartNodeId;
    uint64_t FinishNodeId;

    bool HasPath;
    double PathLength;

public:
    TPathContainer(uint64_t size, uint64_t startNodeId, uint64_t finishNodeId);
    void SetNodeParent(uint64_t nodeId, uint64_t patentId);
    void ReconstructPath();
    vector<uint64_t> &GetPath();
    double GetLength();
    uint64_t GetNodeCount();
    uint64_t HasPathFromStartToFinish();
    void PathWasFound(double length);
};


#endif