#include "board.h"
#include <cmath>


vector<tile> board::make_board(int w, int h, int mines){
    columns = w;
    rows = h;
    m_num = mines;
    int tilecount = w * h;
    for (int i = 0; i < tilecount; i++){
        tile ugh;
        ugh.b_num = 0;
        tiles.push_back(ugh);
    }
    for (int i = 1; i < mines; i++){
        int random = rand() % (tilecount);
        if (tiles[random].b_num == 10){
            i -= 1;
        }
        else{
            tiles.at(random).b_num = 10;
            if (random%h != 0){
                tiles[(random - 1)].b_num += 1;
                tiles[random + (h - 1)].b_num += 1;
                tiles[random - (h + 1)].b_num += 1;
            }
            if ((random+1)%h != 0){
                tiles[random + 1].b_num += 1;
                tiles[random + (h + 1)].b_num += 1;
                tiles[random - (h - 1)].b_num += 1;
            }
            tiles[random + h].b_num += 1;
            tiles[random - (h)].b_num += 1;
            bombs.push_back(random);
        }
    }
    return tiles;
}
vector<int> board::return_bombs() const{
    return bombs;
}

vector<tile> board::reset() {
    tiles.clear();
    bombs.clear();
    tiles = board::make_board(columns, rows, m_num);
    return tiles;
}

void board::reveal_tile(int x, int y, vector<tile> blegh){
    tiles.clear();
    tiles = blegh;
    int index = x*rows + y;
    tiles[index].hidden = false;
    int tilecount = rows * columns;
    if(tiles[index].b_num == 0){
        if (index%rows != 0){
            if (tiles[(index - 1)].hidden and index -1 >= 0){
                reveal_tile(x,(y-1), tiles);
            }
            if (tiles[index + (rows - 1)].hidden and (index + (rows - 1)) < tilecount){
                reveal_tile(x+1, y-1, tiles);
            }
            if (tiles[index - (rows + 1)].hidden and (index - (rows + 1)) >= 0){
                reveal_tile(x-1,y-1, tiles);
            }
        }
        if ((index+1)%rows != 0){
            if (tiles[index + 1].hidden and index + 1 <= tilecount){
                reveal_tile(x, y+1, tiles);
            }
            if (tiles[index + (rows + 1)].hidden and (index + (rows + 1))< tilecount){
                reveal_tile(x+1, y+1, tiles);
            }
            if (tiles[index - (rows - 1)].hidden and (index - (rows - 1)) >= 0){
                reveal_tile(x-1, y+1, tiles);
            }
        }
        if (tiles[index + rows].hidden and index + rows < tilecount){
            reveal_tile(x+1, y, tiles);
        }
        if (tiles[index - (rows)].hidden and index - (rows) >= 0){
            reveal_tile(x-1, y, tiles);
        }
    }
}

vector<tile> board::return_board() {
    return tiles;
}
