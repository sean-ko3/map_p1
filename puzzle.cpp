//Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725

//main driver
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "puzzle.h"
#include <cctype>


//a vector of all valid characters
//(the colors will be added later because it is dependent on the # of colors)

void Puzzle::help(){
    cout << "Important Information to know: \n";
}

void Puzzle::get_options(int argc, char **argv){
  int choice;
  int option_index = 0;



option long_options[] = {
    //all the different types of commands accepted
    {"output", required_argument,   nullptr, 'o' },
    {"help",   no_argument,         nullptr, 'h' },
    {"queue",  no_argument,         nullptr, 'q' },
    {"stack",  no_argument,         nullptr, 's' },
    { nullptr, 0,                   nullptr, '\0'},
  };
  // long_options[]

   while ((choice = getopt_long(argc, argv, "o:hqs", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
            help();
            break;

            case 'q':
            if (q_or_s != '\0'){ //making sure q_or_s is empty 
                cerr << "Error: only one (queue or stack) can be chosen!";
                exit(1);
            }
            q_or_s = 'q';

            break;

            case 's':
            if (q_or_s != '\0'){ //making sure q_or_s is empty 
                cerr << "Error: only one (queue or stack) can be chosen!";
                exit(1);
            }
            q_or_s = 's';

            break;

            case 'o':
            
            output_mode = optarg;
            if(output_mode != "list" &&  output_mode != "map"){
                 cerr <<" Error: output_mode needs to be fixed\n";
            }
            break;
        

            default:
            cerr << "Error: invalid option";
            exit(1);
        }
    }
}

bool is_comment(const string &input){
    return input.find("//") == 0;
}
//reading from file specified on the command line
//parameters are a Solution object and a 2D array
//putting Solution in parameter because we need to know # of colors and parameter of the 

void Puzzle::read_input(Solution &s) {
    cin >> s.num_colors;
    cin >> s.height;
    cin >> s.width;

    //input checks 
    if((s.height) < 1 || (s.width) < 1){
        cerr << "dimensions must both be >= 1";
        exit(1);
    }
    if (s.num_colors > 26 || static_cast<int> (s.num_colors) < 0){
        cerr << " num colors must be between 0 and 26 inclusive";
        exit(1);
    }

    //need to have counters for @ and ? because they only should appear once
    int start_counter = 0; // for @
    int end_counter = 0; // for ?

    //reserving the amount of rows
    puzzle_map.resize(s.height);

    
    string comments;
    getline(cin, comments); // Read the newline after the dimensions
    uint32_t j = 0;

    while (getline(cin, comments)) {
        if (is_comment(comments)) {
            continue;
            
        }
        else{
            vector<char> row;
            for (uint32_t i = 0; i < s.width; i++){
                row.resize(s.width);
                
                row[i] = comments[i];
                
                if(row[i] >= 'A' && row[i] <= 'Z'){
                    if(static_cast<uint32_t>(tolower(row[i]) - 'a') >= s.num_colors){
                        cerr << "Invalid Character \n" << row[i] << static_cast<uint32_t>(tolower(row[i]));
                        exit(1);
                    }
                }

                else if (row[i] >= 'a' && row[i] <= 'z'){
                    if(static_cast<uint32_t>(row[i] - 'a') >= s.num_colors){
                        cerr << "Invalid Character \n" << row[i];
                        exit(1);
                    }
                }
                

                else if(row[i] == '@'){
                        start_counter++;
                        s.start_coord.x = j;
                        s.start_coord.y = i;
                        s.start_coord.color = '^';
                    }

                else if (row[i] == '?'){
                        end_counter++;
                    }

                else if(row[i] == '#' || row[i] == '^' || row[i] == '.'){
                }
                
                else{
                    cerr << "Invalid Character! " << row[i];
                    exit(1);
                }
            }
            puzzle_map[j] = row;
            j++;
        }
      
        
    }

    //checking both the start @ and end ? only appears once
    if(start_counter > 1 || end_counter > 1 || start_counter == 0 || end_counter == 0){
        cerr << "Error: @ and ? only should appear once";
        exit(1);
    }
}


//creates a Solution class
//calls whatever type of Solution (stack or queue)
//calls how the solution should be presented (list / map)

void Puzzle::solve(Solution &s){
    s.solve_search(puzzle_map, q_or_s);
   
    //if no solution call no solution
    if(s.trace_empty == true){
        s.no_solution(puzzle_map);
    }
    else{
    s.output(output_mode, puzzle_map);
    }
}


int main(int argc, char *argv[]) {
  // This should be in all of your projects, speeds up I/O
  ios_base::sync_with_stdio(false);
  
  //create an object called Puzzle
  Puzzle puz;
  Solution result; 
  puz.get_options(argc, argv);
  puz.read_input(result);

  puz.solve(result);

  
  return 0;
}
