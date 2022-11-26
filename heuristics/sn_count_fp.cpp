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

void Inner(vector<int> arr, vector<int> data, int start, int end, int index, int r, const vector<vector<int>>& neighbors, const vector<int>& threshold, int &num_fp);

void Enumerate(vector<int> arr, int n, int r, const vector<vector<int>>& neighbors, const vector<int>& threshold, int &num_fp)
{
    // A temporary array to store
    // all combination one by one
    vector<int> data(r);
    Inner(arr, data, 0, n-1, 0, r, neighbors, threshold, num_fp);
}

void Inner(vector<int> arr, vector<int> data, int start, int end, int index, int r, const vector<vector<int>>& neighbors, const vector<int>& threshold, int &num_fp)
{
    if (index == r)
    {
        int n = threshold.size();
        vector<int> C(n, 0);
        for (int j = 0; j < r; j++) C[data[j]] = 1;

        bool is_fp = 1;
        for(int u = 0; u < n; ++u)
        {
            int zu = 0;
            for(auto v : neighbors[u])
            {
                zu += (1 - C[v]);
            }
            if(zu >= threshold[u] && C[u] == 0)
            {
                is_fp = 0;
                break;
            }
            else if(zu < threshold[u] && C[u] == 1)
            {
                is_fp = 0;
                break;
            }
        }
        if(is_fp)
        {
            //cout<<"A FP is found"<<endl;
            num_fp++;
        }
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        Inner(arr, data, i+1, end, index+1, r, neighbors, threshold, num_fp);
    }
}

int main(int argc, char *argv[])
{  

    string network_file = "../networks/random/gnp_20/gnp_20.edges";

    string thresh_file = "../networks/random/gnp_20/gnp_20_random_thresh.txt";
        
    // Read in the SyDS
    Syds S;
    S = construct_network(network_file, thresh_file); 

    int n = S.threshold.size();
    
    // Each vertex do not consider own state
    for(int u = 0; u != n; ++u)
    {
        S.neighbors[u].erase(remove(S.neighbors[u].begin(), S.neighbors[u].end(), u), S.neighbors[u].end());
    }
    
    vector<int> v(n);
    iota(v.begin(), v.end(), 0); //[0, 1, ..., n-1]

    int num_fp = 0;
    
    // Enumerate all configurations
    for(int i = 1; i <= n; ++i)
    {    
        Enumerate(v, v.size(), i, S.neighbors, S.threshold, num_fp);
    } 

    cout<<"The number of NE under the self non-essential scheme: "<<num_fp<<endl;

    return 0;
}
