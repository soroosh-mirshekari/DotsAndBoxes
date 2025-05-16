#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <windows.h>


using namespace std;
string const SCORE_BOARD = "scoreboard.csv";
const int MAX_ROWS = 100;
const int MAX_COLS = 2;

class ScoreBoardRow {
public:
    string name;
    int wins;

    ScoreBoardRow(string n, int w) {
        name = n;
        wins = w;
    }

    bool operator<(const ScoreBoardRow &obj) const {
        return wins > obj.wins;
    }
};

string left_number(int number, int width) {


    string num = to_string(number);
    int white_space = width - num.length();
    for (int i = 0; i < white_space; ++i) {
        num += " ";
    }

    return num;
}


void screen_wipe();

void write_to_file(vector<ScoreBoardRow> v);

vector<ScoreBoardRow> read_score_board();

void score_board(bool wipe);

void main_menu(bool wipe);

class Covertor {
public:
    char o;
    int y;
    int x;

    Covertor(int ix, int iy) {
        if (ix % 2 == 1) {
            o = 'h';
            x = (ix - 1) / 2;
            y = iy / 2;
        } else {
            o = 'v';
            x = ix / 2;
            y = (iy - 1) / 2;
        }
    }
};

class Player {
private:
    string name;
    int color;
    int score;
    int wins = 0;
public:
    Player(string n, int c, int s) {
        name = n;
        color = c;
        score = s;
    }

    string get_name() {
        return name;
    }

    int get_color() {
        return color;
    }

    void add_score(int s) {
        score += s;
    }

    int get_score() {
        return score;
    }

    void add_win() {
        wins++;
    }

    void reset_score() {
        score = 0;
    }

    int get_wins() {
        return wins;
    }

    bool operator<(const Player &obj) const {
        return wins > obj.wins;
    }

};

vector<Player> all_players;
int height = 4;
int widht = 4;

void update_score_board(vector<Player> p);

void color_print(string s, int color);

void add_win(string name);

class Game {
private:
    int total_boxes = 0;
    int game_height;
    int game_widht;
    vector<vector<int>> hlines;
    vector<vector<int>> vlines;
    vector<vector<int>> boxes;

    int turn = 0;
public:
    Game(int h, int w) {
        game_height = h;
        game_widht = w;
        for (int i = 0; i < game_height; ++i) {
            vector<int> t;
            for (int j = 0; j < game_widht - 1; ++j) {
                t.push_back(-1);
            }
            hlines.push_back(t);
        }
        for (int i = 0; i < game_height - 1; ++i) {
            vector<int> t;
            for (int j = 0; j < game_widht; ++j) {
                t.push_back(-1);
            }
            vlines.push_back(t);
        }
        for (int i = 0; i < game_height - 1; ++i) {
            vector<int> t;
            for (int j = 0; j < game_widht - 1; ++j) {
                t.push_back(-1);
            }
            boxes.push_back(t);
        }

    }


    void draw_board(bool wipe) {
        if (wipe) { screen_wipe(); }
        cout << "     ";
        cout << "now is ";
        color_print(all_players[turn].get_name(), all_players[turn].get_color());
        cout << " turn" << endl << endl << endl;
        cout << "          ";
        for (int i = 0; i < widht * 2 - 1; ++i) {
            cout << left_number(i, 5);

        }
        cout << endl << endl;
        for (int row = 0; row < height; ++row) {
            cout << "     ";
            cout << left_number(row * 2, 5);
            for (int col = 0; col < widht - 1; ++col) {
                cout << "*";
                if (hlines[row][col] == -1) {
                    cout << "         ";
                } else {
                    color_print("---------", all_players[hlines[row][col]].get_color());
                }

            }
            cout << "*" << endl;
            if (row < height - 1) {
                cout << "          ";
                for (int col = 0; col < widht; ++col) {
                    if (vlines[row][col] == -1) {
                        cout << "          ";
                    } else {
                        if (boxes[row][col] == -1) {
                            color_print("|         ", all_players[vlines[row][col]].get_color());
                        } else {
                            color_print("|", all_players[vlines[row][col]].get_color());
                            if (col < game_widht - 1) {
                                color_print("*********", all_players[boxes[row][col]].get_color());
                            }

                        }

                    }

                }
                cout << endl;
                cout << "     ";
                cout << left_number(row * 2 + 1, 5);
                for (int col = 0; col < widht; ++col) {
                    if (vlines[row][col] == -1) {
                        cout << "          ";
                    } else {
                        if (boxes[row][col] == -1) {
                            color_print("|         ", all_players[vlines[row][col]].get_color());
                        } else {
                            color_print("|", all_players[vlines[row][col]].get_color());
                            if (col < game_widht - 1) {
                                color_print("*********", all_players[boxes[row][col]].get_color());
                            }

                        }
                    }

                }
                cout << endl;
                cout << "          ";
                for (int col = 0; col < widht; ++col) {
                    if (vlines[row][col] == -1) {
                        cout << "          ";
                    } else {
                        if (boxes[row][col] == -1) {
                            color_print("|         ", all_players[vlines[row][col]].get_color());
                        } else {
                            color_print("|", all_players[vlines[row][col]].get_color());
                            if (col < game_widht - 1) {
                                color_print("*********", all_players[boxes[row][col]].get_color());
                            }

                        }
                    }

                }
                cout << endl;


            }
        }


        cout << endl << endl;
        cout << "     ";
        for (int i = 0; i < all_players.size(); ++i) {
            color_print(all_players[i].get_name(), all_players[i].get_color());
            cout << " : ";
            color_print(to_string(all_players[i].get_score()), all_players[i].get_color());
            cout << " | ";
        }
        cout << endl;
        add_line(false);


    }

    void add_line(bool wipe) {
        if (wipe) {
            screen_wipe();
        }
        int free_lines = 0;
        for (int i = 0; i < hlines.size(); ++i) {
            for (int j = 0; j < hlines[i].size(); ++j) {
                if (hlines[i][j] == -1) {
                    free_lines++;
                }
            }
        }
        for (int i = 0; i < vlines.size(); ++i) {
            for (int j = 0; j < vlines[i].size(); ++j) {
                if (vlines[i][j] == -1) {
                    free_lines++;
                }
            }
        }
        if (free_lines <= 0) {
            cout << "game ended!" << endl;
            int winner = 0;
            for (int i = 1; i < all_players.size(); ++i) {
                if (all_players[i].get_score() > all_players[winner].get_score()) {
                    winner = i;
                }
            }
            for (int i = 0; i < all_players.size(); ++i) {
                if (i != winner && all_players[i].get_score() == all_players[winner].get_score()) {
                    cout << "the game is a tie" << endl;
                    for (int j = 0; j < all_players.size(); ++j) {
                        all_players[j].reset_score();
                    }
                    score_board(false);
                }
            }
            all_players[winner].add_win();
            for (int i = 0; i < all_players.size(); ++i) {
                all_players[i].reset_score();
            }
            color_print(all_players[winner].get_name() + " wins the game!", all_players[winner].get_color());
            cout << endl;
            add_win(all_players[winner].get_name());

            score_board(false);
        }

        int ix, iy;
        int y, x;
        char o;
        cout << "please give line coordination and orientation : or enter -1 -1 to leave " << endl;
        cin >> iy >> ix;
        if (ix == -1 && iy == -1) {
            for (int i = 0; i < all_players.size(); ++i) {
                all_players[i].reset_score();
            }
            main_menu(true);
        }
        Covertor c = Covertor(ix, iy);
        y = c.y;
        x = c.x;
        o = c.o;
        if (cin.fail() || ix % 2 == iy % 2) {
            cout << "you entered wrong input" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            add_line(false);
        }
        if (o == 'h') {
            if (y >= hlines.size() || x >= hlines[0].size()) {
                cout << "you entered wrong input" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                add_line(false);
            }
            if (hlines[y][x] == -1) {
                hlines[y][x] = turn;
                cout << "line added!" << endl;

            } else {
                cout << "this line exist!" << endl;
                add_line(false);
            }

        } else if (o == 'v') {
            if (y >= vlines.size() || x >= vlines[0].size()) {
                cout << "you entered wrong input" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                add_line(false);
            }
            if (vlines[y][x] == -1) {
                vlines[y][x] = turn;
                cout << "line added!" << endl;

            } else {
                cout << "this line exist!" << endl;
                add_line(false);
            }

        } else {
            cout << "you entered wrong input" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            add_line(false);
        }
        int new_box = box_count();
        int diff = new_box - total_boxes;
        total_boxes = new_box;
        if (diff == 0) {
            turn++;
            if (turn >= all_players.size()) {
                turn = 0;
            }
        } else {
            all_players[turn].add_score(diff);
        }
        draw_board(true);
    }

    int box_count() {
        int box_count = 0;
        for (int i = 0; i < hlines.size() - 1; ++i) {
            for (int j = 0; j < hlines[i].size(); ++j) {
                if (hlines[i][j] != -1) {
                    if (hlines[i + 1][j] != -1) {
                        if (vlines[i][j] != -1) {
                            if (vlines[i][j + 1] != -1) {
                                box_count++;
                                if (boxes[i][j] == -1) {
                                    boxes[i][j] = turn;
                                }
                            }
                        }
                    }
                }
            }

        }
        return box_count;
    }

};

void player_menu(bool wipe);

void SetColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,
                            (bgColor << 4) | textColor);
}

void color_print(const string text, int color) {
    SetColor(color, 0);
    cout << text;
    SetColor(7, 0);
}

void screen_wipe() {
    cout << "--------------------------above screen should wiped!-----------------------------" << endl;
    system("CLS");
}


void size_menu(bool wipe);


void main_menu(bool wipe) {
    if (wipe) {
        screen_wipe();
    }
    int command;
    cout << "1.new game" << endl << "2.change size" << endl << "3.add players" << endl << "4.score board" << endl;
    cin >> command;
    if (command == 1) {
        if (all_players.size() < 2) {
            cout << "you have less than 2 players please add them: " << endl;
            player_menu(false);
        } else {
            Game new_game = Game(height, widht);
            new_game.draw_board(true);
        }

    } else if (command == 2) {
        size_menu(true);
    } else if (command == 3) {
        player_menu(true);
    } else if (command == 4) {
        score_board(true);
    } else {
        cout << "you entered wrong input!" << endl;
        cin.clear();


        cin.ignore(1000, '\n');


        main_menu(false);
    }


}


void size_menu(bool wipe) {
    if (wipe) {
        screen_wipe();
    }

    int input;
    cout << "current board size is height: " << height << " widht: " << widht << endl;
    cout << "1.change " << endl << "0.return to main menu" << endl;
    cin >> input;
    if (input == 0) {
        main_menu(true);
    } else if (input == 1) {
        int h, w;
        cout << "enter height and width: " << endl;
        cin >> h >> w;
        if (h < 4 || w < 4) {
            cout << "wrong input: " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            size_menu(false);
        } else {
            height = h;
            widht = w;
            cout << "size changed!" << endl;

            size_menu(true);
        }

    } else {
        cout << "wrong input" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        size_menu(false);
    }

}

void player_menu(bool wipe) {
    if (wipe) {
        screen_wipe();
    }
    int input;
    int del_input;
    string in_name;
    int in_color;
    cout << "color codes are: ";
    for (int i = 1; i < 15; ++i) {
        color_print(to_string(i), i);
        cout << "  |  ";
    }
    cout << endl;
    for (int i = 0; i < all_players.size(); ++i) {
        cout << "    " << i + 1 << " - ";
        color_print(all_players[i].get_name(), all_players[i].get_color());
        cout << endl;
    }
    cout << "enter: " << endl << "1 to add new player" << endl << "2 to delete player" << endl
         << "0 to return to main menu" << endl;
    cin >> input;
    if (input == 0) {
        main_menu(true);
    } else if (input == 1) {
        cout << "enter player name and color code to add it: " << endl;
        cin >> in_name >> in_color;
        if (cin.fail()) {
            cout << "you entered wrong input" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            player_menu(false);
        }
        Player temp(in_name, in_color, 0);
        all_players.push_back(temp);
        player_menu(true);
    } else if (input == 2) {
        cout << "enter player number: " << endl;
        cin >> del_input;
        if (cin.fail()) {
            cout << "you entered wrong input" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            player_menu(false);
        }
        all_players.erase(all_players.begin() + del_input - 1);
        player_menu(false);
    } else {
        cout << "wrong input!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        player_menu(false);
    }

}

void score_board(bool wipe) {
    if (wipe) {
        screen_wipe();
    }
    int x;
    update_score_board(all_players);
    vector<ScoreBoardRow> v = read_score_board();
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i) {
        cout << i + 1 << "-" << v[i].name << "  " << v[i].wins << endl;
    }
    cout << "press 0 to return" << endl;
    cin >> x;
    if (x == 0) {
        main_menu(true);
    } else {
        cout << "wrong input!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        score_board(false);
    }

}


vector<ScoreBoardRow> read_score_board() {
    vector<ScoreBoardRow> rows;
    ifstream file(SCORE_BOARD);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string data[MAX_ROWS][MAX_COLS];
    string line;
    int row = 0;
    while (getline(file, line)) 
	{
		if(line.length() == 0){
			break;
		}
        stringstream ss(line);
        string cell;
        int col = 0;
        while (getline(ss, cell, ',') && col < MAX_COLS) {
            data[row][col] = cell;
            col++;
        }
        row++;
    }

    file.close();
    for (int i = 0; i < row; ++i) {
        rows.push_back(ScoreBoardRow(data[i][0], stoi(data[i][1])));
    }
    return rows;


}


void update_score_board(vector<Player> p) {
    vector<ScoreBoardRow> v = read_score_board();
    vector<Player> missing;
    for (int i = 0; i < p.size(); ++i) {
        bool found = false;
        for (int j = 0; j < v.size(); ++j) {
            if (p[i].get_name() == v[j].name) {
                found = true;
            }
        }
        if (!found) {
            missing.push_back(p[i]);
        }

    }
    for (int i = 0; i < missing.size(); ++i) {
        v.push_back(ScoreBoardRow(missing[i].get_name(), missing[i].get_wins()));
    }
    write_to_file(v);


}

void add_win(string name) {
    vector<ScoreBoardRow> v = read_score_board();
    for (int i = 0; i < v.size(); ++i) {
        if (name == v[i].name) {
            v[i].wins++;
            break;
        }
    }
    write_to_file(v);
}

void write_to_file(vector<ScoreBoardRow> v) {
    std::ofstream ofs;
    ofs.open(SCORE_BOARD, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    fstream fout;
    fout.open(SCORE_BOARD, ios::out | ios::app);
    for (int i = 0; i < v.size(); ++i) {
        fout << v[i].name << "," << v[i].wins << "\n";
    }
    fout.close();
}


int main() {
    main_menu(true);


    return 0;
}