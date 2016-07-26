#include <iostream>
#include <cstring>

#include "graph.h"
#include "a_star_algorithm.h"
#include "dijkstra_algorithm.h"
#include "io.h"

using namespace std;


void Help(char *progName)
{
    cout << "Usage: " << endl;
    cout << progName << " preprocess --input <input file> --output <preprocessed graph>" << endl;
    cout << progName << " search --graph <preprocessed graph> --input <input file> --output <output file> [--full-output]" << endl;

}

int main(int argc, char **argv)
{
    if (argc != 6 && argc != 8 && argc != 9) {
        Help(argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "preprocess")) {

        if (!strcmp(argv[2], "--input") && !strcmp(argv[4], "--output")) {
            ifstream graphFile(argv[3], ios::binary);

            if (!graphFile) {
                cerr << "Error: Graph file not found" << endl;
                return 2;
            }

            ofstream preprocessedGraph(argv[5], ios::binary);

            TGraph graph;
            graph = ReadGraph(graphFile);
            WriteProcessedGraph(preprocessedGraph, graph);

            graphFile.close();
            preprocessedGraph.close();

        } else {
            Help(argv[0]);
            return 1;
        }

    } else if (!strcmp(argv[1], "search")) {
        if (!strcmp(argv[2], "--graph") && !strcmp(argv[4], "--input") && !strcmp(argv[6], "--output")) {
            ifstream graphFile(argv[3], ios::binary);
            ifstream queryFile(argv[5], ios::binary);

            if (!graphFile) {
                cerr << "Error: Graph file not found" << endl;
                return 2;
            }

            if (!queryFile) {
                cerr << "Error: Query file not found" << endl;
                return 2;
            }

            ofstream outputFile(argv[7], ios::binary);

            bool needFullOutput = false;
            if (argc == 9 && !strcmp(argv[8], "--full-output")) {
                needFullOutput = true;
            }

            TGraph graph;
            graph = ReadProcessedGraph(graphFile);

            uint64_t queryCount = ReadQueriesCount(queryFile);

            for (int i = 0; i < queryCount; ++i) {
                TQuery query = ReadQuery(queryFile);

                double pathLength;
                if (!graph.NodesInOneConnectedComponent(query.Start, query.Finish)) {
                    pathLength = NO_PATH;
                    //cout <<  NO_PATH << endl;
                    WritePathLength(outputFile, pathLength);

                } else {
                    TAStarAlgorithm findAlgorithm(&graph, query.Start, query.Finish, needFullOutput);

                    pathLength =  findAlgorithm.GetPathLength();
                    //   cout <<  pathLength << endl;
                    WritePathLength(outputFile, pathLength);

                    if (needFullOutput) {
                        uint64_t nodeCount = findAlgorithm.GetPathNodeCount();
                        vector<uint64_t> path = findAlgorithm.GetPath();

                        WriteFullPathInfo(outputFile, nodeCount, path);

                        // cout << findAlgorithm.GetPathNodeCount() << endl;
                        // for (uint64_t nodeId : path) {
                        //     cout << nodeId << " ";
                        // }
                        // cout << endl;
                    }
                }

            }

            graphFile.close();
            queryFile.close();
            outputFile.close();

        } else {
            Help(argv[0]);
            return 1;
        }

    } else if (!strcmp(argv[1], "benchmark")) {
        if (!strcmp(argv[2], "--graph") && !strcmp(argv[4], "--input")) {
            ifstream graphFile(argv[3], ios::binary);
            ifstream queryFile(argv[5], ios::binary);

            if (!graphFile) {
                cerr << "Error: Graph file not found" << endl;
                return 2;
            }

            if (!queryFile) {
                cerr << "Error: Query file not found" << endl;
                return 2;
            }


            bool needFullOutput = false;

            TGraph graph;
            graph = ReadProcessedGraph(graphFile);

            uint64_t queryCount = ReadQueriesCount(queryFile);
            cout << queryCount << endl;

            for (int i = 0; i < queryCount; ++i) {
                TQuery query = ReadQuery(queryFile);

                double pathLength;
                if (!graph.NodesInOneConnectedComponent(query.Start, query.Finish)) {
                    pathLength = NO_PATH;
                    cout << NO_PATH << endl << 0 << endl << 0 << endl;
                } else {
                    TDijkstraAlgorithm dijkstraAlgorithm(&graph, query.Start, query.Finish, needFullOutput);
                    pathLength =  dijkstraAlgorithm.GetPathLength();
                    cout <<  pathLength << endl;
                    cout << dijkstraAlgorithm.GetSeenNodesCount() << endl;

                    TAStarAlgorithm aStarAlgorithm(&graph, query.Start, query.Finish, needFullOutput);
                    cout  << aStarAlgorithm.GetSeenNodesCount() << endl;
                }

            }

            graphFile.close();
            queryFile.close();

        } else {
            Help(argv[0]);
            return 1;
        }




    }    else {
        Help(argv[0]);
        return 1;
    }

    return 0;
}