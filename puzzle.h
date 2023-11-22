//Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#include "solution.h"


class Puzzle{
    public:
    //gets the option 
    void get_options(int argc, char **argv);

    //reads the the puzzle
    void read_input(Solution &s);

    //returns the solution
    void solve(Solution &s);

    //returns a string to help users 
    void help();
    
    
    
    private:
    
    //character determining if output should be map or list
    string output_mode = "\0";
    
    //character determining if we are using a queue or stack
    char q_or_s = '\0';

    vector<vector<char>> puzzle_map;
};