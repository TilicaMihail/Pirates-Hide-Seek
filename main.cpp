#include <iostream> 
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
using namespace std;

ifstream fin("db.txt");
ifstream fin_board("game_board.txt");
ifstream fin_piece("pieces.txt");
ofstream fout("db.txt");

//typedef void *action();

int game_board[4][3][3], pieces[4][4][3][3], pieces_positions[4], piece_orientation[4], fr[4], cnt, piece_to_move = -1, pieces_moved[4];
int number_of_challanges;
string current_screen = "menu", last_screen = "";
bool game_lost = 0;
vector<int> current_challange;
vector<vector<int>> challanges;
map <string, int> challanges_map;
// pieces[orientation][piece_id][][]

void get_game_board() {
    for(int i = 0; i < 4; i ++)
        for(int j = 0; j < 3; j ++)
            for(int k = 0; k < 3; k ++)
                fin_board >> game_board[i][j][k];
}

void get_pieces() {
    for(int i = 0; i < 4; i ++)
        pieces_positions[i] = -1;
    for(int i = 0; i < 4; i ++)
        for(int j = 0; j < 3; j ++)
            for(int k = 0; k < 3; k ++)
                fin_piece >> pieces[0][i][j][k];
}

void gen_rotated_pieces() {
    for(int i = 0; i < 4; i ++)
        for(int j = 1; j < 4; j ++)
            for(int k = 0; k < 3; k ++)
                for(int l = 0; l < 3; l ++)
                    pieces[j][i][k][l] = pieces[j - 1][i][2 - l][k];

}

void init_game() {
    get_game_board();
    get_pieces();
    gen_rotated_pieces();
}

vector<int> get_free_sqares() {
    vector<int> result;
    for(int i = 0; i < 4; i ++)
        for(int j = 0; j < 3; j ++)
            for(int k = 0; k < 3; k ++)
                if(game_board[i][j][k] && pieces_positions[i] != -1 && !pieces[piece_orientation[pieces_positions[i]]][pieces_positions[i]][j][k])
                    result.push_back(game_board[i][j][k]);
    sort(result.begin(), result.end());
    return result;
}

bool compare_vectors(vector<int> a, vector<int> b) {
    int l1 = a.size(), l2 = b.size();
    if(l1 != l2)
        return false;
    for(int i = 0; i < min(l1, l2); i ++)
        if(a[i] != b[i])
            return false;
    return true;
}

bool is_correct_solution() {
    vector<int> current_solution;
    current_solution = get_free_sqares();
    return compare_vectors(current_solution, current_challange);
}

string vector_to_string(vector<int> a) {
    string result;
    int length = a.size();
    for(int i = 0; i < length; i ++)
        result = result + to_string(a[i]);
    return result;
}

void register_challange() {
    vector<int> challange;
    challange = get_free_sqares();
    if(challanges_map[vector_to_string(challange)] != 1)
        challanges.push_back(challange),
        challanges_map[vector_to_string(challange)] = 1;
}

void backtracking(int k) {
    for(int i = 0; i < 4; i ++) 
        for(int j = 0; j < 4; j ++)
            if(fr[i] == 0) {
                pieces_positions[k] = i;
                piece_orientation[i] = j;
                fr[i] = 1;
                    if(k == 3)
                        register_challange();
                    else 
                        backtracking(k + 1);
                fr[i] = 0;
            }
}

void save_challanges_to_db() {
    int l1 = challanges.size();
    cout << l1 << endl;
    for(int i = 0; i < l1; i ++) {
        int l2 = challanges[i].size();
        cout << l2 << endl;
        for(int k = 0; k < l2; k ++)
            cout << challanges[i][k] << " ";
    }
}

void generate_challanges() {
    backtracking(0);
    save_challanges_to_db();
}

void get_challanges() {
    
}

void change_orientation0() {
    piece_orientation[0] ++;
    piece_orientation[0] %= 4;
}

void change_orientation1() {
    piece_orientation[1] ++;
    piece_orientation[1] %= 4;
}

void change_orientation2() {
    piece_orientation[2] ++;
    piece_orientation[2] %= 4;
}

void change_orientation3() {
    piece_orientation[3] ++;
    piece_orientation[3] %= 4;
}

void activate_move0() {
    if(!pieces_moved[0])
        piece_to_move = 0;
}

void activate_move1() {
    if(!pieces_moved[0])
        piece_to_move = 1;
}

void activate_move2() {
    if(!pieces_moved[0])
        piece_to_move = 2;
}

void activate_move3() {
    if(!pieces_moved[0])
        piece_to_move = 3;
}

void move0() {
    pieces_positions[0] = piece_to_move;
    pieces_moved[piece_to_move] = 1;
    piece_to_move = -1;
}

void move1() {
    pieces_positions[1] = piece_to_move;
    pieces_moved[piece_to_move] = 1;
    piece_to_move = -1;
}

void move2() {
    pieces_positions[2] = piece_to_move;
    pieces_moved[piece_to_move] = 1;
    piece_to_move = -1;
}

void move3() {
    pieces_positions[3] = piece_to_move;
    pieces_moved[piece_to_move] = 1;
    piece_to_move = -1;
}

void new_game() {

}

void to_menu() {

}

void show_lose_message() {

}

void show_menu() {

}

void show_game() {

}

void show_rules() {

}

void handle_buttons() {

}

void game_loop() {
    while(true) {
        handle_buttons();
        if(last_screen != current_screen) {
            if(current_screen == "menu")
                show_menu();
            if(current_screen == "game")
                show_game();
            if(current_screen == "rules")
                show_rules();
        }
        if(current_screen == "game" && game_lost)
            show_lose_message();

    }
}

int main() {
    
}