#ifndef _IO_
#define _IO_

#include "graph.h"
#include "help_calculations.h"

#include <cmath>
#include <fstream>
#include <iostream>

using  namespace std;

static const int NO_PATH = -1;

struct TQuery {
    uint64_t Start;
    uint64_t Finish;
};

struct TReply {
    double PathLength;
    vector <uint64_t> VisitedNodes;
};

TGraph ReadProcessedGraph(ifstream &graphFile);
void WriteProcessedGraph(ofstream &graphFile, TGraph &graph);
TGraph ReadGraph(ifstream &graphFile);
uint64_t ReadQueriesCount(ifstream &queryFile);
TQuery ReadQuery(ifstream &queryFile);
void WritePathLength(ofstream &outputFile, double pathLength);
void WriteFullPathInfo(ofstream &outputFile, uint64_t nodeCount, vector<uint64_t> &path);

#endif