#include <vector>
#include <iostream>
#include <fstream>
#include "ll.h"
struct path_state {
    int row;
    int col;
    int prow;
    int pcol;
    char dir;
    int sum; 
};

//print prints out a 2D array
//it takes a 2D array as an input
//it returns nothing
template <typename T>
void print (std::vector<std::vector<T> > m) {
    for (auto x : m){
        for (auto y : x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    return;
}
//valid checks if a point is valid in a 2D array
//it takes a 2D array of characters and 2 integers as parameters
//it returns a boolean true or false
bool valid(std::vector<std::vector<char> > m, int row, int col) {
    if (row >= static_cast<int>(m.size()) || col >= static_cast<int>(m[row].size()) || row < 0 || col < 0 || m[row][col] != '-'){
        return false;
    }
    return true;
}
//pathfinder finds a path through a 2D array
//it takes a number matrix, a character matrix, and a vector for holding the start values
//it returns a true or false if it finds the path or not
bool pathfinder (const std::vector<std::vector<int> > & og, std::vector<std::vector<char>> & path, const std::vector<int> start){
    stack<path_state> s;
    //push in the starting position(the first 0)
    s.push({start[0],start[1],start[0],start[1],'0', og[start[0]][start[1]]});
    bool output = false;
    while (!s.isEmpty()){
        path_state t = s.pop();
        //if outside bounds OR crossing path OR at a 0, not at start, and sum is less than or equal to 0, do nothing
        if (!valid(path, t.row, t.col) || ((t.row != start[0] || t.col != start[1]) && t.sum <= 0 && og[t.row][t.col] == 0)){
            
        }
         else if (t.dir == '-'){
            //case for if no directions
            path[t.prow][t.pcol] = '-';
        }
        //if we are at a 0, sum is bigger than 0, and we are not at the start, return true
        else if ((t.row != start[0] || t.col != start[1]) && t.sum > 0 && og[t.row][t.col] == 0) {
            path[t.prow][t.pcol] = t.dir;
            path[t.row][t.col] = 'X';
            output = true;
            break;
        } 
       
        //anything else
        else {
            //change directions of the last position to the direction
            path[t.prow][t.pcol] = t.dir;
            //add last position to the sum
            t.sum += og[t.row][t.col];
            //checks if directions are valid, if not, do not push them in.
            bool down = valid(path, t.row+1, t.col);
            bool up = valid(path, t.row-1, t.col);
            bool left = valid(path, t.row, t.col-1);
            bool right = valid(path, t.row, t.col+1);
            s.push({t.row, t.col, t.prow, t.pcol, '-', t.sum});
            

            //left
            if (left) {
                s.push({t.row, t.col-1, t.row, t.col, '<', t.sum});
            }
            //right
            if (right) {
                s.push({t.row, t.col+1, t.row, t.col, '>', t.sum});
            }
            //down
            if (down){
                s.push({t.row+1, t.col, t.row, t.col, 'V', t.sum});
            }
            //up 
            if (up) {
                s.push({t.row-1, t.col, t.row, t.col, '^', t.sum});
            }
        }
    }
    //change the starting arrow to a N, S, E, or W
    if (path[start[0]][start[1]] == 'V') {
        path[start[0]][start[1]] = 'S';
    } else if (path[start[0]][start[1]] == '^') {
        path[start[0]][start[1]] = 'N';
    } else if (path[start[0]][start[1]] == '<') {
        path[start[0]][start[1]] = 'W';
    } else if (path[start[0]][start[1]] == '>') {
        path[start[0]][start[1]] = 'E';
    }
    return output;
}

int main() {
    
    char response = 'y';
    while (response == 'y' || response == 'Y'){
    std::string inputFile = "";
    std::cout << "Which file would you like to process?";
    std::cin >> inputFile;
    std::ifstream fin(inputFile);
    int row;
    int col;
    fin >> row >> col;
    std::vector<std::vector<int> > og(row, std::vector<int>(col, 0));
    std::vector<std::vector<char> > path(row, std::vector<char>(col, '-'));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fin >> og[i][j];
        }
    }
    fin.close();
    std::vector<int> start {0,0};
    std::cout << "OG Matrix:" << std::endl;
    print(og);
    std::cout << "Path Matrix:" << std::endl;
    bool path_found = false;
    for (unsigned i = 0; i < og.size(); i++) {
        for (unsigned j = 0; j < og[i].size(); j++) {
            if (og[i][j] == 0) {
                start[0] = static_cast<int>(i);
                start[1] = static_cast<int>(j);
                path_found = pathfinder(og, path, start);
            }
            if (path_found == true){
                break;
            }
        }
        if (path_found == true){
                break;
        }
    }
    if (path_found){
        print(path);
    } else {
        std::cout << "No path found" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Would you like to end? (Y or y to continue, anything else to end)" << std::endl;
    std::cin >> response;
    }

    return 0;    
}
