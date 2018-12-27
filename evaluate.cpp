#include <iostream>
#include <string>
#include "board.h"
using namespace std;
using Eigen::Array;

extern int pawn_value;
extern int bishop_value;
extern int knight_value;
extern int rook_value;
extern int queen_value;

extern Array<int,8,8> white_pawn_pos_value;
extern Array<int,8,8> white_bishop_pos_value;
extern Array<int,8,8> white_knight_pos_value;
extern Array<int,8,8> white_rook_pos_value;
extern Array<int,8,8> white_queen_pos_value;
extern Array<int,8,8> white_king_pos_value;
extern Array<int,8,8> white_king_pos_value_late;

extern Array<int,8,8> black_pawn_pos_value;
extern Array<int,8,8> black_bishop_pos_value;
extern Array<int,8,8> black_knight_pos_value;
extern Array<int,8,8> black_rook_pos_value;
extern Array<int,8,8> black_queen_pos_value;
extern Array<int,8,8> black_king_pos_value;
extern Array<int,8,8> black_king_pos_value_late;

int Board::evaluate_material() {
    // calculate number of pieces of each type and multiply by piece value:
    int white_pawn_value = ((whites * pawns).cast <int> ().sum()) * pawn_value;
    int white_bishop_value = ((whites * bishops).cast <int> ().sum()) * bishop_value;
    int white_knight_value = ((whites * knights).cast <int> ().sum()) * knight_value;
    int white_rook_value = ((whites * rooks).cast <int> ().sum()) * rook_value;
    int white_queen_value = ((whites * queens).cast <int> ().sum()) * queen_value;

    int black_pawn_value = ((blacks * pawns).cast <int> ().sum()) * pawn_value;
    int black_bishop_value = ((blacks * bishops).cast <int> ().sum()) * bishop_value;
    int black_knight_value = ((blacks * knights).cast <int> ().sum()) * knight_value;
    int black_rook_value = ((blacks * rooks).cast <int> ().sum()) * rook_value;
    int black_queen_value = ((blacks * queens).cast <int> ().sum()) * queen_value;

    int white_value = white_pawn_value 
                + white_bishop_value 
                + white_knight_value 
                + white_rook_value 
                + white_queen_value;

    int black_value = black_pawn_value 
            + black_bishop_value 
            + black_knight_value 
            + black_rook_value 
            + black_queen_value;

    int white_advantage = white_value - black_value;

    if (debug_mode) {
        cout << "------Material evaluation------" << endl
         << "White pawns:    " << white_pawn_value << endl
         << "White bishops:  " << white_bishop_value << endl
         << "White knights:  " << white_knight_value << endl
         << "White rooks:    " << white_rook_value << endl
         << "White queens:   " << white_queen_value << endl
         << "-------------------------------" << endl
         << "Black pawns:    " << black_pawn_value << endl
         << "Black bishops:  " << black_bishop_value << endl
         << "Black knights:  " << black_knight_value << endl
         << "Black rooks:    " << black_rook_value << endl
         << "Black queens:   " << black_queen_value << endl
         << "-------------------------------" << endl
         << "White advantage: " << white_advantage << endl << endl; 

    }
    return (white_advantage);
}

int Board::evaluate_positions() {
    // calculate number of pieces of each type and multiply by piece value:

    Array<int,8,8> white_pawn_value = ((whites * pawns).cast<int>() * white_pawn_pos_value) ;
    Array<int,8,8> white_bishop_value = ((whites * bishops).cast<int>() * white_bishop_pos_value) ;
    Array<int,8,8> white_knight_value = ((whites * knights).cast<int>() * white_knight_pos_value) ;
    Array<int,8,8> white_rook_value = ((whites * rooks).cast<int>() * white_rook_pos_value) ;
    Array<int,8,8> white_queen_value = ((whites * queens).cast<int>() * white_queen_pos_value) ;

    Array<int,8,8> white_king_value;
    if (game_phase == 0) {
        // early game
        white_king_value = ((whites * kings).cast<int>() * white_king_pos_value);
    }
    else {
        // late game
        white_king_value = ((whites * kings).cast<int>() * white_king_pos_value_late);
    }

    Array<int,8,8> black_pawn_value = ((blacks * pawns).cast<int>() * black_pawn_pos_value);
    Array<int,8,8> black_bishop_value = ((blacks * bishops).cast<int>() * black_bishop_pos_value) ;
    Array<int,8,8> black_knight_value = ((blacks * knights).cast<int>() * black_knight_pos_value) ;
    Array<int,8,8> black_rook_value = ((blacks * rooks).cast<int>() * black_rook_pos_value) ;
    Array<int,8,8> black_queen_value = ((blacks * queens).cast<int>() * black_queen_pos_value) ;

    Array<int,8,8> black_king_value;
    if (game_phase == 0) {
        // early game
        black_king_value = ((blacks * kings).cast<int>() * black_king_pos_value) ;
    }
    else {
        // late game
        black_king_value = ((blacks * kings).cast<int>() * black_king_pos_value_late);
    }
    
    Array<int,8,8> white_value = white_pawn_value 
                + white_bishop_value 
                + white_knight_value 
                + white_rook_value 
                + white_queen_value
                + white_king_value;

    Array<int,8,8> black_value = black_pawn_value 
            + black_bishop_value 
            + black_knight_value 
            + black_rook_value 
            + black_queen_value
            + black_king_value;

    Array<int,8,8> white_advantage = white_value - black_value;

    int total_white_advantage = white_advantage.sum();

    if (debug_mode) {
        cout << "------Position evaluation------" << endl
         << white_advantage
         << endl << "-------------------------------" << endl
         << "White advantage: " << total_white_advantage << endl << endl; 

    }
    return (total_white_advantage);
}
