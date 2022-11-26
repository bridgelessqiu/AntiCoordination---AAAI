#ifndef SYDS_H_06210354
#define SYDS_H_06210354

#include<vector>
#include<unordered_map>
#include<string>

struct Syds
{
    std::vector<std::vector<int>> neighbors;

    std::vector<int> threshold;
    
    std::unordered_map<std::string, int> name_id_mapping; //[name : id]
};

struct Pack
{
    std::vector<int> CC;
    
    bool is_fp;

    int same_states;
};

struct NN
{
    int n_step;
    int n_vertex_change;
};

#endif
