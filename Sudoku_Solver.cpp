//backend code sample
#include <bits/stdc++.h>
using namespace std;
bool isSafe(vector<vector<int>>&mat, int row, int col, int num){
    int n = mat.size();
    for(int i = 0; i<n; i++){
        if(mat[row][i] == num || mat[i][col] == num) return false;
    }

    int rowStart = row - (row % 3);
    int colStart = col - (col % 3);
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(mat[i+rowStart][j+colStart] == num) return false;
        }
    }
    return true;
}
bool solveSudoku(vector<vector<int>>&mat, int row, int col){
    int n = mat.size();
    //base case
    if(row == n - 1 && col == n){
        return true;
    }
    if(col == n){
        row++;
        col = 0;
    }
    if(mat[row][col] != 0){
        return solveSudoku(mat, row, col+1);
    }
    for(int i = 1; i<=n; i++){
        if(isSafe(mat, row, col, i)){
            mat[row][col] = i;
            if(solveSudoku(mat, row, col+1)){
                return true;
            }
            mat[row][col] = 0;
        }
    }
    return false;
}
void sudoku(vector<vector<int>> &mat) {
  	solveSudoku(mat, 0, 0);
}
int main(){
    vector<vector<int>> mat = {
        {0, 0, 0, 2, 6, 0, 7, 0, 1},
        {6, 8, 0, 0, 7, 0, 0, 9, 0},
        {1, 9, 0, 0, 0, 4, 5, 0, 0},
        {8, 2, 0, 1, 0, 0, 0, 4, 0},
        {0, 0, 4, 6, 0, 2, 9, 0, 0},
        {0, 5, 0, 0, 0, 3, 0, 2, 8},
        {0, 0, 9, 3, 0, 0, 0, 7, 4},
        {0, 4, 0, 0, 5, 0, 0, 3, 6},
        {7, 0, 3, 0, 1, 8, 0, 0, 0}
    };
    cout << "Original Sudoku:" << endl;
    for(int i = 0; i<mat.size(); i++){
        for(int j = 0; j< mat[0].size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Solved Sudoku:" << endl;
  	if(solveSudoku(mat, 0, 0)){
        for(int i = 0; i<mat.size(); i++){
            for(int j = 0; j< mat[0].size(); j++){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}