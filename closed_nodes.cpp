#include "closed_nodes.h"

void TClosedNodesContainer::AddNode(uint64_t nodeId)
{
    ClosedNodes.insert(nodeId);
}
bool TClosedNodesContainer::Contains(uint64_t nodeId)
{
    return ClosedNodes.find(nodeId) != ClosedNodes.end();
}

