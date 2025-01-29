#include <vector>
using namespace std;

struct tile{
    int b_num = 0;
    bool hidden = true;
    bool red_flag = false;
};

class board{
public:
    int rows;
    int columns;
    int m_num;
    vector<tile> tiles;
    vector<int> bombs;
    vector<tile> make_board(int w, int h, int mines);
    vector<int> return_bombs() const;
    vector<tile> return_board();
    vector<tile> reset();
    void reveal_tile(int row, int col, vector<tile> blegh);
};
