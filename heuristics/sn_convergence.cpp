#include "other_function.h"
#include "heuristic.h"
#include "syds.h"
#include<algorithm>
#include<math.h>
#include<iostream>
#include<cstdlib>
#include<unordered_map>
#include<string>
#include<vector>
#include<random>
#include<fstream>

using namespace std;

int main(int argc, char *argv[])
{   
    string network_type = argv[1]; // real, random
    string network_name = argv[2]; // google_plus, gnp ...

    string network_file = "../networks/" + network_type + "/" + network_name + "/" + network_name + ".edges";
    
    string thresh_file = "../networks/" + network_type + "/" + network_name + "/" + network_name + "_random_thresh_memoryless.txt";
    
    // Read in the SyDS
    Syds S;
    S = construct_network(network_file, thresh_file); 

    int n = S.threshold.size();

    // Construct a random initial configuration C
    random_device rd{};
    mt19937 rng{rd()};
    bernoulli_distribution d(0.5);

    vector<int>C (n, 0);
    for(int i = 0; i < n; ++i) C[i] = (int)d(rng);
    
    NN N = SynchronousUpdateMemoryless(S.neighbors, S.threshold, C);

    return 0;
}
