#ifndef _CLOSED_NODES
#define _CLOSED_NODES

#include "graph.h"
#include <set>

class TClosedNodesContainer
{
private:
    set <uint64_t> ClosedNodes;
public:
    TClosedNodesContainer() {}
    void AddNode(uint64_t nodeId);
    bool Contains(uint64_t nodeId);
};

using namespace std;



#endif