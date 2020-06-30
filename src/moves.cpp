#include<iostream>
#include"moves.h"

std::vector<Move> Moves::generateMoves(Position &pos) {
    std::vector<Move> moves;
    pos.all = pos.Pieces[pos.color].all | pos.Pieces[!pos.color].all; 
    pos.kingsq = _tzcnt_u64(pos.Pieces[pos.color].king);

    pos.pinned = getPinned(pos);

    if(pos.isinCheck()) {
        CheckType checkdata = PieceMoves::getCheckData(pos.kingsq, pos.color, pos.Pieces[pos.color], pos.Pieces[!pos.color]);
        pos.safety_map = checkdata.safety_map; 
        
        kingMoves(pos, moves);
        //Generate blocking evasions
        if(checkdata.nchecks < 2) {
            queenMoves(pos, moves);
            bishopMoves(pos, moves);      
            knightMoves(pos, moves);    
            rookMoves(pos, moves);    
            pawnMoves(pos, moves);
        }
    }
    else {
        pos.safety_map = ~0ULL;

        kingMoves(pos, moves); 
        queenMoves(pos, moves);
        bishopMoves(pos, moves);
        knightMoves(pos, moves); 
        rookMoves(pos, moves); 
        pawnMoves(pos, moves);
    }

    return moves; 
}

GameState Moves::makeMove(Position &pos, Move &move) {
    //find which piece is to be moved 
    //place on desired square 
    uint64_t dest = 1ULL << move.destination;  
    uint64_t orig = ~(1ULL << move.origin);

    switch(move.aggressor) {
        case PAWN: 
            pos.Pieces[pos.color].pawn &= orig;
            pos.Pieces[pos.color].pawn |= dest;
            break; 
        case ROOK:
            pos.Pieces[pos.color].rook &= orig;
            pos.Pieces[pos.color].rook |= dest; 
            break;
        case KNIGHT:
            pos.Pieces[pos.color].knight &= orig;
            pos.Pieces[pos.color].knight |= dest; 
            break;
        case BISHOP:
            pos.Pieces[pos.color].bishop &= orig;
            pos.Pieces[pos.color].bishop |= dest; 
            break;
        case QUEEN:
            pos.Pieces[pos.color].queen &= orig;
            pos.Pieces[pos.color].queen |= dest; 
            break;
        case KING:
            pos.Pieces[pos.color].king &= orig;
            pos.Pieces[pos.color].king |= dest; 
            break; 
    }
    pos.Pieces[pos.color].all &= orig; pos.Pieces[pos.color].all |= dest;

    //Get victim
    if(dest & pos.Pieces[!pos.color].all) { 
        pos.Pieces[!pos.color].all &= ~dest; 
        if((dest & pos.Pieces[!pos.color].pawn) != 0) {
            move.victim = PAWN; 
            pos.Pieces[!pos.color].pawn &= ~dest; 
        }
        else if((dest & pos.Pieces[!pos.color].rook) != 0) {
            move.victim = ROOK; 
            pos.Pieces[!pos.color].rook &= ~dest; 
        }
        else if((dest & pos.Pieces[!pos.color].knight) != 0) {
            move.victim = KNIGHT; 
            pos.Pieces[!pos.color].knight &= ~dest; 
        }
        else if((dest & pos.Pieces[!pos.color].bishop) != 0) {
            move.victim = BISHOP; 
            pos.Pieces[!pos.color].bishop &= ~dest; 
        }
        else {
            move.victim = QUEEN; 
            pos.Pieces[!pos.color].queen &= ~dest; 
        }
    }
    else {
        move.victim = QUIET; 
    }

    //*** special moves ***// 
    if(move.aggressor == PAWN && move.promotion) {
        //a promotion occurred
        //remove pawn from the board
        pos.Pieces[pos.color].pawn &= ~dest;
        switch(move.promotype) {
            case ROOK:
                pos.Pieces[pos.color].rook |= dest;
                break;
            case KNIGHT:
                pos.Pieces[pos.color].knight |= dest;
                break;
            case BISHOP:
                pos.Pieces[pos.color].bishop |= dest;
                break;
            case QUEEN:
                pos.Pieces[pos.color].queen |= dest;
                break;
        }
    }
    else if(move.aggressor == PAWN && move.enpassant) {
        move.victim = PAWN; 
        int victimsq = pos.color ? move.destination + 8 : move.destination - 8; 
        //remove victim from the board
        pos.Pieces[!pos.color].pawn &= ~(1ULL << victimsq);
        pos.Pieces[!pos.color].all &= ~(1ULL << victimsq); 
    }

    //*** update game metadata ***// 
    GameState metadata;
    metadata.eptarget = pos.en_passant_target;
    if(pos.color == BLACK) {++pos.fullmove_number;} //update move number
    pos.color = !pos.color; //switch color
    if(move.victim != QUIET || move.aggressor == PAWN) {
        pos.halfmove_clock = 0; 
    } //for 50 move draw
    else {
        ++pos.halfmove_clock; 
    }

    if(move.aggressor == PAWN && abs(move.destination - move.origin) > 10) {
        pos.en_passant_target = pos.color ? move.destination - 8 : move.destination + 8; 
    }
    else {
        pos.en_passant_target = 65; 
    }

    return metadata; 
}

void Moves::unmakeMove(Position &pos, Move move, GameState metadata) {
    //Update game metadata
    if(pos.color == WHITE) {--pos.fullmove_number;}
    pos.color = !pos.color;
    if(move.victim == QUIET && move.aggressor != PAWN) {
        --pos.halfmove_clock;
    }
    pos.en_passant_target = metadata.eptarget; 

    uint64_t orig = 1ULL << move.origin; 
    uint64_t dest = 1ULL << move.destination; 
    //Put victim back on board 
    switch(move.victim) {
        case QUIET: break;
        case PAWN:
            pos.Pieces[!pos.color].pawn |= dest;
            pos.Pieces[!pos.color].all |= dest; 
            break;
        case ROOK: 
            pos.Pieces[!pos.color].rook |= dest; 
            pos.Pieces[!pos.color].all |= dest;
            break;
        case KNIGHT: 
            pos.Pieces[!pos.color].knight |= dest;
            pos.Pieces[!pos.color].all |= dest; 
            break;
        case BISHOP:
            pos.Pieces[!pos.color].bishop |= dest;
            pos.Pieces[!pos.color].all |= dest;
            break;
        case QUEEN:
            pos.Pieces[!pos.color].queen |= dest;
            pos.Pieces[!pos.color].all |= dest;
            break;
    }

    dest = ~dest; 
    //Put aggressor back in correct spot 
    switch(move.aggressor) {
        case PAWN: 
            pos.Pieces[pos.color].pawn |= orig;
            pos.Pieces[pos.color].pawn &= dest; 
            break;
        case ROOK: 
            pos.Pieces[pos.color].rook |= orig;
            pos.Pieces[pos.color].rook &= dest; 
            break;
        case KNIGHT: 
            pos.Pieces[pos.color].knight |= orig;
            pos.Pieces[pos.color].knight &= dest;
            break;
        case BISHOP: 
            pos.Pieces[pos.color].bishop |= orig;
            pos.Pieces[pos.color].bishop &= dest; 
            break;
        case QUEEN: 
            pos.Pieces[pos.color].queen |= orig;
            pos.Pieces[pos.color].queen &= dest;         
            break;
        case KING: 
            pos.Pieces[pos.color].king |= orig; 
            pos.Pieces[pos.color].king &= dest; 
            break;
    }
    pos.Pieces[pos.color].all &= dest; pos.Pieces[pos.color].all |= orig;

    //***undo promotion***//
    if(move.aggressor == PAWN && move.promotion) {
        //get rid of destination square 
        switch(move.promotype) {
            case ROOK:
                pos.Pieces[pos.color].rook &= dest;
                break;
            case KNIGHT:
                pos.Pieces[pos.color].knight &= dest;
                break;
            case BISHOP:
                pos.Pieces[pos.color].bishop &= dest;
                break;
            case QUEEN:
                pos.Pieces[pos.color].queen &= dest;
                break;
        }       
    }
    //***undo enpassant***//
    if(move.aggressor == PAWN && move.enpassant) {
        //victim is in the wrong spot, lets put it back
        pos.Pieces[!pos.color].pawn &= dest;
        pos.Pieces[!pos.color].all &= dest;

        int realsq = pos.color ? move.destination + 8 : move.destination - 8; 
        
        pos.Pieces[!pos.color].pawn |= (1ULL << realsq);
        pos.Pieces[!pos.color].all |= (1ULL << realsq); 
    }
}

void kingMoves(Position &pos, std::vector<Move> &moves) {
    uint64_t king_attacks = getKingPseudoLegal(pos.kingsq);
    king_attacks &= ~pos.Pieces[pos.color].all;
    Move move;
    move.origin = pos.kingsq;
    move.aggressor = KING;
    while(king_attacks) {
        move.destination = pop_lsb(king_attacks);
        moves.push_back(move); 
    }
}

void queenMoves(Position &pos, std::vector<Move> &moves) {
    uint64_t queen_loc = pos.Pieces[pos.color].queen;
    Move move;
    move.aggressor = QUEEN;
    while(queen_loc) {
        move.origin = pop_lsb(queen_loc);
        uint64_t bishop_attacks = getBishopPseudoLegal(move.origin, pos.all);
        uint64_t rook_attacks = getRookPseudoLegal(move.origin, pos.all);
        rook_attacks &= ~pos.Pieces[pos.color].all;
        bishop_attacks &= ~pos.Pieces[pos.color].all;
        if((1ULL << move.origin) & pos.pinned) {
            //queen is pinned
            //a queen can always move in a pin 
            // if one direction is possible the other is impossible 
            uint64_t newbish = getBishopPseudoLegal(pos.kingsq, pos.all & ~(1ULL << move.origin));
            if(newbish & (1ULL << move.origin)) {
                bishop_attacks &= newbish;
                rook_attacks = 0ULL;               
            }
            else {
                rook_attacks &= getRookPseudoLegal(pos.kingsq, pos.all & ~(1ULL << move.origin)); 
                bishop_attacks = 0ULL;
            }        
        } 
        uint64_t queen_attacks = rook_attacks | bishop_attacks; 
        queen_attacks &= pos.safety_map; 
        while(queen_attacks) {
            move.destination = pop_lsb(queen_attacks);
            moves.push_back(move); 
        }
    }
}

void bishopMoves(Position &pos, std::vector<Move> &moves) {
    uint64_t bishop_loc = pos.Pieces[pos.color].bishop; 
    Move move;
    move.aggressor = BISHOP;
    while(bishop_loc) {
        move.origin = pop_lsb(bishop_loc);
        
        uint64_t bishop_attacks = getBishopPseudoLegal(move.origin, pos.all);
        bishop_attacks &= ~pos.Pieces[pos.color].all;

        if((1ULL << move.origin) & pos.pinned) {
            //bishop is pinned
            //bishop can only move diagonally along a pin
            uint64_t newbish = getBishopPseudoLegal(pos.kingsq, pos.all & ~(1ULL << move.origin));
            if(newbish & (1ULL << move.origin)) {
                bishop_attacks &= newbish;
            }
            else {
                bishop_attacks = 0ULL;
            }
        }

        bishop_attacks &= pos.safety_map; 
        while(bishop_attacks) {
            move.destination = pop_lsb(bishop_attacks);
            moves.push_back(move); 
        }
    }
}

void knightMoves(Position &pos, std::vector<Move> &moves) {
    uint64_t knight_loc = pos.Pieces[pos.color].knight;
    Move move;
    move.aggressor = KNIGHT;
    while(knight_loc) {
        move.origin = pop_lsb(knight_loc);

        uint64_t knight_attacks = getKnightPseudoLegal(move.origin); 
        knight_attacks &= ~pos.Pieces[pos.color].all;

        if(1ULL << (move.origin) & pos.pinned) {
            //Knights can never move along a pin line
            knight_attacks = 0ULL;
        }
        
        knight_attacks &= pos.safety_map; 

        while(knight_attacks) {
            move.destination = pop_lsb(knight_attacks); 
            moves.push_back(move); 
        }
    }
}

void rookMoves(Position &pos, std::vector<Move> &moves) {
    uint64_t rook_loc = pos.Pieces[pos.color].rook;
    Move move;
    move.aggressor = ROOK; 
    while(rook_loc) {
        move.origin = pop_lsb(rook_loc);
        uint64_t rook_attacks = getRookPseudoLegal(move.origin, pos.all);
        rook_attacks &= ~pos.Pieces[pos.color].all;

        if((1ULL << move.origin) & pos.pinned) {
            //rook is pinned 
            uint64_t newrook = getRookPseudoLegal(pos.kingsq, pos.all & ~(1ULL << move.origin));
            if(newrook & (1ULL << move.origin)) {
                rook_attacks &= newrook;
            }
            else {
                rook_attacks = 0ULL;
            }
            rook_attacks &= getRookPseudoLegal(pos.kingsq, pos.all & ~(1ULL << move.origin));
        }

        rook_attacks &= pos.safety_map; 
        while(rook_attacks) {
            move.destination = pop_lsb(rook_attacks);
            moves.push_back(move); 
        }
    }
}

void pawnMoves(Position &pos, std::vector<Move> &moves) {
    if(pos.Pieces[pos.color].pawn == 0ULL) {return;}

    Move move;
    move.aggressor = PAWN; 
    move.promotion = false; 
    move.enpassant = false; 

    uint64_t emptysquares = ~pos.all; 
    bool side = pos.color; 
    //*** Get single push ***//
    uint64_t singlepush = getPawnSinglePush(pos.Pieces[side].pawn, emptysquares, side); 

    while(singlepush) {
        move.origin = pop_lsb(singlepush);
        side ? move.destination = move.origin - 8 : move.destination = move.origin + 8;

        if(((1ULL << move.destination) & pos.safety_map) == 0) {
            continue; 
        }

        //check for pin
        if((1ULL << move.origin) & pos.pinned) {
            if(getRookPseudoLegal(pos.kingsq, pos.all) & (1ULL << move.origin)) {
                if((getRookPseudoLegal(move.destination, pos.all) & (1ULL << pos.kingsq)) == 0) {
                    continue; 
                }
            }
            else {
                pos.printPosition();
                std::cout << "SINGLE PUSH" << std::endl;
                continue; 
            }
        }

        //check for promotion 
        if(!side && move.destination >= 56) {
            makePromotion(move, moves);
        }
        else if(move.destination <= 7) {
            makePromotion(move, moves); 
        }
        else {
            moves.push_back(move); 
        } 
    }

    //*** get double pushes***//
    uint64_t doublepush = getPawnDoublePush(pos.Pieces[side].pawn, emptysquares, side);

    while(doublepush) {
        move.origin = pop_lsb(doublepush);
        side ? move.destination = move.origin - 16 : move.destination = move.origin + 16; 

        if(((1ULL << move.destination) & pos.safety_map) == 0) {
            continue; 
        }

        if((1ULL << move.origin) & pos.pinned) {
            if(getRookPseudoLegal(pos.kingsq, pos.all) & (1ULL << move.origin)) {
                std::cout << "DBL if" << std::endl;
                if((getRookPseudoLegal(move.destination, pos.all) & (1ULL << pos.kingsq)) == 0) {
                    std::cout << "Double pin reject" << std::endl;
                    continue; 
                }
            }
            else {
                pos.printPosition();
                std::cout << "DBL PUSH" << std::endl;
            }
        }

        //no promotion possible with double push
        moves.push_back(move); 
    }

    /*** get captures ***/
    uint64_t pawns = pos.Pieces[side].pawn;
    while(pawns) {
        move.origin = pop_lsb(pawns);

        uint64_t pawn_attacks = getPawnCapturesPseudoLegal(move.origin, side, pos.Pieces[!side].all);
        pawn_attacks &= pos.safety_map; 

        //***check for en passant capture ***/
        if(pos.en_passant_target != 65) {
            enPassantCapture(pos.en_passant_target, pos.Pieces[side].pawn, move, moves, side);  
        }

        while(pawn_attacks) {
            move.destination = pop_lsb(pawn_attacks);
            //pins 
            if((1ULL << move.origin) & pos.pinned) {
                if(getBishopPseudoLegal(pos.kingsq, pos.all) & (1ULL << move.origin)) {
                    std::cout << "Capture if" << std::endl;
                    if((getBishopPseudoLegal(move.destination, pos.all) & (1ULL << pos.kingsq)) == 0) {
                        std::cout << "Capture pin reject" << std::endl;
                        continue; 
                    }
                }
                else {
                    pos.printPosition();
                    std::cout << "CAPTURE" << std::endl;
                }
            }

            if(!side && move.destination >= 56) {
                makePromotion(move, moves);

            }
            else if(move.destination <= 7) {
                makePromotion(move, moves); 

            }
            else {
                moves.push_back(move); 
            } 
        }
    }
}

//OPTIMIZE HERE - OBSTRUCTED MIGHT BE SLOW 
uint64_t getPinned(Position &pos) {
    uint64_t pinned = 0ULL; 
    uint64_t pinner = xrayRookAttacks(pos.kingsq, pos.all, pos.Pieces[pos.color].all)
                    & (pos.Pieces[!pos.color].rook | pos.Pieces[!pos.color].queen);
    while(pinner) {
        int sq = pop_lsb(pinner);
        uint64_t possible_pinned = getRookPseudoLegal(pos.kingsq, pos.all); 
        possible_pinned &= getRookPseudoLegal(sq, pos.all);
        possible_pinned &= pos.Pieces[pos.color].all;
        if(_popcnt64(possible_pinned) == 1) {
            pinned |= possible_pinned; 
        }
    }

    pinner = xrayBishopAttacks(pos.kingsq, pos.all, pos.Pieces[pos.color].all)
            & (pos.Pieces[!pos.color].bishop | pos.Pieces[!pos.color].queen); 
    while(pinner) {
        int sq = pop_lsb(pinner);
        uint64_t possible_pinned = getBishopPseudoLegal(pos.kingsq, pos.all); 
        possible_pinned &= getBishopPseudoLegal(sq, pos.all);
        possible_pinned &= pos.Pieces[pos.color].all;
        if(_popcnt64(possible_pinned) == 1) {
            pinned |= possible_pinned; 
        }
    }
    return pinned; 
}

void makePromotion(Move currmove, std::vector<Move> &moves) {
    currmove.promotion = true; 
    currmove.promotype = ROOK;
    moves.push_back(currmove);
    currmove.promotype = KNIGHT;
    moves.push_back(currmove);
    currmove.promotype = BISHOP;
    moves.push_back(currmove);
    currmove.promotype = QUEEN;
    moves.push_back(currmove);
}

void enPassantCapture(int targetsq, uint64_t mypawns, Move currmove, std::vector<Move> &moves, bool side) {
    currmove.enpassant = true; 
    uint64_t ep_pawns = getPawnCapturesPseudoLegal(targetsq, !side, mypawns);
    while(ep_pawns) {
        //max size is two 
        currmove.origin = pop_lsb(ep_pawns);
        currmove.destination = targetsq; 
        moves.push_back(currmove); 
    }
}