#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include "board.h"
using namespace std;

struct leaderEntry{
    string minutes;
    string sec;
    string name;
};

int main()
{
    ifstream newfile("C:/Users/aily0/CLionProjects/minesweeper/files/board_config.cfg");
    string columns;
    string rows;
    string mc;
    if (newfile.is_open()){
        getline(newfile, columns);
        getline(newfile, rows);
        getline(newfile, mc);
    }
    ifstream leader_file("C:/Users/aily0/Downloads/Minesweeper_v4/Minesweeper_v4/files/leaderboard.txt");
    if (!leader_file){
        cout << "error";
    }
    vector<leaderEntry> leaders;
    string line;
    while (getline(leader_file, line)){
        leaderEntry oopsyloopsy;
        oopsyloopsy.minutes = (line.substr(0,2));
        oopsyloopsy.sec = (line.substr(3, 2));
        oopsyloopsy.name = line.substr(6, (line.size() - 6));
        leaders.push_back(oopsyloopsy);
    }
    int blegh = 0;
    int windowNum = 1;
    int w = stoi(columns);
    int h = stoi(rows);
    int mines = stoi(mc);
    int height = (h * 32) + 100;
    int width = w * 32;
    int tilecount = h * w;
    bool paused = false;
    bool loser = false;
    vector<int> bombs;
    bool debug_pressed = false;
    vector<tile> tiles;
    int flag_num = 0;
    board lol;
    bool game_over = false;
    bool leader_open = false;


    sf::Font font;
    font.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/font.ttf");
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    //welcome window variables
    sf::Text welcome, inputStatement, name, leaderBoard;
    welcome.setFont(font);
    welcome.setString("WELCOME TO MINESWEEPER!");
    welcome.setCharacterSize(24);
    welcome.setFillColor(sf::Color::White);
    welcome.setStyle(sf::Text::Bold | sf::Text::Underlined);
    float center = welcome.getGlobalBounds().width;
    welcome.setPosition((width-center)/2.0f,(height/2.0f)-150);

    inputStatement.setFont(font);
    inputStatement.setString("Enter your name:");
    inputStatement.setFillColor(sf::Color::White);
    inputStatement.setCharacterSize(20);
    inputStatement.setStyle(sf::Text::Bold);
    inputStatement.setPosition((width-inputStatement.getGlobalBounds().width)/2.0f,height/2.0f-75);

    name.setFont(font);
    string bleep = "|";
    name.setString(bleep);
    name.setCharacterSize(10);
    name.setFillColor(sf::Color::Yellow);
    name.setCharacterSize(18);
    name.setStyle(sf::Text::Bold);
    name.setPosition((width-name.getGlobalBounds().width)/2.0f,height/2.0f-45);


    sf::Texture debug, digits, happy, lose, win, flag, leader, mine, n1, n2, n3, n4, n5, n6, n7, n8, pause, play, hidden, reveal;
    debug.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/debug.png");
    digits.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/digits.png");
    happy.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/face_happy.png");
    lose.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/face_lose.png");
    win.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/face_win.png");
    flag.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/flag.png");
    leader.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/leaderboard.png");
    mine.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/mine.png");
    n1.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_1.png");
    n2.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_2.png");
    n3.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_3.png");
    n4.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_4.png");
    n5.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_5.png");
    n6.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_6.png");
    n7.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_7.png");
    n8.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/number_8.png");
    pause.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/pause.png");
    play.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/play.png");
    hidden.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/tile_hidden.png");
    reveal.loadFromFile("C:/Users/aily0/CLionProjects/minesweeper/files/images/tile_revealed.png");

    sf::Sprite dbug(debug), hFace(happy), l(lose), winnie(win), rFlag(flag), lBoard(leader), bomb(mine), t1(n1), t2(n2), t3(n3), t4(n4), t5(n5), t6(n6), t7(n7), t8(n8), stop(pause), start(play), hide(hidden), rev(reveal);
    sf::Sprite unitsTile, tensTile, hundredsTile, thousadnsTile;
    sf::Sprite flagunits, flagtens, flagneg;
    flagunits.setTexture(digits);
    flagtens.setTexture(digits);
    flagneg.setTexture(digits);
    flagneg.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
    unitsTile.setTexture(digits);
    unitsTile.setPosition((w*32)-33, 32*(h+0.5f));
    tensTile.setTexture(digits);
    tensTile.setPosition((w*32)-54, 32*(h+0.5f));
    hundredsTile.setTexture(digits);
    hundredsTile.setPosition((w*32)-76, 32*(h+0.5f));
    thousadnsTile.setTexture(digits);
    thousadnsTile.setPosition((w*32)-97, 32*(h+0.5f));
    hFace.setPosition((w * 16.0) - 32,32*(h+0.5f));
    winnie.setPosition((w * 16.0) - 32,32*(h+0.5f));
    l.setPosition((w * 16.0) - 32,32*(h+0.5f));
    dbug.setPosition((w * 32) -304, 32*(h+.5f));
    start.setPosition((w*32) - 240, 32*(h+.5f));
    stop.setPosition((w*32)-240, 32*(h+.5f));
    lBoard.setPosition((w*32)-176, 32*(h+.5f));

    //time
    auto time = chrono::steady_clock::now();
    int t = 0;
    int pauseTime = 0;
    int clicks = 0;
    chrono::steady_clock::time_point p1;

    leaderBoard.setFont(font);
    leaderBoard.setString("LEADERBOARD");
    leaderBoard.setCharacterSize(20);
    leaderBoard.setFillColor(sf::Color::White);
    leaderBoard.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderBoard.setPosition((width/2-leaderBoard.getGlobalBounds().width)/2.0f,(height/4.0f)-120);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (windowNum == 1) {
                debug_pressed = false;
                if (event.type == sf::Event::TextEntered) {
                    if (blegh <= 10) {
                        if (isalpha(event.text.unicode)) {
                            if (blegh == 0) {
                                bleep = toupper(event.text.unicode);
                                name.setString(bleep + "|");
                                name.setPosition((width - name.getGlobalBounds().width) / 2.0f, height / 2.0f - 45);
                                blegh += 1;
                            } else {
                                bleep += tolower(event.text.unicode);
                                name.setString(bleep + "|");
                                name.setPosition((width - name.getGlobalBounds().width) / 2.0f, height / 2.0f - 45);
                                blegh += 1;
                            }
                        }
                    }
                }
                if ((event.type == sf::Event::KeyPressed) and sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    if (blegh >= 1) {
                        bleep.pop_back();
                        name.setString(bleep + "|");
                        name.setPosition((width - name.getGlobalBounds().width) / 2.0f, height / 2.0f - 45);
                        blegh -= 1;
                    }
                }
                if ((event.type == sf::Event::KeyPressed) and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) and
                    blegh > 0) {
                    //board creation
                    tiles = lol.make_board(w, h, mines);
                    bombs = lol.return_bombs();
                    flag_num = 0;
                    windowNum += 1;
                }
                window.clear(sf::Color::Blue);
                window.draw(welcome);
                window.draw(inputStatement);
                window.draw(name);
                window.display();
            }
            else if(windowNum == 2) {
                window.clear(sf::Color::White);
                int square = 0;
                int x;
                int y;
                int revealed_squares = 0;
                int right_flags = 0;
                window.draw(hFace);
                window.draw(dbug);
                window.draw(stop);
                window.draw(lBoard);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    x = position.x;
                    y = position.y;
                }
                if ((y/32) < h and sf::Mouse::isButtonPressed(sf::Mouse::Left) and game_over == false) {
                    int bffr = ((x/32) * h) + (y/32);
                    auto it = find(bombs.begin(), bombs.end(), bffr);
                    if (it != bombs.end()) {
                        for (int teeheehee : bombs){
                            tiles[teeheehee].hidden = false;
                        }
                        window.draw(l);
                        loser = true;
                        game_over = true;
                    }
                    if (tiles[bffr].b_num == 0){
                        lol.reveal_tile(x/32, y/32, tiles);
                        tiles = lol.return_board();
                    }
                    tiles[bffr].hidden = false;
                }
                else if (hFace.getGlobalBounds().contains(x, y) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // smiley face button
                    flag_num = 0;
                    loser = false;
                    tiles = lol.reset();
                    bombs = lol.return_bombs();
                }
                if (dbug.getGlobalBounds().contains(x,y) and sf::Mouse::isButtonPressed(sf::Mouse::Left) and game_over == false){
                    // debug button
                    if (debug_pressed){
                        debug_pressed = false;
                    }
                    else{
                        debug_pressed = true;
                    }
                    if (game_over){
                        debug_pressed = false;
                    }
                }
                //clock
                if (start.getGlobalBounds().contains(x,y) and sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    paused = !paused;
                    clicks++;
                    if (clicks % 2 == 1 and !leader_open){
                        p1 = chrono::steady_clock::now();
                    }
                    else if (clicks%2 == 0 or leader_open){
                        auto p2 = chrono::steady_clock::now();
                        auto dp = chrono::duration_cast<chrono::duration<int>>(p2 - p1);
                        pauseTime += dp.count();
                    }
                }
                if (lBoard.getGlobalBounds().contains(x, y) and sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    //leaderboard button
                    leader_open = true;
                }
                auto time2 = chrono::steady_clock::now();
                auto dt = chrono::duration_cast<chrono::duration<int>>(time2 - time);
                t = dt.count() - pauseTime;
                int units = (t % 60)%10;
                int tens = (t % 60)/10;
                int hundreds = (t/60) % 10;
                int thousands = (t/60)/10;
                if (!paused){
                    unitsTile.setTextureRect(sf::IntRect(21 * units, 0, 21, 32));
                    tensTile.setTextureRect(sf::IntRect(21*tens, 0, 21, 32));
                    hundredsTile.setTextureRect(sf::IntRect(21*hundreds, 0, 21, 32));
                    thousadnsTile.setTextureRect(sf::IntRect(21*thousands, 0, 21, 32));
                }
                window.draw(unitsTile);
                window.draw(tensTile);
                window.draw(hundredsTile);
                window.draw(thousadnsTile);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    x = ((position.x)/32);
                    y = ((position.y)/32);
                }
                if (y < h and sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    int bffr = (x*h)+y;
                    if (tiles[bffr].red_flag){
                        tiles[bffr].red_flag = false;
                        flag_num -= 1;
                    }
                    else {
                        tiles[bffr].red_flag = true;
                        flag_num += 1;
                    }
                }
                for (int i = 0; i < w; i++){
                    for (int j = 0; j < h; j++){
                        int hi = tiles[square].b_num;
                        rev.setPosition(i*32, j*32);
                        window.draw(rev);
                        if (hi == 1){
                            t1.setPosition(i*32, j*32);
                            window.draw(t1);
                        }
                        else if (hi == 2){
                            t2.setPosition(i*32, j*32);
                            window.draw(t2);
                        }
                        else if (hi == 3){
                            t3.setPosition(i*32, j*32);
                            window.draw(t3);
                        }
                        else if (hi == 4){
                            t4.setPosition(i*32, j*32);
                            window.draw(t4);
                        }
                        else if (hi == 5){
                            t5.setPosition(i*32, j*32);
                            window.draw(t5);
                        }
                        else if (hi == 6){
                            t6.setPosition(i*32, j*32);
                            window.draw(t6);
                        }
                        else if (hi == 7){
                            t7.setPosition(i*32, j*32);
                            window.draw(t7);
                        }
                        else if (hi == 8){
                            t8.setPosition(i*32, j*32);
                            window.draw(t8);
                        }
                        else if (hi >= 10){
                            bomb.setPosition(i*32, j*32);
                            window.draw(bomb);
                            if (tiles[square].red_flag ){
                                right_flags += 1;
                            }
                        }
                        if (tiles[square].hidden == true){
                            hide.setPosition(i*32,j*32);
                            window.draw(hide);
                        }
                        else{
                            revealed_squares += 1;
                        }
                        if (tiles[square].red_flag){
                            rFlag.setPosition(i*32,j*32);
                            window.draw(rFlag);
                        }
                        if (loser == true and hi >= 10){
                            bomb.setPosition(i*32, j*32);
                            window.draw(bomb);
                            window.draw(l);
                        }
                        square += 1;
                        if (paused or leader_open){
                            rev.setPosition(i*32, j*32);
                            window.draw(rev);
                        }
                    }
                    if (revealed_squares + right_flags == tilecount){
                        window.draw(winnie);
                        windowNum = 3;
                    }
                }
                if (debug_pressed == true){
                    for (int i = 0; i < bombs.size(); i++){
                        int location = bombs[i];
                        int a = location/h;
                        int b = location % h;
                        bomb.setPosition(a*32, b*32);
                        window.draw(bomb);
                    }
                }
                if (paused){
                    window.draw(start);
                }
                if (leader_open){
                    windowNum = 3;
                }
                int counter = mines - flag_num;
                if (counter < 0 and counter > -10){
                    flagneg.setPosition(33, 32*(h + .5f)+16);
                    window.draw(flagneg);
                    flagunits.setTextureRect(sf::IntRect(21 * (-1 * counter), 0, 21, 32));
                    flagunits.setPosition(54, 32*(h + .5f)+16);
                    window.draw(flagunits);
                }
                else if (counter <= -10){
                    int units = (counter* -1) % 10;
                    int tens = counter/(-10);
                    flagneg.setPosition(33, 32*(h + .5f)+16);
                    window.draw(flagneg);
                    flagtens.setTextureRect(sf::IntRect(21 * (tens), 0, 21, 32));
                    flagtens.setPosition(54, 32*(h + .5f)+16);
                    flagunits.setTextureRect(sf::IntRect(21 * (units), 0, 21, 32));
                    flagunits.setPosition(75, 32*(h + .5f)+16);
                    window.draw(flagunits);
                    window.draw(flagtens);
                }
                else if (counter < 10){
                    int units = (counter) % 10;
                    flagunits.setTextureRect(sf::IntRect(21 * (units), 0, 21, 32));
                    flagunits.setPosition(33, 32*(h + .5f)+16);
                    window.draw(flagunits);
                }
                else if (counter >= 10){
                    int units = (counter) % 10;
                    int tens = counter/(10);
                    flagtens.setTextureRect(sf::IntRect(21 * (tens), 0, 21, 32));
                    flagtens.setPosition(54, 32*(h + .5f)+16);
                    flagunits.setTextureRect(sf::IntRect(21 * (units), 0, 21, 32));
                    flagunits.setPosition(75, 32*(h + .5f)+16);
                    window.draw(flagunits);
                    window.draw(flagtens);
                }
                window.display();
            }
            else if (windowNum == 3){
                sf::RenderWindow leaderboard(sf::VideoMode((width/2), height/2), "Minesweeper", sf::Style::Close);
                while (leaderboard.isOpen()){
                    sf::Event death;
                    while (leaderboard.pollEvent(death)) {
                        if (death.type == sf::Event::Closed){
                            leaderboard.close();
                            leader_open = false;
                            windowNum = 2;
                        }
                        int ahhhhh = 1;
                        string leader_string = "";
                        for (int i = 0; i < 5; i++){
                            leader_string += to_string(ahhhhh);
                            leader_string += ".\t";
                            leader_string += leaders[i].minutes;
                            leader_string += ":";
                            leader_string += leaders[i].sec;
                            leader_string += "\t";
                            leader_string += leaders[i].name;
                            leader_string += "\n\n";
                            ahhhhh += 1;
                        }
                        sf::Text leader;
                        leader.setFont(font);
                        leader.setString(leader_string);
                        leader.setCharacterSize(18);
                        leader.setFillColor(sf::Color::White);
                        leader.setStyle(sf::Text::Bold);
                        leader.setPosition((width/2-leader.getGlobalBounds().width)/2.0f,(height/2 - leader.getGlobalBounds().height)/2.0f + 20);
                        leaderboard.clear(sf::Color::Blue);
                        leaderboard.draw(leaderBoard);
                        leaderboard.draw(leader);
                        leaderboard.display();
                    }
                }
            }
        }
    }
    return 0;
}
