#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <string>

struct Coord{
    int row;
    int col;
};

struct Move{
    Coord from;
    Coord to;
    bool capture;
    bool promotion;
    bool special1; // used for castles, en passant
    bool special2; // promotion types, etc.
};


class Board{
protected:
    Eigen::Array<bool,8,8> whites;
    Eigen::Array<bool,8,8> blacks;

    Eigen::Array<bool,8,8> pawns;
    Eigen::Array<bool,8,8> bishops;
    Eigen::Array<bool,8,8> knights;
    Eigen::Array<bool,8,8> rooks;
    Eigen::Array<bool,8,8> queens;
    Eigen::Array<bool,8,8> kings;

    Eigen::Array<bool,8,8> threats;

    bool player; 
    int turn;
    int game_phase;
    bool in_check;
    bool debug_mode;

private:
    // updates piece positions from old square to new square:
    void shift_piece(int fx, int fy, int tx, int ty);
    // subroutines of that:
    void shift_colour(int fx, int fy, int tx, int ty);
    void shift_pawn(int fx, int fy, int tx, int ty);
    void shift_bishop(int fx, int fy, int tx, int ty);
    void shift_knight(int fx, int fy, int tx, int ty);
    void shift_rook(int fx, int fy, int tx, int ty);
    void shift_queen(int fx, int fy, int tx, int ty);
    void shift_king(int fx, int fy, int tx, int ty);

    // move generation:
    // std::vector<struct Move> generate_pawn_moves(int player);
    void generate_pawn_moves(int player);

    // evaluation subroutines:
    int evaluate_material();
    int evaluate_positions();
    int evaluate_pawns();

public:
    Board(bool debug = false);
    void initialize();
    // void move_piece(from, to);
    void display();
    void user_move();
    // std::vector<struct Move> generate_moves(int player);
    void generate_moves(int player);
    int evaluate();
};