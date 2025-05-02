#include "maze_solver.h"
#include <stack>
using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {
    // 1. Guard – out of bounds, wall, or already visited ➔ return false
    if (!maze.inBounds(r, c) || maze.isWall(r, c) || visited[r][c]) {
        return false;
    }

    // 2. Goal – if (r,c) == finish, add to path and return true
    if (r == maze.finish.row && c == maze.finish.col) {
        maze.path.push_back({r, c});
        return true;
    }

    // 3. Mark current cell as visited
    visited[r][c] = true;

    // 4. Explore in N, E, S, W order
    const int dr[4] = {-1, 0, 1, 0}; // row offsets for N, E, S, W
    const int dc[4] = {0, 1, 0, -1}; // col offsets

    for (int i = 0; i < 4; i++) {
        int newR = r + dr[i];
        int newC = c + dc[i];

        if (dfs(maze, newR, newC, visited)) {
            maze.path.push_back({r, c});
            return true;
        }
    }

    // 6. Fail – no path found from this cell
    return false;
}

bool MazeSolver::solveDFS(Maze& maze) {
    // Clear any existing path
    maze.path.clear();
    
    // Create visited matrix
    vector<vector<bool>> visited(maze.grid.size(), 
                               vector<bool>(maze.grid[0].size(), false));
    
    // Start DFS from the start position
    bool found = dfs(maze, maze.start.row, maze.start.col, visited);
    
    // If path found, add the start position to the path
    if (found) {
        maze.path.push_back(maze.start);
    }
    
    return found;
}
