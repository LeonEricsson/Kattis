//
// Created by Leon Ericsson on 2022-03-24.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <string>

using IntMatrix = std::vector<std::vector<int32_t>>;
using BoolMatrix = std::vector<std::vector<int32_t>>;

constexpr int32_t horse_r[] = {-2, -2, -1, 1, 2, 2, 1, -1};
constexpr int32_t horse_c[] = {-1, 1, 2, 2, 1, -1, -2, -2};

void printGrid(IntMatrix& grid){
    for(int32_t i{0}; i < 8; ++i){
        for(int32_t j{0}; j < 8; ++j){
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool valid(BoolMatrix& vis, int row, int col){
    if (row < 0 || col < 0 || row >= 8 || col >= 8)
        return false;

    if (vis[row][col])
        return false;

    return true;
}

void BFS(IntMatrix& grid, int32_t startRow, int32_t startCol){
    BoolMatrix visited(8, std::vector<int32_t>(8, false));

    // Stores indices of the matrix cells
    std::queue<std::pair<int32_t, int32_t> > q;

    q.push({ startRow, startCol });
    visited[startRow][startCol] = true;

    while (!q.empty()) {

        auto cell = q.front();
        auto row = cell.first;
        auto col = cell.second;

        q.pop();

        // Go to the 8 possible cells horse can jump to
        for (int i = 0; i < 8; i++) {

            int newrow = row + horse_r[i];
            int newcol = col + horse_c[i];

            if (valid(visited, newrow, newcol)) {
                q.push({ newrow, newcol });
                visited[newrow][newcol] = true;
                grid[newrow][newcol] = grid[row][col] + 1;
            }
        }
    }
}

constexpr int rowmap[] = {-1,7,6,5,4,3,2,1,0};
std::unordered_map<char, int32_t> colmap = {
        {'a',0}, {'b', 1}, {'c', 2},
        {'d', 3}, {'e', 4}, {'f', 5},
        {'g', 6}, {'h', 7}
};

constexpr int rowmap2[] = {8,7,6,5,4,3,2,1};
constexpr char colmap2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

int main(){
    int32_t n;
    std::string input;
    std::cin >> n;
    while(n--){
        IntMatrix grid(8, std::vector<int32_t>(8, 0));

        std::cin >> input;
        auto col = colmap[input[0]];
        auto row = rowmap[(input[1] - '0')];

        BFS(grid, row, col);

        std::vector<std::pair<int32_t, int32_t>> hidingPlaces;
        int32_t maxDist{0};
        for(int32_t i{0}; i < 8; ++i){
            for(int32_t j{0}; j < 8; ++j){
                if(grid[i][j] > maxDist){
                    hidingPlaces.clear();
                    maxDist = grid[i][j];
                    hidingPlaces.emplace_back(std::make_pair(i,j));
                } else if(grid[i][j] == maxDist){
                    hidingPlaces.emplace_back(std::make_pair(i,j));
                }
            }
        }
        std::cout << maxDist << " ";
        for(const auto& p : hidingPlaces){
            std::cout << colmap2[p.second] << rowmap2[p.first] << " ";
        }
        std::cout << "\n";
    }
}