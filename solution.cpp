//A8A3A33EF075ACEF9B08F5B9845569ECCB423725
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "solution.h"
#include <deque>


using namespace std;

uint32_t char_index(const char &input){
    if(input == '^'){
        return 0;
    }
    else{
        return static_cast<uint32_t>((input) - 'a' + 1);
    }
}

//helper function
bool Solution::should_be_in_search(const uint32_t &x, const uint32_t &y, const char &color, const vector<vector<char>> &maze){
    
    uint32_t z = char_index(color);
    
    //backtracer spot should be empty, and within range of the map
    if(backtracer[z][x][y] == '0'){ 
        
            if(maze[x][y] == '#'){
                return false;
            }
            else if (maze[x][y] == '.' || maze[x][y] == '?' || maze[x][y] == '@'){
                return true;
            }

            //if the color of door match current color, we can move 
            else if((maze[x][y] >= 'A' && maze[x][y] <= 'Z')){
                if(color == maze[x][y] + 32){
                    return true;
                }
                else {
                    return false;
                }
            }
            else if ((maze[x][y] >= 'a' && maze[x][y] <= 'z') || maze[x][y] == '^'){
                return true;
            }
    }
                  
            else {
                return false;
            }
   return false;
}

void Solution::solve_search(const vector<vector<char>> &maze, const char &qs){

    //reserving space for the color dimension first
    backtracer.resize(num_colors + 1, vector<vector<char>>(height, vector<char>(width, '0'))); // have to include ^ as a version
    
   

    //creating a queue using deque
    //Holds information: {direction of prev position, {character in the puzzle, {x coordinate, y coordinate}}}
    deque <Coordinates> search_container;

    
    

   //push back the character and 
    search_container.push_back(start_coord);
    backtracer[char_index(start_coord.color)][start_coord.x][start_coord.y] = '@';

        uint32_t x;
        uint32_t y;
        char color;
    
    while(search_container.size() != 0){ //while loop that continues until our queue is empty or ? is found
       
       //for queue
       if(qs == 'q'){
            x = search_container.front().x;
            y = search_container.front().y;
            color = search_container.front().color;
            
       }
       //for stack
       else{
            x = search_container.back().x;
            y = search_container.back().y;
            color = search_container.back().color;
           
       }

       //now we can take away whatever we were looking at because we got all the info we need
       if (qs == 'q'){
            search_container.pop_front();
       }
       else if (qs == 's'){
            search_container.pop_back();
       }
        if (((maze[x][y] >= 'a' && maze[x][y] <= 'z') || maze[x][y] == '^') && maze[x][y] != color){
            if(backtracer[char_index(maze[x][y])][x][y] == '0'){
                Coordinates a_button {x,y, maze[x][y]};
                search_container.push_back(a_button);
                backtracer[char_index(maze[x][y])][x][y] = color;
                continue;
            }
            else{
                continue;
            }
       } 
       
       
        //set up rules to join the queue
        
        bool k;

        //adding the top
        if(static_cast<int> (x - 1) >= 0){
            k = should_be_in_search(x - 1,  y , color, maze);
            Coordinates top;
            if(k == true){
                top = {x - 1, y, color};
                backtracer[char_index(top.color)][top.x][top.y] = 'B';
                if(maze[top.x][top.y] == '?'){
                    end_coord = top;
                    break;
                }
                search_container.push_back(top);
            
             }

        }
        
        //adding the right
        if(y + 1 < width){
            k = should_be_in_search(x, y + 1,  color, maze);
            Coordinates right;

            if(k == true){
                right = {x, y + 1, color};
                backtracer[char_index(right.color)][right.x][right.y] = 'L';
                if(maze[right.x][right.y] == '?'){
                    end_coord = right;
                    break;
                }
                search_container.push_back(right);
                
            }
            
        }

        //adding the bottom
        if(x + 1  < height){
            k = should_be_in_search(x + 1, y,  color, maze);
            Coordinates bottom;
            if(k == true){
                bottom = {x + 1, y, color};
                backtracer[char_index(bottom.color)][bottom.x][bottom.y] = 'U';
                if(maze[bottom.x][bottom.y] == '?'){  
                    end_coord = bottom;
                    break;
                }
                search_container.push_back(bottom);
            }
            
        }
            
        //adding the left
        if (static_cast<int> (y - 1) >= 0){
            k = should_be_in_search(x, y - 1, color, maze);
            Coordinates left;
            if(k == true){
                left = {x, y - 1, color};
                backtracer[char_index(left.color)][left.x][left.y] = 'R';
                if(maze[left.x][left.y] == '?'){
                    end_coord = left;
                    break;;
                }
                search_container.push_back(left);
                
             }
        }
    }
    
   
   if(search_container.empty()){
        trace_empty = true;
        return;
   }

   else{
    Coordinates hit_point;
    //backtrace technique;
    hit_point = end_coord;

    trace.push_back(hit_point);

    while(hit_point.x != start_coord.x || hit_point.y != start_coord.y || hit_point.color != start_coord.color){
        //if U then we go up changing y 
        if((backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] >= 'a' && 
        backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] <= 'z') || backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] == '^'){
            hit_point.color = backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y];
            trace.push_back(hit_point);
        }

        else if(backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] == 'U'){
            hit_point.x--;
            trace.push_back(hit_point);
        }
        //if R then we move to the right
        else if (backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] == 'R'){
            hit_point.y++;
            trace.push_back(hit_point);
        }
        //if B then we move to the bottom
        else if (backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] == 'B'){
            hit_point.x++;
            trace.push_back(hit_point);
        }
        //if we have to the move left
        else if(backtracer[char_index(hit_point.color)][hit_point.x][hit_point.y] == 'L'){
            hit_point.y--;
            trace.push_back(hit_point);
        } 
       
    }
   }

}


void Solution::output(string out_mode, const vector<vector<char>> &maze){
    if(out_mode == "list"){
        list_output();
    }
    else{
        map_output(maze);
    }
}

void Solution::list_output(){
    reverse(trace.begin(), trace.end());
    for(Coordinates i: trace){
        cout << "(" << i.color << ", (" << i.x << ", " << i.y << "))\n";
    }
}   

void Solution::map_output(const vector<vector<char>> &maze){
    reverse(trace.begin(), trace.end());
   
    uint32_t layer  = '^';
    char color;

    for(uint32_t i = 0; i < num_colors + 1; i++){
        //for every layer of map 
        color = static_cast<char> (layer);
    
        cout << "// color " << color << '\n';
        
        vector<vector<char>> layer_map = maze;
         //first update the map where the trace doesn't go through
         //going to set every button and door to be and then change the ones that are in the solution later
        for(uint32_t row = 0; row < height; row++){
            for(uint32_t column = 0; column < width; column++){
                if(tolower(layer_map[row][column]) == color || layer_map[row][column] == '@'){
                    layer_map[row][column] = '.';
                }
            }
        }
         //go through everything in trace
        for(Coordinates k : trace){
            //if k is the same color and we on a button
            if(((maze[k.x][k.y] >= 'a' && maze[k.x][k.y] <= 'z')) && (backtracer[char_index(k.color)][k.x][k.y] != color)){
                
                if(maze[k.x][k.y] == color && maze[k.x][k.y] == k.color){
                    layer_map[k.x][k.y] = '@';
                }
                else if(k.color == color && maze[k.x][k.y] != k.color) {
                    layer_map[k.x][k.y] = '%';
                }
            }
            
             else if(k.color == color && maze[k.x][k.y] != '?'){
                layer_map[k.x][k.y] = '+';
            }
        } 
        
        if(layer == '^'){
           layer_map[start_coord.x][start_coord.y] = '@';
        }

        for(uint32_t a = 0; a < height; a++){
            for(uint32_t b = 0; b < width; b++){
                cout << layer_map[a][b];
            }
            
            cout << "\n";
        }
        layer = i + 'a';
    }
}
        
void Solution::no_solution(const vector<vector<char>> &maze){
    cout << "No solution.\nDiscovered:\n";
    bool hashornot = false; //keeps track if that position shoud be hashed or not
    //you get hashed if you have never been discovered

    vector<vector<char>> no_sol = maze;
    for(uint32_t i = 0; i < height; i++){
        for(uint32_t j  = 0; j < width; j++){
            for(uint32_t z = 0; z <= num_colors; z++){
                hashornot = true;
                if(backtracer[z][i][j] != '0'){
                   hashornot = false;
                   break;
                }
            }
            if(hashornot){
            no_sol[i][j] = '#';
            }

        }
    }
    for(uint32_t i = 0; i < height; i++){
        for(uint32_t j  = 0; j < width; j++){
            cout << no_sol[i][j];
        }
        cout << '\n';
    }

}