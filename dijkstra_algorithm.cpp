#include "dijkstra_algorithm.h"

TDijkstraAlgorithm::TDijkstraAlgorithm(TGraph *graph, uint64_t startNodeId, uint64_t finishNodeId, bool needFullOutput)
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

double TDijkstraAlgorithm::HeuristicCostEstimate(const TNode start, const TNode finish)
{
    return CalculateDistance(start.Coordinates, finish.Coordinates);
}

void TDijkstraAlgorithm::Calculate()
{
    OpenNodes->AddNode(StartNodeId, 0, 0);

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
                OpenNodes->AddNode(neighbor.Id, pathLengthFromStartThroughNode, 0);
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


double TDijkstraAlgorithm::GetPathLength()
{
    return Path->GetLength();
}

bool TDijkstraAlgorithm::HasPath()
{
    return Path->HasPathFromStartToFinish();
}

vector<uint64_t> &TDijkstraAlgorithm::GetPath()
{
    return Path->GetPath();
}

uint64_t TDijkstraAlgorithm::GetPathNodeCount()
{
    return Path->GetNodeCount();
}

TDijkstraAlgorithm::~TDijkstraAlgorithm()
{
    delete OpenNodes;
    delete ClosedNodes;
    delete Path;
}

uint64_t TDijkstraAlgorithm::GetSeenNodesCount()
{
    return SeenNodesCount;
}
