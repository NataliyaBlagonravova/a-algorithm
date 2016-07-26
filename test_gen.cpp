#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        cout << "Error" << endl;
        exit(0);
    }

    ofstream query(argv[1]);

    uint64_t query_size  = 10000;

    query.write((char *)&query_size, sizeof(query_size));

    for (uint64_t i = 1; i < query_size + 1; ++i) {
        uint64_t nodeId = i;
        query.write((char *)&nodeId, sizeof(nodeId));
        ++nodeId;
        query.write((char *)&nodeId, sizeof(nodeId));
    }

    query.close();
    return 0;
}