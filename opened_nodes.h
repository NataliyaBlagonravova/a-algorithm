#ifndef _OPENED_NODES
#define _OPENED_NODES

#include "graph.h"
#include "help_calculations.h"

#include <queue>
#include <map>

using namespace std;

class TOpenedNodesContainer
{
private:
    struct TOpenNode {
        uint64_t Id;
        double EstimateFullPathLength;
    };

    class CompareByHeuristicEstimatePath
    {
    public:
        bool operator()(const TOpenNode &left, const TOpenNode &right) const
        {
            return (left.EstimateFullPathLength > right.EstimateFullPathLength);
        }
    };

    priority_queue <TOpenNode, vector<TOpenNode>, CompareByHeuristicEstimatePath> SortedNodes;
    map<uint64_t, double> PathLengthFromStart;

    uint64_t Size;

    uint64_t BestNodeId;
    double BestNodePathLengthFromStart;

public:
    TOpenedNodesContainer() {}
    void AddNode(uint64_t nodeId, double pathLengthFromStart, double heuristicCostEstimate);
    void FindNextBestNode();
    bool Contains(uint64_t nodeId);
    uint64_t GetBestNodeId();
    double GetBestNodePathLengthFromStart();
    double GetPathLengthFromStart(uint64_t nodeId);
    bool IsEmpty();

};


#endif