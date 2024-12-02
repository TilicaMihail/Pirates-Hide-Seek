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

int game_board[4][3][3], pieces[4][4][3][3], pieces_positions[4], piece_orientation[4], fr[4], cnt;
int number_of_challanges;
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

void get_random_challange() {
    
}

int main() {
    
}