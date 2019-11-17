#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>

const unsigned int H  = 30;
const unsigned int W  = 50;
const unsigned int TIMES  = 10000;
const double WAIT  = 0.1; // 一世代WAIT秒


int count_neighbours(std::vector<std::vector<bool> > grid, int x, int y) {
    int dx[] = {1,0,-1,1,-1,0,1,-1};
    int dy[] = {0,1,-1,1,0,-1,-1,1};

    int count = 0;

    for(int i = 0; i < 8; i++) {
        int next_x = x + dx[i];
        int next_y = y + dy[i];
        if(next_x >= 0 && next_y >= 0 && next_x < W && next_y  < H) {
            // チェックする
            if(grid[next_y][next_x] == 1) {
                count++;
            }
        }
    }
    return count;
}

bool test_count_neighbours(std::vector<std::vector<bool> > grid) {

    int hoge = count_neighbours(grid, 1, 1);
    int expect = 1;
    return hoge == expect;
}

bool get_next_state(bool current_state, int neighbours) {
    if(current_state) {
        switch (neighbours) {
        case 2:
        case 3:
            return current_state;
        case 0:
        case 1:
            return false;
        default:
            return false;
        }
    } else {
        switch (neighbours){
        case 3:
            return true;
        default:
            return false;
        }
    }
}

void test_get_next_state(bool current_state, int neighbours, bool expect) {

    bool next_state = get_next_state(current_state, neighbours);
    std::cout << (expect == next_state) << std::endl;
}

std::vector<std::vector<bool> > replace(std::vector<std::vector<bool> > old_grid) {
    std::vector<std::vector<bool> > new_grid(H, std::vector<bool>(W,0));

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            int count = count_neighbours(old_grid, j, i);
            bool next_state = get_next_state(old_grid[i][j], count);
            new_grid[i][j] = next_state;
        }
    }
    return new_grid;
}

void print(std::vector<std::vector<bool> > grid) {
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(grid[i][j] == 1) {
                std::cout << 'o';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Game_Exec() {
    std::vector<std::vector<bool> > grid(H, std::vector<bool>(W,0));

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            grid[i][j] = rand()%2;
        }
    }

    for(int i = 0 ; i < TIMES; i++) {
        system("clear");
        grid = replace(grid);
        print(grid);
        usleep(int(WAIT*1000000));
    }
}

int main(void) {
    
    Game_Exec();

    // {
        // std::vector<std::vector<bool> > grid;
    //     grid = {{1,0,0}, {0,0,0}, {0,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,1,0}, {0,0,0}, {0,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,1}, {0,0,0}, {0,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,0}, {1,0,0}, {0,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,0}, {0,1,0}, {0,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,0}, {0,0,1}, {0,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,0}, {0,0,0}, {1,0,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,0}, {0,0,0}, {0,1,0}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;

    //     grid = {{0,0,0}, {0,0,0}, {0,0,1}}; 
    //     std::cout << test_count_neighbours(grid) << std::endl;
    // }

    // {
    //     test_get_next_state(0,1,0);
    //     test_get_next_state(0,2,0);
    //     test_get_next_state(0,3,1);
    //     test_get_next_state(0,4,0);
    //     test_get_next_state(0,5,0);
    //     test_get_next_state(0,6,0);
    //     test_get_next_state(0,7,0);
    //     test_get_next_state(0,8,0);
    //     test_get_next_state(1,0,0);
    //     test_get_next_state(1,1,0);
    //     test_get_next_state(1,2,1);
    //     test_get_next_state(1,3,1);
    //     test_get_next_state(1,4,0);
    //     test_get_next_state(1,5,0);
    //     test_get_next_state(1,6,0);
    //     test_get_next_state(1,7,0);
    //     test_get_next_state(1,8,0);
    // }
}