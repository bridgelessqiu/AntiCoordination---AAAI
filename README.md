# Nash and Convergence of Anti-coordination Games
Paper: *Networked Anti-Coordination Games Meet Graphical Dynamical Systems: Equilibria and Convergence*
<br/>
**Full version** (contains complete proofs of theorems): [https://arxiv.org/pdf/2301.02889.pdf]



## Directory structure
- **heuristics**: contains code for system evolution and counting fixed points
- **networks**: contains selected networks


## Recompile the program (if needed): 
1. `g++ -std=c++11 -O3 heuristic.cpp other_function.cpp se_convergence.cpp -o se_convergence`
2. `g++ -std=c++11 -O3 heuristic.cpp other_function.cpp sn_convergence.cpp -o sn_convergence`
3. `g++ -std=c++11 -O3 heuristic.cpp other_function.cpp se_count_fp.cpp -o se_count_fp`
4. `g++ -std=c++11 -O3 heuristic.cpp other_function.cpp sn_count_fp.cpp -o sn_count_fp`


## Parameters
- **network_type**: random, real
- **network_name**: 
    * power_10000, gnp_10000, small_world_10000 (random networks)
    * astroph, deezer, google_plus (real networks)

## Examples

### Self essential dynamics (SE) from a randomly generated initial configuration:
1. `cd heuristics/`
2. `./se_convergence network_type network_name`

For example:
- SE dynamics on the gnp network of size 10,000: `./se_convergence random gnp_10000`

- SE dynamics on the astroph network: `./se_convergence real astroph`

### Self non-essential (SN) dynamics from a randomly generated initial configuration:
1. `cd heuristics/`
2. `./sn_convergence network_type network_name`
    
For example: 
- SN dynamics on the gnp network of size 10,000: `./sn_convergence random gnp_10000`

- SN dynamics on the astroph network: `./sn_convergence real astroph`

### Count the number of NE in the provided example instance under the SE Scheme:
1. `cd heuristics/`
2. `./se_count_fp`

### Count the number of NE in the provided example instance under the SN Scheme:
1. `cd heuristics/`
2. `./sn_count_fp`
