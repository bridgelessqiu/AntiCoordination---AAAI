## Directory structure
- **heuristics**: contains code for system evolution and counting fixed points
- **networks**: contains selected networks


## Recompile the program (if needed): 
1. g++ -std=c++11 -O3 heuristic.cpp other_function.cpp se_convergence.cpp -o se_convergence
2. g++ -std=c++11 -O3 heuristic.cpp other_function.cpp sn_convergence.cpp -o sn_convergence
3. g++ -std=c++11 -O3 heuristic.cpp other_function.cpp se_count_fp.cpp -o se_count_fp
4. g++ -std=c++11 -O3 heuristic.cpp other_function.cpp sn_count_fp.cpp -o sn_count_fp


Parameters:
- network_type: random, real
- network_name: power_10000, gnp_10000, small_world_10000 (random networks)
                astroph, deezer, google_plus (real networks)

To run self essential dynamics (SE) from a randomly generated initial configuration:
1. cd heuristics/
2. ./se_convergence network_type network_name
     
    Example: to run the SE dynamics on the gnp network of size 10,000:
             ./se_convergence random gnp_10000

             to run the SE dynamics on the astroph network:
             ./se_convergence real astroph

To run self non-essential (SN) dynamics from a randomly generated initial configuration:
1. cd heuristics/
2. ./sn_convergence network_type network_name
    
    Example: to run the SN dynamics on the gnp network of size 10,000:
             ./sn_convergence random gnp_10000

             to run the SN dynamics on the astroph network:
             ./sn_convergence real astroph

To count the number of NE in the provided example instance under the SE scheme:
1. cd heuristics/
2. ./se_count_fp

To count the number of NE in the provided example instance under the SN scheme:
1. cd heuristics/
2. ./sn_count_fp
