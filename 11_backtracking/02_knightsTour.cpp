#include <iostream>
#include <list>
using namespace std;

int** create2DArray(int height, int width=-1, int value=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = value;
        }
    }
    return arr;
}

void freeArray(int **arr, int height){
    for(int i=0; i<height; i++){
        free(arr[i]);
    }
    free(arr);
}

void goKnight(int level, int a, int b, int row, int col, int** grid, int* dx, int* dy){
    grid[a][b] = level;
    if(level == row * col){
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                cout << (grid[i][j] < 10 ? "0":"") << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    for(int i=0; i<8; i++){
        int x = a + dx[i];
        int y = b + dy[i];
        if(x > -1 && y > -1 && x < row && y < col && grid[x][y] == -1){
            goKnight(level+1, x, y, row, col, grid, dx, dy);
            grid[x][y] = -1;
        }
    }
}

void knightTour(int row, int col){
    int** grid = create2DArray(row, col, -1);
    int dx[8] = {2,1,-1,-2,2,1,-1,-2};
    int dy[8] = {1,2,2,1,-1,-2,-2,-1};
    goKnight(1,0,0, row, col, grid, dx, dy);
    freeArray(grid, row);
}

int main(){
    int row = 5, col = 5;
    int grid[row][col];
    fill(grid[0], grid[0]+row*col, -1);
    knightTour(row, col);

    return 0;
}
