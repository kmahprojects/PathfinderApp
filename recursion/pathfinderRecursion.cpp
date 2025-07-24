#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//fillMatrix fills a matrix with values from a text file
//fillMatrix takes an ifstream and a 2 dimensional matrix of integers as parameters
//it returns nothing
void fillMatrix (std::ifstream&fin, std::vector<std::vector<int>>& v) {
    for (unsigned row = 0; row < v.size(); row++) {
        for (unsigned col = 0; col < v[row].size(); col++) {
            int x;
            fin >> x;
            v[row][col] = x;
        }
    }
}
//printMatrix prints out a matrix
//it takes a 2 dimensional matrix as parameters
//it returns nothing
template<typename T>
void printMatrix (std::vector<std::vector<T>> & v) {
    for (unsigned row = 0; row < v.size(); row++) {
        for (unsigned col = 0; col < v[row].size(); col++) {
            std::cout << v[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

bool isValid (std::vector<std::vector<char> > & path, int r, int c) {
    if (r >= static_cast<int>(path.size()) || c >= static_cast<int>(path[r].size()) || r < 0 || c < 0 || path[r][c] != '-') {
        return false;
    }
    return true;
}

bool findStart (std::vector<std::vector<int>>& matrix, std::vector<int>& start) {
    for (unsigned row = 0; row < matrix.size(); row++) {
        for (unsigned col = 0; col < matrix[row].size(); col++) {
            if (matrix[row][col] == 0) {
                start[0] = static_cast<int>(row);
                start[1] = static_cast<int>(col);
                return true;
            }
        }
    }
    return false;
}

//pathFind finds a path from a 0 to another 0 in a matrix of integers, and draws the path on another matrix
//it takes two 2d matrices, one of integers, one of characters, an integer row and column, and an integer sum
//it returns true or false, depending on if a path where the sum is greater than 0 was found
bool pathFind (std::vector<std::vector<int>>& og, std::vector<std::vector<char>>& path ,std::vector<int> start, int r, int c, int sum = 0) {
    if (r < static_cast<int>(og.size()) && c < static_cast<int>(og[r].size()) && (r != start[0] || c != start[1])) {
        if (og[r][c] == 0) {
            if (sum > 0) {
                path[r][c] = 'X';
                return true;
            }
            return false;
        }
    }
    bool isFound;
    if(isValid(path, r+1, c)) {
        if(r == start[0] && c == start[1]) {
            path[r][c] = 'S';
        } else {
            path[r][c] = 'V';
        }
        isFound = pathFind(og, path, start, r+1, c, sum + og[r][c]);
        if (isFound) {
            return true;
        } else {
            path[r][c] = '-';
        }
    }

    if(isValid(path, r-1, c)) {
        if(r == start[0] && c == start[1]) {
            path[r][c] = 'N';
        } else {
            path[r][c] = '^';
        }
        isFound = pathFind(og, path, start, r-1, c, sum + og[r][c]);
        if (isFound) {
            return true;
        } else {
            path[r][c] = '-';
        }
    }

    if(isValid(path, r, c+1)) {
        if(r == start[0] && c == start[1]) {
            path[r][c] = 'E';
        } else {
            path[r][c] = '>';
        }
        isFound = pathFind(og, path, start, r, c+1, sum + og[r][c]);
        if (isFound) {
            return true;
        } else {
            path[r][c] = '-';
        }
    }
    if(isValid(path, r, c-1)) {
        if(r == start[0] && c == start[1]) {
            path[r][c] = 'W';
        } else {
            path[r][c] = '<';
        }
        isFound = pathFind(og, path, start, r, c-1, sum + og[r][c]);
        if (isFound) {
            return true;
        } else {
            path[r][c] = '-';
        }
    }
    return false;
}


int main() {
    char response = 'y';
    while (response == 'y' || response == 'Y'){
        int cols, rows;
    std::string myFile;
    std::cout << "Type the name of the file you want to process" << std::endl;
    std::cin >> myFile;
    std::ifstream fin;
    fin.open(myFile);
    if (fin.is_open()) {
        fin >> rows >> cols;
        std::vector<std::vector<int>> original (rows, std::vector<int> (cols, 0));
        std::cout << "OG Matrix:" << std::endl;
        fillMatrix(fin, original);
        printMatrix(original);
        std::cout << "Path Matrix:" << std::endl;
        std::vector<std::vector<char>> path (rows, std::vector<char> (cols, '-'));
        std::vector<int> points = {0,0};
        bool pathFound = false;
        if(findStart(original, points)) {
            pathFound = pathFind(original, path, points, points[0], points[1]);
        } else {
            std::cout << "No starting point found";
        }
        if (pathFound) {
            printMatrix(path);
        } else {
            std::cout << "No path found";
        }
        
        fin.close();
    }
    std::cout << std::endl;
    std::cout << "Would you like to end? (Y or y to continue, anything else to end)" << std::endl;
    std::cin >> response;
    }
    
    return 0;
}