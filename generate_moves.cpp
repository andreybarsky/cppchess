#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <memory>
#include "board.h"

using namespace std;
using Eigen::Array;

typedef vector<Coord> Cvec;
typedef shared_ptr<Cvec> Cvec_ptr;
typedef vector<Move> Mvec;
typedef shared_ptr<Mvec> Mvec_ptr;

Cvec_ptr where(Array<bool,8,8> arr) {
    // returns a pointer to a vector of coordinate pairs 
    // corresponding to where the input array is true
    Cvec_ptr coord_vec_ptr ( new Cvec );

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (arr(y,x)) {
                Coord c = {y,x};
                coord_vec_ptr -> push_back(c);
            }
        }
    }

    return coord_vec_ptr;
}

void Board::generate_moves(int player) {
    generate_pawn_moves(player);
}

void Board::generate_pawn_moves(int player) {

    // player is 0 (white) or 1 (black)

    Array<bool,8,8> * player_colour_array_ptr = (player ? &blacks : &whites);
    Array<bool,8,8> * enemy_colour_array_ptr = ((!player) ? &blacks : &whites);

    Array<bool,8,8> player_pawns = pawns * (*player_colour_array_ptr);

    Array<bool,8,8> all_pieces = whites + blacks;


    Cvec pawn_locations = *where(player_pawns);
    Mvec_ptr moves_ptr ( new Mvec ) ;


    int forward_direction = (player ? -1 : +1); // pawn forward movement
    int start_row = (player ? 6 : 1); // can double push if on this row
    int end_row = (player ? 1 : 6); // can promote if on this row

    for (unsigned int i = 0; i < pawn_locations.size(); i++) {
        // for each pawn
        Coord pawn = (pawn_locations)[i];
        Coord next_square = {pawn.row + forward_direction, pawn.col};
        if (!all_pieces(next_square.row, next_square.col)) {
            // if the next square is empty, valid move
            bool promotion = (pawn.row == end_row);
            if (promotion) {
                // promotion from forward push
                Move knight_promo_push = {pawn, next_square, 0, promotion, 0, 0};
                Move bishop_promo_push = {pawn, next_square, 0, promotion, 0, 1};
                Move rook_promo_push = {pawn, next_square, 0, promotion, 1, 0};
                Move queen_promo_push = {pawn, next_square, 0, promotion, 1, 1};
                moves_ptr -> push_back (knight_promo_push);
                moves_ptr -> push_back (bishop_promo_push);
                moves_ptr -> push_back (rook_promo_push);
                moves_ptr -> push_back (queen_promo_push);
            } else {
                // regular forward push
                Move pawn_push = {pawn, next_square, 0, 0, 0, 0};
                moves_ptr -> push_back (pawn_push);

                cout << "Pawn at position " << pawn.row << "," << pawn.col << " can push" << endl;

                // double push
                bool has_moved = (pawn.row != start_row);
                if (!has_moved) {
                    Coord next_next_square = {pawn.row + (forward_direction*2), pawn.col};
                    if (!all_pieces(next_next_square.row, next_next_square.col)) {
                        Move pawn_double_push = {pawn, next_next_square, 0, 0, 0, 1};
                        moves_ptr -> push_back (pawn_double_push);
                        cout << "Pawn at position " << pawn.row << "," << pawn.col << " can double push" << endl;
                    }
                }
            }
        }

        // captures:

        Coord left_diagonal = {pawn.row + forward_direction, pawn.col - 1};
        Coord right_diagonal = {pawn.row + forward_direction, pawn.col + 1};

        bool promotion = (pawn.row == end_row);

        // to left side:
        if ((pawn.col - 1) > 0) {
            if ((*enemy_colour_array_ptr)(left_diagonal.row, left_diagonal.col)) {
                if (promotion) {
                    Move knight_promo_cap_left = {pawn, left_diagonal, 1, promotion, 0, 0};
                    Move bishop_promo_cap_left = {pawn, left_diagonal, 1, promotion, 0, 1};
                    Move rook_promo_cap_left = {pawn, left_diagonal, 1, promotion, 1, 0};
                    Move queen_promo_cap_left = {pawn, left_diagonal, 1, promotion, 1, 1};
                    moves_ptr -> push_back (knight_promo_cap_left);
                    moves_ptr -> push_back (bishop_promo_cap_left);
                    moves_ptr -> push_back (rook_promo_cap_left);
                    moves_ptr -> push_back (queen_promo_cap_left);
                } else {
                    Move pawn_cap_left = {pawn, left_diagonal, 1, 0, 0, 0};
                    moves_ptr -> push_back (pawn_cap_left);
                    cout << "Pawn at position " << pawn.row << "," << pawn.col << " can cap left" << endl;
                }
            }            
        }

        // to right side:
        if ((pawn.col + 1) < 8) {
            if ((*enemy_colour_array_ptr)(right_diagonal.row, right_diagonal.col)) {
                if (promotion) {
                    Move knight_promo_cap_right = {pawn, right_diagonal, 1, promotion, 0, 0};
                    Move bishop_promo_cap_right = {pawn, right_diagonal, 1, promotion, 0, 1};
                    Move rook_promo_cap_right = {pawn, right_diagonal, 1, promotion, 1, 0};
                    Move queen_promo_cap_right = {pawn, right_diagonal, 1, promotion, 1, 1};
                    moves_ptr -> push_back (knight_promo_cap_right);
                    moves_ptr -> push_back (bishop_promo_cap_right);
                    moves_ptr -> push_back (rook_promo_cap_right);
                    moves_ptr -> push_back (queen_promo_cap_right);
                } else {
                    Move pawn_cap_right = {pawn, right_diagonal, 1, 0, 0, 0};
                    moves_ptr -> push_back (pawn_cap_right);
                    cout << "Pawn at position " << pawn.row << "," << pawn.col << " can cap right" << endl;
                }
            }
        }
    }

     // vector<Move> pawn_moves;

}

