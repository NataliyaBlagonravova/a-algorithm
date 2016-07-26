#include "io.h"

TGraph ReadProcessedGraph(ifstream &graphFile)
{
    vector<TNode> nodes;

    uint64_t nodeCount;
    graphFile.read((char *)&nodeCount, sizeof(nodeCount));

    double longitude;
    double lattitude;
    uint64_t connectedComponentId;

    uint64_t neighborsCount;

    TNode fakeNode;
    nodes.push_back(fakeNode);

    for (int i = 1; i <= nodeCount; ++i) {
        graphFile.read((char *)&longitude, sizeof(longitude));
        graphFile.read((char *)&lattitude, sizeof(lattitude));
        graphFile.read((char *)&connectedComponentId, sizeof(connectedComponentId));

        TNode node;
        node.Coordinates.Longitude = longitude;
        node.Coordinates.Lattitude = lattitude;
        node.ConnectedComponentId = connectedComponentId;

        nodes.push_back(node);

        graphFile.read((char *)&neighborsCount, sizeof(neighborsCount));

        uint64_t neighborId;
        double distance;

        for (int j = 0; j < neighborsCount; ++j) {
            graphFile.read((char *)&neighborId, sizeof(neighborId));
            graphFile.read((char *)&distance, sizeof(distance));

            TNeighbor neighbor;

            neighbor.Id = neighborId;
            neighbor.Distance =  distance;

            nodes[i].Neighbors.push_back(neighbor);
        }

    }

    TGraph graph(nodes);
    return graph;

}

void WriteProcessedGraph(ofstream &graphFile, TGraph &graph)
{
    uint64_t nodeCount = graph.GetNodeCount();

    graphFile.write((char *)&nodeCount, sizeof(nodeCount));

    for (int i = 1; i <= nodeCount; ++i) {

        double longitude = graph.GetNode(i).Coordinates.Longitude;
        double lattitude = graph.GetNode(i).Coordinates.Lattitude;
        uint64_t connectedComponentId = graph.GetNode(i).ConnectedComponentId;

        graphFile.write((char *)&longitude, sizeof(longitude));
        graphFile.write((char *)&lattitude, sizeof(lattitude));
        graphFile.write((char *)&connectedComponentId, sizeof(connectedComponentId));

        uint64_t neighborsCount = graph.GetNode(i).Neighbors.size();

        graphFile.write((char *)&neighborsCount, sizeof(neighborsCount));

        uint64_t neighborId;
        double distance;

        for (int j = 0; j < neighborsCount; ++j) {
            neighborId = graph.GetNode(i).Neighbors[j].Id;
            distance = graph.GetNode(i).Neighbors[j].Distance;

            graphFile.write((char *)&neighborId, sizeof(neighborId));
            graphFile.write((char *)&distance, sizeof(distance));
        }

    }
}

TGraph ReadGraph(ifstream &graphFile)
{
    vector<TNode> nodes;

    uint64_t nodeCount;
    graphFile.read((char *)&nodeCount, sizeof(nodeCount));

    uint64_t edgeCount;
    graphFile.read((char *)&edgeCount, sizeof(edgeCount));

    double longitude;
    double lattitude;

    TNode fakeNode;
    nodes.push_back(fakeNode);

    for (int i = 0; i < nodeCount; ++i) {
        graphFile.read((char *)&longitude, sizeof(longitude));
        graphFile.read((char *)&lattitude, sizeof(lattitude));

        TNode node;
        node.Coordinates.Longitude = GetRadians(longitude);
        node.Coordinates.Lattitude = GetRadians(lattitude);

        nodes.push_back(node);
    }

    uint64_t nodeId;
    uint64_t neighborId;

    for (int i = 0; i < edgeCount; ++i) {
        graphFile.read((char *)&nodeId, sizeof(nodeId));
        graphFile.read((char *)&neighborId, sizeof(neighborId));

        TNeighbor neighbor;

        neighbor.Id = neighborId;
        neighbor.Distance =  CalculateDistance(nodes[nodeId].Coordinates, nodes[neighborId].Coordinates);

        nodes[nodeId].Neighbors.push_back(neighbor);
    }

    TGraph graph(nodes);
    graph.FindConnectedComponents();
    return graph;
}

TQuery ReadQuery(ifstream &queryFile)
{
    uint64_t start;
    uint64_t finish;

    queryFile.read((char *)&start, sizeof(start));
    queryFile.read((char *)&finish, sizeof(finish));

    TQuery query;
    query.Start = start;
    query.Finish = finish;

    return query;
}

uint64_t ReadQueriesCount(ifstream &queryFile)
{
    uint64_t queryCount;
    queryFile.read((char *)&queryCount, sizeof(queryCount));
    return queryCount;
}

void WritePathLength(ofstream &outputFile, double pathLength)
{
    outputFile.write((char *)&pathLength, sizeof(pathLength));
}

void WriteFullPathInfo(ofstream &outputFile, uint64_t nodeCount, vector<uint64_t> &path)
{
    outputFile.write((char *)&nodeCount, sizeof(nodeCount));
    for (int i = 0; i < nodeCount; ++i) {
        outputFile.write((char *)&path[i], sizeof(path[i]));
    }
}



