#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;

int pawn_value = 1000; // millipawns
int bishop_value = 3000;
int knight_value = 3000;
int rook_value = 5000;
int queen_value = 9000;

Eigen::Array<int,8,8> white_pawn_pos_value;
Eigen::Array<int,8,8> white_bishop_pos_value;
Eigen::Array<int,8,8> white_knight_pos_value;
Eigen::Array<int,8,8> white_rook_pos_value;
Eigen::Array<int,8,8> white_queen_pos_value;
Eigen::Array<int,8,8> white_king_pos_value;
Eigen::Array<int,8,8> white_king_pos_value_late;

Eigen::Array<int,8,8> black_pawn_pos_value;
Eigen::Array<int,8,8> black_bishop_pos_value;
Eigen::Array<int,8,8> black_knight_pos_value;
Eigen::Array<int,8,8> black_rook_pos_value;
Eigen::Array<int,8,8> black_queen_pos_value;
Eigen::Array<int,8,8> black_king_pos_value;
Eigen::Array<int,8,8> black_king_pos_value_late;



void initialize_piece_square_tables() {
// piece square tables, relative to black side of board:
    black_pawn_pos_value << 
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
         5,  5, 10, 25, 25, 10,  5,  5,
         0,  0,  0, 20, 20,  0,  0,  0,
         5, -5,-10,  0,  0,-10, -5,  5,
         5, 10, 10,-20,-20, 10, 10,  5,
         0,  0,  0,  0,  0,  0,  0,  0;

    black_knight_pos_value <<
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50;

    black_bishop_pos_value << 
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20;

    black_rook_pos_value <<
         0,  0,  0,  0,  0,  0,  0,  0,
         5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
         0,  0,  0,  5,  5,  0,  0,  0;

    black_queen_pos_value <<
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
         -5,  0,  5,  5,  5,  5,  0, -5,
          0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20;

    black_king_pos_value <<
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
         20, 20,  0,  0,  0,  0, 20, 20,
         20, 30, 10,  0,  0, 10, 30, 20;

    black_king_pos_value_late <<
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -50,-30,-30,-30,-30,-30,-30,-50;

    // equivalent for white is just a vertical mirroring:

    white_pawn_pos_value = black_pawn_pos_value.colwise().reverse();
    white_bishop_pos_value = black_bishop_pos_value.colwise().reverse();
    white_knight_pos_value = black_knight_pos_value.colwise().reverse();
    white_rook_pos_value = black_rook_pos_value.colwise().reverse();
    white_queen_pos_value = black_queen_pos_value.colwise().reverse();
    white_king_pos_value = black_king_pos_value.colwise().reverse();
    white_king_pos_value_late = black_king_pos_value_late.colwise().reverse();
}