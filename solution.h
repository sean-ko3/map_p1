//A8A3A33EF075ACEF9B08F5B9845569ECCB423725
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class Solution{
    public:

    struct Coordinates{
        uint32_t x;
        uint32_t y;
        char color;
    };

    //function that tells me what to do using integers (0: stop going through w path 1: its a door or '.' 2: we landed on a color button)
    bool should_be_in_search(const uint32_t &x, const uint32_t &y, const char &color, const vector<vector<char>> &maze);
    
    //using a Breadth First Search, using DFS or BFS basedon on qs
    void solve_search(const vector<vector<char>> &maze, const char &qs);
    
    //output_mode takes in qs and determines whether to output the solution in list/map version
    void output(string out_mode, const vector<vector<char>> &maze);

    void no_solution(const vector<vector<char>> &maze);

    bool trace_empty = false;
    
   
    uint32_t num_colors;
    uint32_t height;
    uint32_t width;
    Coordinates start_coord;
    Coordinates end_coord;

    private:
    vector<vector<vector<char>>> backtracer;

    vector <Coordinates> trace;

    void list_output();

    void map_output(const vector<vector<char>> &maze);


};