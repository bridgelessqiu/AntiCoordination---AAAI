// Memoryful - self essential
// Memoryless - self non-essential

#include "heuristic.h"
#include "syds.h"
#include<list>
#include<queue>
#include<unordered_map>
#include <chrono>
#include<cstdlib>
#include<random>
#include<numeric>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

/* ---------------------------------------------------------------- *
 * Synchronous update from C to convergence for the memoryful game  *
 * ---------------------------------------------------------------- */
NN SynchronousUpdateMemoryful2(const vector<vector<int>>& neighbors, const vector<int> threshold, vector<int> C)
{
    int n = threshold.size(); // The number of vertices

    NN N; // Keep track

    int avg_v_change = 0;

    int num_of_time_steps = 1; // The number of time-steps until convergence
    
    vector<int> C_prime (n, 0); // The successor of C
    vector<int> C_prev(C.begin(), C.end()); // Used to determine if a 2-cycle is reached
    vector<int> num_of_zeros(n, 0); // num_of_zeros[v]: the # 0's in the closed neighborhood of v
    vector<int> change_of_zeros(n, 0); // change_of_zeros[v]: the change of #0's after a update
    
    for(int u = 0; u != n; ++u)
    {
        for(auto v : neighbors[u])
        {
            num_of_zeros[u] += (1 - C[v]); // count the #0's in the closed neighborhood
        }

        if(num_of_zeros[u] >= threshold[u])
        {
            C_prime[u] = 1;
        }
        else
        {
            C_prime[u] = 0;
        }

        if(C_prime[u] != C[u]) // state changes
        {
            if(C_prime[u] == 0)
            {
                for(auto w : neighbors[u]) change_of_zeros[w]++;
            }
            else
            {
                for(auto w : neighbors[u]) change_of_zeros[w]--;
            }
        }
    }
 
    bool fixed_point_converged = true; 
    bool two_cycle_converged = false; 
   
    // Update C
    for(int u = 0; u != n; ++u)
    {
        if(C[u] != C_prime[u])
        {
            fixed_point_converged = false;
        }
        C[u] = C_prime[u];
    }

    num_of_time_steps++;

    if(fixed_point_converged)
    {
        cout<<"---------------------------------------"<<endl;
        cout<<"Number of time-steps (Self essential): "<<num_of_time_steps<<endl;
        cout<<"---------------------------------------\n\n";

        cout<<"The initial configuration C is a fixed point."<<endl;

        N.n_step = num_of_time_steps;
        N.n_vertex_change = 0;

        return N;
    }

    while(!fixed_point_converged && !two_cycle_converged)
    {
        
        num_of_time_steps++;
        for(int u = 0; u != n; ++u)
        {
            num_of_zeros[u] += change_of_zeros[u];
            change_of_zeros[u] = 0; // IMPORANT, need to reset to 0
        }
    
        fixed_point_converged = true;

        // Update C', determine if a fixed point is reached
        for(int u = 0; u != n; ++u)
        {
            if(num_of_zeros[u] >= threshold[u])
            {
                C_prime[u] = 1;
            }
            else
            {
                C_prime[u] = 0;
            }

            if(C_prime[u] != C[u]) //state changes
            {
                fixed_point_converged = false;

                if(C_prime[u] == 0)
                {
                    for(auto w : neighbors[u]) change_of_zeros[w]++;
                }
                else
                {
                    for(auto w : neighbors[u]) change_of_zeros[w]--;
                }
            }
        }

        // Update C, Check if a two cycle is reached
        two_cycle_converged = true;
        
        // Check if a 2-cycle is reached, update C and C_prev
        for(int u = 0; u != n; ++u)
        {
            if(C_prime[u] != C_prev[u]) 
            {
                avg_v_change++;
                two_cycle_converged = false;
            }

            C_prev[u] = C[u];

            C[u] = C_prime[u];
        }

    }
    
    cout<<"---------------------------------------"<<endl;
    cout<<"Number of time-steps (Self essential): "<<num_of_time_steps<<endl;
    cout<<"---------------------------------------\n\n";

    if(fixed_point_converged) cout<<"A fixed point is reached"<<endl;
    else if(two_cycle_converged) cout<<"A 2-cycle is reached"<<endl;

    N.n_step = num_of_time_steps;
    N.n_vertex_change = avg_v_change / num_of_time_steps;    

    return N;
}


/* ---------------------------------------------------------------- *
 * Synchronous update from C to convergence for the memoryful game  *
 * ---------------------------------------------------------------- */
vector<int> SynchronousUpdateMemoryful(const vector<vector<int>>& neighbors, const vector<int> threshold, vector<int> C)
{
    int n = threshold.size(); // The number of vertices

    int num_of_time_steps = 1; // The number of time-steps until convergence
    
    vector<int> C_prime (n, 0); // The successor of C
    vector<int> C_prev(C.begin(), C.end()); // Used to determine if a 2-cycle is reached
    vector<int> num_of_zeros(n, 0); // num_of_zeros[v]: the # 0's in the closed neighborhood of v
    vector<int> change_of_zeros(n, 0); // change_of_zeros[v]: the change of #0's after a update
    
    for(int u = 0; u != n; ++u)
    {
        for(auto v : neighbors[u])
        {
            num_of_zeros[u] += (1 - C[v]); // count the #0's in the closed neighborhood
        }

        if(num_of_zeros[u] >= threshold[u])
        {
            C_prime[u] = 1;
        }
        else
        {
            C_prime[u] = 0;
        }

        if(C_prime[u] != C[u]) // state changes
        {
            if(C_prime[u] == 0)
            {
                for(auto w : neighbors[u]) change_of_zeros[w]++;
            }
            else
            {
                for(auto w : neighbors[u]) change_of_zeros[w]--;
            }
        }
    }
 
    bool fixed_point_converged = true; 
    bool two_cycle_converged = false; 
   
    // Update C
    for(int u = 0; u != n; ++u)
    {
        if(C[u] != C_prime[u]) fixed_point_converged = false;
        C[u] = C_prime[u];
    }

    if(fixed_point_converged)
    {
        cout<<"---------------------------------------"<<endl;
        cout<<"Number of time-steps (Self essential): "<<num_of_time_steps<<endl;
        cout<<"---------------------------------------\n\n";

        cout<<"The initial configuration C is a fixed point."<<endl;
        return C;
    }

    num_of_time_steps++;

    while(!fixed_point_converged && !two_cycle_converged)
    {
        num_of_time_steps++;
        for(int u = 0; u != n; ++u)
        {
            num_of_zeros[u] += change_of_zeros[u];
            change_of_zeros[u] = 0; // IMPORANT, need to reset to 0
        }
    
        fixed_point_converged = true;

        // Update C', determine if a fixed point is reached
        for(int u = 0; u != n; ++u)
        {
            if(num_of_zeros[u] >= threshold[u])
            {
                C_prime[u] = 1;
            }
            else
            {
                C_prime[u] = 0;
            }

            if(C_prime[u] != C[u]) //state changes
            {
                fixed_point_converged = false;

                if(C_prime[u] == 0)
                {
                    for(auto w : neighbors[u]) change_of_zeros[w]++;
                }
                else
                {
                    for(auto w : neighbors[u]) change_of_zeros[w]--;
                }
            }
        }

        // Update C, Check if a two cycle is reached
        two_cycle_converged = true;
        
        // Check if a 2-cycle is reached, update C and C_prev
        for(int u = 0; u != n; ++u)
        {
            if(C_prime[u] != C_prev[u]) two_cycle_converged = false;

            C_prev[u] = C[u];

            C[u] = C_prime[u];
        }

    }
    
    cout<<"---------------------------------------"<<endl;
    cout<<"Number of time-steps (Self essential): "<<num_of_time_steps<<endl;
    cout<<"---------------------------------------\n\n";

    if(fixed_point_converged) cout<<"A fixed point is reached"<<endl;
    else if(two_cycle_converged) cout<<"A 2-cycle is reached"<<endl;

    //return num_of_time_steps;
    return C;
}

/* -------------------------------------------------------------- *
 * Synchronous update from C to convergence for memoryless games  *
 * -------------------------------------------------------------- */
NN SynchronousUpdateMemoryless(vector<vector<int>>& neighbors, const vector<int> threshold, vector<int> C)
{
    int n = threshold.size(); // The number of vertices

    // Own state is not considered
    for(int u = 0; u != n; ++u)
    {
        neighbors[u].erase(remove(neighbors[u].begin(), neighbors[u].end(), u), neighbors[u].end()); 
    }

    int num_of_time_steps = 1; // The number of time-steps until convergence

    NN N; // Keep track

    int avg_v_change = 0;
    
    vector<int> C_prime (n, 0); // The successor of C
    vector<int> C_prev(C.begin(), C.end()); // Used to determine if a 2-cycle is reached
    vector<int> num_of_zeros(n, 0); // num_of_zeros[v]: the # 0's in the closed neighborhood of v
    vector<int> change_of_zeros(n, 0); // change_of_zeros[v]: the change of #0's after a update
    
    for(int u = 0; u != n; ++u)
    {
        for(auto v : neighbors[u])
        {
            num_of_zeros[u] += (1 - C[v]); // count the #0's in the closed neighborhood
        }

        if(num_of_zeros[u] >= threshold[u])
        {
            C_prime[u] = 1;
        }
        else
        {
            C_prime[u] = 0;
        }

        if(C_prime[u] != C[u]) // state changes
        {
            if(C_prime[u] == 0)
            {
                for(auto w : neighbors[u]) change_of_zeros[w]++;
            }
            else
            {
                for(auto w : neighbors[u]) change_of_zeros[w]--;
            }
        }
    }
 
    bool fixed_point_converged = true; 
    bool two_cycle_converged = false; 
   
    // Update C
    for(int u = 0; u != n; ++u)
    {
        if(C[u] != C_prime[u]) fixed_point_converged = false;
        C[u] = C_prime[u];
    }
    if(fixed_point_converged)
    {
        cout<<"The initial configuration C is a fixed point."<<endl;
        N.n_step = num_of_time_steps;
        N.n_vertex_change = 0;

        return N;
    }

    num_of_time_steps++;

    while(!fixed_point_converged && !two_cycle_converged)
    {
        num_of_time_steps++;
        for(int u = 0; u != n; ++u)
        {
            num_of_zeros[u] += change_of_zeros[u];
            change_of_zeros[u] = 0; // IMPORANT, need to reset to 0
        }
    
        fixed_point_converged = true;

        // Update C', determine if a fixed point is reached
        for(int u = 0; u != n; ++u)
        {
            if(num_of_zeros[u] >= threshold[u])
            {
                C_prime[u] = 1;
            }
            else
            {
                C_prime[u] = 0;
            }

            if(C_prime[u] != C[u]) //state changes
            {
                fixed_point_converged = false;

                if(C_prime[u] == 0)
                {
                    for(auto w : neighbors[u]) change_of_zeros[w]++;
                }
                else
                {
                    for(auto w : neighbors[u]) change_of_zeros[w]--;
                }
            }
        }

        // Update C, Check if a two cycle is reached
        two_cycle_converged = true;
        
        // Check if a 2-cycle is reached, update C and C_prev
        for(int u = 0; u != n; ++u)
        {
            if(C_prime[u] != C_prev[u]) 
            {
                two_cycle_converged = false;
                avg_v_change++;
            }

            C_prev[u] = C[u];

            C[u] = C_prime[u];
        }
    }
    
    cout<<"---------------------------------------"<<endl;
    cout<<"Number of time-steps (Self non-essential)  : "<<num_of_time_steps<<endl;
    cout<<"---------------------------------------\n\n";

    if(fixed_point_converged) cout<<"A fixed point is reached"<<endl;
    else if(two_cycle_converged) cout<<"A 2-cycle is reached"<<endl;

    N.n_step = num_of_time_steps;
    N.n_vertex_change = avg_v_change / (num_of_time_steps - 1);

    return N;
}

