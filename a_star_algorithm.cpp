#include "a_star_algorithm.h"

TAStarAlgorithm::TAStarAlgorithm(TGraph *graph, uint64_t startNodeId, uint64_t finishNodeId, bool needFullOutput)
{
    Graph = graph;
    OpenNodes = new TOpenedNodesContainer();
    ClosedNodes = new TClosedNodesContainer();
    Path = new TPathContainer(Graph->GetNodeCount(), startNodeId, finishNodeId);

    StartNodeId = startNodeId;
    FinishNodeId = finishNodeId;

    NeedFullOutput = needFullOutput;

    SeenNodesCount = 0;

    Calculate();
}

double TAStarAlgorithm::HeuristicCostEstimate(const TNode start, const TNode finish)
{
    return CalculateDistance(start.Coordinates, finish.Coordinates);
}

void TAStarAlgorithm::Calculate()
{
    OpenNodes->AddNode(StartNodeId, 0, HeuristicCostEstimate(
                           Graph->GetNode(StartNodeId),
                           Graph->GetNode(FinishNodeId)));

    while (!OpenNodes->IsEmpty()) {
        OpenNodes->FindNextBestNode();

        uint64_t nodeId = OpenNodes->GetBestNodeId();
        double pathLengthFromStart = OpenNodes->GetBestNodePathLengthFromStart();

        ++SeenNodesCount;


        if (nodeId == FinishNodeId) {
            Path->PathWasFound(pathLengthFromStart);
            if (NeedFullOutput) {
                Path->ReconstructPath();
            }
            return;
        }

        ClosedNodes->AddNode(nodeId);

        for (TNeighbor neighbor : Graph->GetNode(nodeId).Neighbors) {
            if (ClosedNodes->Contains(neighbor.Id)) {
                continue;
            }

            double pathLengthFromStartThroughNode =
                pathLengthFromStart +
                neighbor.Distance;


            if (!OpenNodes->Contains(neighbor.Id)) {
                OpenNodes->AddNode(neighbor.Id, pathLengthFromStartThroughNode,
                                   HeuristicCostEstimate(
                                       Graph->GetNode(neighbor.Id),
                                       Graph->GetNode(FinishNodeId)));
                Path->SetNodeParent(neighbor.Id, nodeId);
            } else {
                if (pathLengthFromStartThroughNode < OpenNodes->GetPathLengthFromStart(neighbor.Id)) {
                    OpenNodes->AddNode(neighbor.Id, pathLengthFromStartThroughNode,
                                       HeuristicCostEstimate(
                                           Graph->GetNode(neighbor.Id),
                                           Graph->GetNode(FinishNodeId)));
                    Path->SetNodeParent(neighbor.Id, nodeId);
                }
            }

        }



    }

}


double TAStarAlgorithm::GetPathLength()
{
    return Path->GetLength();
}

bool TAStarAlgorithm::HasPath()
{
    return Path->HasPathFromStartToFinish();
}

vector<uint64_t> &TAStarAlgorithm::GetPath()
{
    return Path->GetPath();
}

uint64_t TAStarAlgorithm::GetPathNodeCount()
{
    return Path->GetNodeCount();
}

TAStarAlgorithm::~TAStarAlgorithm()
{
    delete OpenNodes;
    delete ClosedNodes;
    delete Path;
}

uint64_t TAStarAlgorithm::GetSeenNodesCount()
{
    return SeenNodesCount;
}
