#include<vector>
#include<ctype.h> 
#include<cctype>
#include<clocale> 
#include<iostream>
#include"position.h"

std::vector<Move> Position::getMoves() {
    std::vector<Move> Moves; 
    all_pieces = Pieces[0].all | Pieces[1].all; 

    int nchecks = getKingMoves(Moves);

    if(nchecks < 2) {
        pinned = PieceMoves::findPinnedPieces(Pieces[color], Pieces[!color], all_pieces);

        getRookMoves(Moves); 
        getBishopMoves(Moves); 
        getQueenMoves(Moves);         
    }
    return Moves;
}


void Position::setFEN(std::string FEN) {
    //Zero out all the bitboards
    Pieces[WHITE].pawn = 0ULL; Pieces[WHITE].rook = 0ULL; Pieces[WHITE].knight = 0ULL;
    Pieces[WHITE].bishop = 0ULL; Pieces[WHITE].queen = 0ULL; Pieces[WHITE].king = 0ULL; 
    Pieces[BLACK].pawn = 0ULL; Pieces[BLACK].rook = 0ULL; Pieces[BLACK].knight = 0ULL;
    Pieces[BLACK].bishop = 0ULL; Pieces[BLACK].queen = 0ULL; Pieces[BLACK].king = 0ULL; 
    Pieces[WHITE].all = 0ULL; Pieces[BLACK].all = 0ULL;

    int it = 0; 
    int rank = 7; int file = 0; 
    while(rank >= 0) {
        if(isdigit(FEN.at(it))) {
            int skips = FEN.at(it) - '0';
            file += skips; 
        }
        else {
            char piece = FEN.at(it); 
            if(piece == 'P') {Pieces[WHITE].pawn += (1ULL << (8*rank + file));}
            else if(piece == 'R') {Pieces[WHITE].rook += (1ULL << (8*rank + file));}
            else if(piece == 'N') {Pieces[WHITE].knight += (1ULL << (8*rank + file));}
            else if(piece == 'B') {Pieces[WHITE].bishop += (1ULL << (8*rank + file));}
            else if(piece == 'Q') {Pieces[WHITE].queen += (1ULL << (8*rank + file));}
            else if(piece == 'K') {Pieces[WHITE].king += (1ULL << (8*rank + file));}
            else if(piece == 'p') {Pieces[BLACK].pawn += (1ULL << (8*rank + file));}
            else if(piece == 'r') {Pieces[BLACK].rook += (1ULL << (8*rank + file));}
            else if(piece == 'n') {Pieces[BLACK].knight += (1ULL << (8*rank + file));}
            else if(piece == 'b') {Pieces[BLACK].bishop += (1ULL << (8*rank + file));}
            else if(piece == 'q') {Pieces[BLACK].queen += (1ULL << (8*rank + file));}
            else {Pieces[BLACK].king += (1ULL << (8*rank + file));}
            ++file; 
        }
        if(file == 8) {
            rank--;
            it += 2; //skip over the backslash 
            file = 0;
        }
        else {
            ++it; 
        }
    }

    //Set the 'all' bitboards
    Pieces[WHITE].all = Pieces[WHITE].pawn | Pieces[WHITE].rook | Pieces[WHITE].knight | Pieces[WHITE].bishop | Pieces[WHITE].queen | Pieces[WHITE].king; 
    Pieces[BLACK].all = Pieces[BLACK].pawn | Pieces[BLACK].rook | Pieces[BLACK].knight | Pieces[BLACK].bishop | Pieces[BLACK].queen | Pieces[BLACK].king;  

    //Next handle the color
    if(FEN.at(it) == 'w') {color = WHITE;}
    else {color = BLACK;}
    it += 2; 

    //Castling 
    if(FEN.at(it) == '-') {
        castling[0] = 0; castling[1] = 0; castling[2] = 0; castling[3] = 0; 
        it += 2; 
    }
    else {
        while(std::isalpha(FEN.at(it))) {
            if(FEN.at(it) == 'K') {
                castling[0] = 1;
                ++it;
            }
            else if(FEN.at(it) == 'Q') {
                castling[1] = 1;
                ++it;
            }
            else if(FEN.at(it) == 'k') {
                castling[2] = 1;
                ++it;
            }
            else {
                castling[3] = 1;
                ++it; 
            }
        }
        ++it; 
    }

    //en passant target 
    if(FEN.at(it) == '-') {
        en_passant_target = 65; 
        it += 2; 
    }
    else {
        file = FEN.at(it) - 'a'; 
        ++it;
        rank = FEN.at(it) - '0';
        it += 2; 
    }
    
    //halfmove clock, for 50 move repetition
    halfmove_clock = FEN.at(it) - '0'; 
    it += 2; 

    //Fullmove clock
    fullmove_number = FEN.at(it) - '0'; 
}

//Print position to the terminal
//For debugging purposes 
void Position::printPosition() {
    char board[8][8];
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(Pieces[WHITE].pawn & (1ULL << (8*i+j))) {board[i][j] = 'P';}
            else if(Pieces[WHITE].rook & (1ULL << (8*i+j))) {board[i][j] = 'R';}
            else if(Pieces[WHITE].knight & (1ULL << (8*i+j))) {board[i][j] = 'N';}
            else if(Pieces[WHITE].bishop & (1ULL << (8*i+j))) {board[i][j] = 'B';}
            else if(Pieces[WHITE].queen & (1ULL << (8*i+j))) {board[i][j] = 'Q';}
            else if(Pieces[WHITE].king & (1ULL << (8*i+j))) {board[i][j] = 'K';}
            else if(Pieces[BLACK].pawn & (1ULL << (8*i+j))) {board[i][j] = 'p';}
            else if(Pieces[BLACK].rook & (1ULL << (8*i+j))) {board[i][j] = 'r';}
            else if(Pieces[BLACK].knight & (1ULL << (8*i+j))) {board[i][j] = 'n';}
            else if(Pieces[BLACK].bishop & (1ULL << (8*i+j))) {board[i][j] = 'b';}
            else if(Pieces[BLACK].queen & (1ULL << (8*i+j))) {board[i][j] = 'q';}
            else if(Pieces[BLACK].king & (1ULL << (8*i+j))) {board[i][j] = 'k';}
            else {board[i][j] = '*';}
        }
    }

    std::cout << "     A    B    C    D    E    F    G    H" << std::endl;
    std::cout << "   +----+----+----+----+----+----+----+----+" << std::endl;
    for(int i = 7; i >= 0; --i) {
        std::cout << i+1 << "  | ";
        for(int j = 0; j < 8; ++j) {
            std::cout << board[i][j] << "  | ";
        }
        std::cout << " Rank " << i+1 << std::endl; 
        std::cout << "   +----+----+----+----+----+----+----+----+" << std::endl;
    }
    std::cout << "     A    B    C    D    E    F    G    H - file(s)" << std::endl;

    //More game information
    if(color == WHITE) {
        std::cout << std::endl << "White to move" << std::endl << std::endl; 
    }
    else {
        std::cout << std::endl << "Black to move" << std::endl << std::endl;
    }

    std::cout << "Move: " << fullmove_number << std::endl << std::endl; 
    std::cout << "Half moves since capture or pawn move: " << halfmove_clock << std::endl << std::endl;
    castling[0] ? std::cout << "White kingside castling rights: YES" << std::endl : std::cout << "White kingside castling rights: NO" << std::endl;
    std::cout << std::endl;
    castling[1] ? std::cout << "White queenside castling rights: YES" << std::endl : std::cout << "White queenside castling rights: NO" << std::endl;
    std::cout << std::endl; 
    castling[2] ? std::cout << "Black kingside castling rights: YES" << std::endl : std::cout << "Black kingside castling rights: NO" << std::endl;
    std::cout << std::endl;
    castling[3] ? std::cout << "Black queenside castling rights: YES" << std::endl : std::cout << "Black queenside castling rights: NO" << std::endl;
    std::cout << std::endl;
    std::cout << "En passant target: " << int(en_passant_target) << std::endl << std::endl;
}


/* ****** Private member functions ******* */ 

void Position::getRookMoves(std::vector<Move> &Moves) {
    std::vector<char> rook_square = serialize(Pieces[color].rook);
    for(int i = 0; i < rook_square.size(); ++i) {
        uint64_t rook_attacks = PieceMoves::getRookPseudoLegal(rook_square[i], all_pieces); 
        rook_attacks &= ~Pieces[color].all; 
        rook_attacks &= piece_evasions; 

        //Now we need to find which ones are legal 
        if(pinned & (1ULL << rook_square[i])) {
            rook_attacks &= PieceMoves::getPinnedMoves(rook_square[i], Pieces[color].king, Pieces[!color], all_pieces); 
        }

        std::vector<char> destinations = serialize(rook_attacks); 
        Move move;
        move.origin = rook_square[i];
        move.aggressor = ROOK; 
        for(int j = 0; j < destinations.size(); ++j) {
            move.destination = destinations[j];
            Moves.push_back(move);
        }
    }
}

void Position::getBishopMoves(std::vector<Move> &Moves) {
    std::vector<char> bishop_square = serialize(Pieces[color].bishop);
    for(int i = 0; i < bishop_square.size(); ++i) {
        uint64_t bishop_attacks = PieceMoves::getBishopPseudoLegal(bishop_square[i], all_pieces);
        bishop_attacks &= ~Pieces[color].all;
        bishop_attacks &= piece_evasions; 

        //Now remove illegal moves
        if(pinned & (1ULL << bishop_square[i])) {
            bishop_attacks &= PieceMoves::getPinnedMoves(bishop_square[i], Pieces[color].king, Pieces[!color], all_pieces);
        }

        std::vector<char> destinations = serialize(bishop_attacks); 
        Move move;
        move.origin = bishop_square[i];
        move.aggressor = BISHOP; 
        for(int j = 0; j < destinations.size(); ++j) {
            move.destination = destinations[j]; 
            Moves.push_back(move); 
        }
    }
}

void Position::getQueenMoves(std::vector<Move> &Moves) {
    std::vector<char> queen_square = serialize(Pieces[color].queen);
    for(int i = 0; i < queen_square.size(); ++i) {
        uint64_t queen_attacks = PieceMoves::getQueenPseudoLegal(queen_square[i], all_pieces);
        queen_attacks &= ~Pieces[color].all;
        queen_attacks &= piece_evasions; 

        //Now remove illegal moves 
        if(pinned & (1ULL << queen_square[i])) {
            queen_attacks &= PieceMoves::getPinnedMoves(queen_square[i], Pieces[color].king, Pieces[!color], all_pieces);
        }

        std::vector<char> destinations = serialize(queen_attacks); 
        Move move;
        move.origin = queen_square[i];
        move.aggressor = QUEEN; 
        for(int j = 0; j < destinations.size(); ++j) {
            move.destination = destinations[j]; 
            Moves.push_back(move); 
        }
    }
}

int Position::getKingMoves(std::vector<Move> &Moves) {
    if(Pieces[color].king == 0ULL) {
        piece_evasions = ~0ULL;
        return 0; 
    }
    
    char king_loc = __builtin_ctzl(Pieces[color].king); 
    int nchecks = 0; 
    piece_evasions = 0ULL; 

    uint64_t king_attacks = PieceMoves::getKingPseudoLegal(king_loc); 
    king_attacks &= ~Pieces[color].all;

    //consider diagonal sliders
    uint64_t kingrays_diagonal = PieceMoves::getBishopPseudoLegal(king_loc, all_pieces);
    if((kingrays_diagonal & (Pieces[!color].bishop | Pieces[!color].queen)) != 0) {
        //King in check by sliding piece
        std::vector<char> attacking_pieces = serialize(kingrays_diagonal & (Pieces[!color].bishop | Pieces[!color].queen));
        for(int i = 0; i < attacking_pieces.size(); ++i) {
            piece_evasions |= kingrays_diagonal & PieceMoves::getBishopPseudoLegal(attacking_pieces[i], all_pieces); 
            //The Xray square is unsafe
            //Remove the king from the board
            king_attacks &= ~PieceMoves::getBishopPseudoLegal(attacking_pieces[i], all_pieces & ~(1ULL << king_loc));
            ++nchecks; 
        }
    }

    //Consider straight sliders 
    uint64_t kingrays_straight = PieceMoves::getRookPseudoLegal(king_loc, all_pieces);
    if((kingrays_straight & (Pieces[!color].rook | Pieces[!color].queen)) != 0) {
        //King in check by sliding piece
        std::vector<char> attacking_pieces = serialize(kingrays_straight & (Pieces[!color].rook | Pieces[!color].queen));
        for(int i = 0; i < attacking_pieces.size(); ++i) {
            piece_evasions |= kingrays_straight & PieceMoves::getRookPseudoLegal(attacking_pieces[i], all_pieces); 
            //The Xray square is unsafe
            //Remove the king from the board
            king_attacks &= ~PieceMoves::getRookPseudoLegal(attacking_pieces[i], all_pieces & ~(1ULL << king_loc));
            ++nchecks; 
        }
    }

    //Consider knights
    //TODO

    //Consider pawns
    //TODO 

    //Write down the possible king moves 
    std::vector<char> destinations = serialize(king_attacks); 
    Move move;
    move.origin = king_loc; 
    move.aggressor = KING;
    for(int i = 0; i < destinations.size(); ++i) {
        move.destination = destinations[i];
        Moves.push_back(move); 
    }

    if(nchecks != 0) {
        incheck = true; 
    }
    else {
        //Not in check
        incheck = false;
        piece_evasions = ~0ULL; 
    } 
    return nchecks; 
}