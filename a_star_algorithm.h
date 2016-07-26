#ifndef _A_STAR_ALGORITHM
#define _A_STAR_ALGORITHM

#include "graph.h"
#include "opened_nodes.h"
#include "closed_nodes.h"
#include "path.h"
#include "help_calculations.h"

#include <cmath>
#include <cstdint>

using namespace std;

class TAStarAlgorithm
{
private:
    TGraph *Graph;
    TOpenedNodesContainer *OpenNodes;
    TClosedNodesContainer *ClosedNodes;

    TPathContainer *Path;

    bool NeedFullOutput;

    uint64_t StartNodeId;
    uint64_t FinishNodeId;

    uint64_t SeenNodesCount;

    double HeuristicCostEstimate(const TNode start, const TNode finish);
    void Calculate();

public:
    TAStarAlgorithm(TGraph *graph, uint64_t startNodeId, uint64_t finishNodeId, bool needFullOutput);
    bool HasPath();
    double GetPathLength();
    uint64_t GetSeenNodesCount();
    vector<uint64_t> &GetPath();
    uint64_t GetPathNodeCount();
    ~TAStarAlgorithm();

};

#endif