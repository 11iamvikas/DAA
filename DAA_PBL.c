#include <bits/stdc++.h>
#include <climits> // Required for INT_MAX
using namespace std;
#define R 12
#define C 10
// These arrays are used to get row and column numbers of 4 neighbors of a given cell
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };
// Function to check if a given cell (x, y) is valid and within the matrix bounds
bool isValid(int x, int y) {
return (x >= 0 && x < R && y >= 0 && y < C);
}
// Function to check if a given cell (x, y) can be visited or not
bool isSafe(int mat[R][C], int visited[R][C], int x, int y) {
if (mat[x][y] == 0 || visited[x][y])
return false;
return true;
}
// Function to mark all adjacent cells of landmines as unsafe
void markUnsafeCells(int mat[R][C]) {
for (int i = 0; i < R; i++) {
for (int j = 0; j < C; j++) {
// If a landmine is found
if (mat[i][j] == 0) {
// Mark all adjacent cells as unsafe (-1)
for (int k = 0; k < 4; k++) {
int newX = i + rowNum[k];
int newY = j + colNum[k];
if (isValid(newX, newY) && mat[newX][newY] == 1) {
mat[newX][newY] = -1;
}
}
}
}
}
// Mark all found adjacent cells as unsafe (set -1 cells to 0)
for (int i = 0; i < R; i++) {
for (int j = 0; j < C; j++) {
if (mat[i][j] == -1)
mat[i][j] = 0;
}
}
}
// Function to find the shortest safe route in the matrix with landmines
// mat[][] - binary input matrix with safe cells marked as 1
// visited[][] - stores info about cells already visited in the current route
// (i, j) are coordinates of the current cell
// min_dist - stores minimum cost of shortest path so far
// dist - stores current path cost
void findShortestPathUtil(int mat[R][C], int visited[R][C], int i, int j, int &min_dist, int dist) {
// If destination is reached
if (j == C - 1) {
min_dist = min(dist, min_dist);
return;
}
// If current path cost exceeds minimum so far
if (dist > min_dist)
return;
// Include (i, j) in current path
visited[i][j] = 1;
// Recurse for all safe adjacent neighbors
for (int k = 0; k < 4; k++) {
int newX = i + rowNum[k];
int newY = j + colNum[k];
if (isValid(newX, newY) && isSafe(mat, visited, newX, newY)) {
findShortestPathUtil(mat, visited, newX, newY, min_dist, dist + 1);
}
}
// Backtrack
visited[i][j] = 0;
}
// Wrapper function to find the shortest safe route
void findShortestPath(int mat[R][C]) {
// Stores minimum cost of shortest path so far
int min_dist = INT_MAX;
// Create a visited array to store info about cells already visited in the current route
int visited[R][C];
// Mark adjacent cells of landmines as unsafe
markUnsafeCells(mat);
// Start from first column and take minimum for all possible starting points in the first column
for (int i = 0; i < R; i++) {
if (mat[i][0] == 1) { // If path is safe from current cell
memset(visited, 0, sizeof(visited));
findShortestPathUtil(mat, visited, i, 0, min_dist, 0);
// If minimum distance is already found, no need to check other rows
if (min_dist == C - 1)
break;
}
}
if (min_dist != INT_MAX)
cout << "Length of shortest safe route is " << min_dist << endl;
else
cout << "Destination not reachable from given source" << endl;
}
// Driver code
int main() {
// Input matrix with landmines shown with number 0
int mat[R][C] = {
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }
};
// Find shortest path
findShortestPath(mat);
return 0;
}