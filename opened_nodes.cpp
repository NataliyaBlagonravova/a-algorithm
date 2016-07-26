#include "opened_nodes.h"


void TOpenedNodesContainer::AddNode(uint64_t nodeId, double pathLengthFromStart, double heuristicCostEstimate)
{
    TOpenNode node;
    node.Id = nodeId;
    node.EstimateFullPathLength = pathLengthFromStart + heuristicCostEstimate;
    SortedNodes.push(node);
    PathLengthFromStart[nodeId] = pathLengthFromStart;
    ++Size;
}

void TOpenedNodesContainer::FindNextBestNode()
{
    TOpenNode node = SortedNodes.top();
    while (!Contains(node.Id)) {
        SortedNodes.pop();
        node = SortedNodes.top();
    }
    BestNodeId = node.Id;
    BestNodePathLengthFromStart = PathLengthFromStart[node.Id];

    SortedNodes.pop();
    PathLengthFromStart.erase(node.Id);
    --Size;
}

bool TOpenedNodesContainer::Contains(uint64_t nodeId)
{
    return PathLengthFromStart.find(nodeId) != PathLengthFromStart.end();
}

uint64_t TOpenedNodesContainer::GetBestNodeId()
{
    return BestNodeId;
}

double TOpenedNodesContainer::GetBestNodePathLengthFromStart()
{
    return BestNodePathLengthFromStart;
}

double TOpenedNodesContainer::GetPathLengthFromStart(uint64_t nodeId)
{
    return PathLengthFromStart[nodeId];
}

bool TOpenedNodesContainer::IsEmpty()
{
    return Size == 0;

}