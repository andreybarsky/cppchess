#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <string>
#include "board.h"

using namespace std;
using Eigen::Array;

extern void initialize_piece_square_tables();

Board::Board(bool debug) {
    initialize();
    debug_mode = debug;
}

void Board::initialize() {
    // ensure bitboards are empty:
    whites.fill(0);
    blacks.fill(0);
    pawns.fill(0);
    bishops.fill(0);
    knights.fill(0);
    rooks.fill(0);
    queens.fill(0);
    kings.fill(0);
    threats.fill(0);

    player = 0; // white
    turn = 0;
    in_check = 0;
    game_phase = 0; // early to late game

    // populate pawns:
    for(int i = 0; i < 8; i++)
    {
        whites(1,i) = 1;
        pawns(1,i) = 1;

        blacks(6,i) = 1;
        pawns(6,i) = 1;
    }

    // populate bishops:
    for(int i = 2; i < 8; i += 3)
    {
        whites(0,i) = 1;
        bishops(0,i) = 1;

        blacks(7,i) = 1;
        bishops(7,i) = 1;
    }

    // populate knights:
    for(int i = 1; i < 8; i += 5)
    {
        whites(0,i) = 1;
        knights(0,i) = 1;

        blacks(7,i) = 1;
        knights(7,i) = 1;
    }

    // populate rooks:
    for(int i = 0; i < 8; i += 7)
    {
        whites(0,i) = 1;
        rooks(0,i) = 1;

        blacks(7,i) = 1;
        rooks(7,i) = 1;
    }

    // populate kings and queens:
    queens(0,3) = 1;
    whites(0,3) = 1;

    kings(0,4) = 1;
    whites(0,4) = 1;

    queens(7,3) = 1;
    blacks(7,3) = 1;

    kings(7,4) = 1;
    blacks(7,4) = 1;
}

void Board::shift_piece(int fx, int fy, int tx, int ty) {
    // shift colour first:
    shift_colour(fx, fy, tx, ty);
    // then shift the right piece type, stopping if we've found it:
    if (pawns(fx, fy)) {
        shift_pawn(fx, fy, tx, ty);
    }
    else if (bishops(fx, fy)) {
        shift_bishop(fx, fy, tx, ty);
    }
    else if (knights(fx, fy)) {
        shift_knight(fx, fy, tx, ty);
    }
    else if (rooks(fx, fy)) {
        shift_rook(fx, fy, tx, ty);
    }
    else if (queens(fx, fy)) {
        shift_queen(fx, fy, tx, ty);
    }
    else if (kings(fx, fy)) {
        shift_king(fx, fy, tx, ty);
    }
}

void Board::shift_colour(int fx, int fy, int tx, int ty) {
    // shift blackness and whiteness: (no need to check which)
    whites(tx, ty) = whites(fx, fy);
    blacks(tx, ty) = blacks(fx, fy);
    whites(fx, fy) = 0;
    blacks(fx, fy) = 0;
}

void Board::shift_pawn(int fx, int fy, int tx, int ty) {
    pawns(tx, ty) = pawns(fx, fy);
    pawns(fx, fy) = 0;
}

void Board::shift_bishop(int fx, int fy, int tx, int ty) {
    bishops(tx, ty) = bishops(fx, fy);
    bishops(fx, fy) = 0;
}

void Board::shift_knight(int fx, int fy, int tx, int ty) {
    knights(tx, ty) = knights(fx, fy);
    knights(fx, fy) = 0;
}

void Board::shift_rook(int fx, int fy, int tx, int ty) {
    rooks(tx, ty) = rooks(fx, fy);
    rooks(fx, fy) = 0;
}

void Board::shift_queen(int fx, int fy, int tx, int ty) {
    queens(tx, ty) = queens(fx, fy);
    queens(fx, fy) = 0;
}

void Board::shift_king(int fx, int fy, int tx, int ty) {
    kings(tx, ty) = kings(fx, fy);
    kings(fx, fy) = 0;
}

void Board::display() {
    cout << "+-----------------------+" << endl;
    for (int rank = 0; rank < 8; rank++) {
        cout << '|';
        for (int file = 0; file < 8; file++) {
            if (!whites(rank,file) && !blacks(rank,file)) {
                if (rank % 2 == file % 2) {
                    cout << "::"; // black square
                }
                else {
                    cout << "  "; // white square
                }
            }
            else {
                // first char is colour
                cout << (whites(rank,file) ? 'w' : 'b');
                // second char is piece-type
                cout << (pawns(rank,file) ? "p" : "");
                cout << (knights(rank,file) ? "N" : "");
                cout << (bishops(rank,file) ? "B" : "");
                cout << (rooks(rank,file) ? "R" : "");
                cout << (queens(rank,file) ? "Q" : "");
                cout << (kings(rank,file) ? "K" : "");
            }
            if (file < 7) {
                cout << ' '; // empty space between pieces
            }
        }
        cout << '|' << endl;
    }
    cout << "+-----------------------+" << endl;
}

pair<int,int> parse(string square) {
    // accepts an alphanumeric string like "e4"
    // and returns zero-indexed int coordinates
    char file = square[0];
    char rank = square[1];
    int col = file - 97;
    int row = rank - 49;
    pair<int, int> coord (row,col);
    cout << "Parsed as " << row << "," << col << endl;
    return coord;
}

void Board::user_move() {
    // request a move-from and a move-to
    // and execute those moves

    string from_square;
    string to_square;

    cout << "Move from:" << endl;
    cin >> from_square;
    pair<int, int> from = parse(from_square);

    cout << "Move to:" << endl;
    cin >> to_square;
    pair<int, int> to = parse(to_square);

    shift_piece(from.first, from.second, to.first, to.second);
    display();
}

int Board::evaluate() {
    // return an int scalar representing favourability
    // of board state for white
    int total_score = 0;
    total_score += evaluate_material();
    total_score += evaluate_positions();
    // total_score += evaluate_pawns();
    return total_score;
}


int main() {
    // calculate positional advantage arrays at runtime:
    initialize_piece_square_tables();

    Board mainboard(true);
    mainboard.display();
    int player = 0;
    while (true)
    {
        mainboard.generate_moves(player);
        mainboard.user_move();
        // mainboard.evaluate();
        player = 1-player;
    }


    return 0;
}