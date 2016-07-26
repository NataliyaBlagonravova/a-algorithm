#include "path.h"

void TPathContainer::ReconstructPath()
{
    uint64_t nodeId = FinishNodeId;
    while (nodeId != HAS_NOT_PARENT) {
        Path.push_back(nodeId);
        nodeId = Parents[nodeId];
    }

    reverse(Path.begin(), Path.end());
}

TPathContainer::TPathContainer(uint64_t size, uint64_t startNodeId, uint64_t finishNodeId)
{
    StartNodeId = startNodeId;
    FinishNodeId = finishNodeId;

    Parents[StartNodeId] = HAS_NOT_PARENT;

    HasPath = false;
}

void TPathContainer::SetNodeParent(uint64_t nodeId, uint64_t patentId)
{
    Parents[nodeId] = patentId;
}

vector<uint64_t> &TPathContainer::GetPath()
{
    return Path;
}

double TPathContainer::GetLength()
{
    return PathLength;
}

uint64_t TPathContainer::GetNodeCount()
{
    return Path.size();
}

uint64_t TPathContainer::HasPathFromStartToFinish()
{
    return HasPath;
}

void TPathContainer::PathWasFound(double length)
{
    HasPath = true;
    PathLength = length;
}

