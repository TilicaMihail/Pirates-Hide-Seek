#include <iostream> 
#include <graphics.h>
#include <winbgim.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <map>
using namespace std;

#define WINDOW_HEIGHT = 1000;
#define WINDOW_WIDTH = 1900;

ifstream fin("db.txt");
ifstream fin_board("game_board.txt");
ifstream fin_piece("pieces.txt");
ofstream fout("db.txt");

//typedef void *action();

int game_board[4][3][3], pieces[4][4][3][3], pieces_positions[4], piece_orientation[4], fr[4], cnt, piece_to_move = -1, pieces_moved[4];
int number_of_challanges;
string current_screen = "menu", last_screen = "";
bool game_lost = 0;
string button_pressed = "";
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

void get_game() {
    srand(time(0));
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
    fout << l1 << endl;
    for(int i = 0; i < l1; i ++) {
        int l2 = challanges[i].size();
        fout << l2 << endl;
        for(int k = 0; k < l2; k ++)
            fout << challanges[i][k] << " ";
        fout << endl;
    }
}

void generate_challanges() {
    backtracking(0);
    save_challanges_to_db();
}

void get_challanges() {
    challanges.clear();
    fin >> number_of_challanges;
    int n, m;
    for(int i = 0; i < number_of_challanges; i ++) {
        fin >> n;
        vector<int> input;
        for(int j = 0; j < n; j ++) {
            fin >> m,
            input.push_back(m);
        }
        challanges.push_back(input);
    }
}

void get_random_challange() {
    current_challange.clear();
    int random_index = rand() % number_of_challanges;
    int l = challanges[random_index].size();
    for(int i = 0; i < l; i ++)
        current_challange.push_back(challanges[random_index][i]);
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

void draw_rounded_rect(int left, int top, int right, int bottom, int radius) {
    arc(left + radius, top + radius, 180, 270, radius, radius);
    arc(right - radius, top + radius, 270, 360, radius, radius);
    arc(right - radius, bottom - radius, 0, 90, radius, radius);
    arc(left + radius, bottom - radius, 90, 180, radius, radius);
    line(left + radius, top, right - radius, top);
    line(left + radius, bottom, right - radius, bottom);
    line(left, top + radius, left, bottom - radius);
    line(right, top + radius, right, bottom - radius);
}

void draw_button(int top_left_x, int top_left_y, int width, int height, int padding, string text_file_name) {
    setfillstyle(1, 7);
    draw_rounded_rect(top_left_x, top_left_y, top_left_x + width, top_left_y + height, 10);
    floodfill(top_left_x + 1, top_left_y + 1, WHITE);
    readimagefile(
        text_file_name.c_str(), 
        top_left_x + padding, 
        top_left_y + padding, 
        top_left_x + width - padding, 
        top_left_y + height - padding
    );
}

void draw_piece(int x, int y, int size, int piece) {

}

void draw_board(int x, int y, int size) {

}

void draw_challange_bar(int x, int y, int width, int height) {

}

void draw_pieces_bar(int x, int y, int size) {

}

void remove_image(int top_left_x, int top_left_y, int width, int height) {
    // this does not remove the image but redraws the background on the spot that the image was in

}

void draw_background() {
    readimagefile("background.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

bool point_is_inside_box(int x, int y, int top_x, int top_y, int bot_x, int bot_y) {
    return false;
}

void init_buttons() {

}

void init_game() {
    get_game();
    generate_challanges();
    get_challanges();
    initgraph(WINDOW_HEIGHT, WINDOW_WIDTH, "Pirates Hide & Seek");
}

void close_game() {
    getch();
    closegraph();
}

void new_game() {
    get_random_challange();
    current_screen = "game";
}

void to_menu() {

}

void show_lose_message() {

}

void show_win_message() {
    
}

void show_menu() {
    cleardevice();
    draw_background();
    readimagefile("titlu.gif", WINDOW_WIDTH * 3 / 20, WINDOW_HEIGHT * 3 / 20, WINDOW_WIDTH * 6 / 20, WINDOW_HEIGHT * 17 / 20);
    draw_button(WINDOW_WIDTH * 4 / 20, WINDOW_HEIGHT * 15 / 20, WINDOW_WIDTH * 5 / 20, WINDOW_HEIGHT * 2 / 20, 0, "butonJoaca.gif");
    draw_button(WINDOW_WIDTH * 11 / 20, WINDOW_HEIGHT * 15 / 20, WINDOW_WIDTH * 5 / 20, WINDOW_HEIGHT * 2 / 20, 0, "butonReguli.gif");
}

void show_game() {
    cleardevice();
    draw_background();
}

void show_rules() {
    cleardevice();
    readimagefile("backgroundReguli.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    draw_button(WINDOW_WIDTH * 6 / 20, WINDOW_HEIGHT * 16 / 20, WINDOW_WIDTH * 14 / 20, WINDOW_HEIGHT * 18 / 20, 0, "butonIesire.gif");
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
            last_screen = current_screen;
        }
        if(current_screen == "game" && game_lost)
            show_lose_message();

    }
}

int main() {
    init_game();
    game_loop();
    close_game();
}