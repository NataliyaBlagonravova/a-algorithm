#include "graph.h"

TGraph::TGraph() {}

TGraph::TGraph(vector<TNode> &nodes)
{
    Nodes = move(nodes);
}

TGraph::TGraph(const TGraph &graph)
{
    Nodes = move(graph.Nodes);
}

TNode &TGraph::GetNode(uint64_t nodeId)
{
    return Nodes[nodeId];
}

uint64_t TGraph::GetNodeCount()
{
    return Nodes.size() - 1; // first node in vector is fake
}

void TGraph::FindConnectedComponents()
{
    uint64_t nodeCount = GetNodeCount();
    vector<bool> vesited(nodeCount + 1, false);

    uint64_t componentId = 0;
    for (int i = 1; i <= nodeCount; ++i)
        if (!vesited[i]) {
            DFS(i, componentId, vesited);
            ++componentId;
        }
}


void  TGraph::DFS(uint64_t startNodeId, uint64_t componentId, vector<bool> &vesited)
{
    stack<uint64_t> stack;
    stack.push(startNodeId);

    uint64_t nodeId;

    while (!stack.empty()) {
        nodeId = stack.top();
        stack.pop();
        Nodes[nodeId].ConnectedComponentId = componentId;
        //cout << nodeId << ": " <<  Nodes[nodeId].ConnectedComponentId << endl;
        if (!vesited[nodeId]) {
            vesited[nodeId] = true;
            for (TNeighbor neighbor : Nodes[nodeId].Neighbors) {
                stack.push(neighbor.Id);
            }
        }
    }
}

bool TGraph::NodesInOneConnectedComponent(uint64_t startNodeId, uint64_t finishNodeId)
{
    return Nodes[startNodeId].ConnectedComponentId == Nodes[finishNodeId].ConnectedComponentId;
}
