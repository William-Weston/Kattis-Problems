/**
 * @file    mate_in_one_move.t.cpp
 * @author  William Weston
 * @brief
 * @version 0.1
 * @date    2023-06-12
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "Solver.h"


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <utility>
#include <vector>




TEST( Tests_MateInOneMove, generate_moves_for_cell )
{
   
   auto board = Board{ "........",
                       "........",
                       "........",
                       "........",
                       "........",
                       "........",
                       "....P...",
                       "........"
                     };


   auto results = generate_moves( Cell{ 6, 4 }, board );


   EXPECT_THAT( results, testing::UnorderedElementsAre( Move{ { 6, 4 }, { 5, 4 } },
                                                      Move{ { 6, 4 }, { 4, 4 } }
                                                    ) );                                                        
}


TEST( Tests_MateInOneMove, Solver_Sample_Input1 )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "rn...q.b\n"
                              "pb..pPkp\n"
                              ".p......\n"
                              "..ppN..p\n"
                              "...P....\n"
                              "..NB....\n"
                              "PPPQ.PP.\n"
                              "..KR....\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "d2g5"s );
}

TEST( Tests_MateInOneMove, Solver_Sample_Input2 )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "..kr...r\n"
                              "p..n..pp\n"
                              ".p.Bnp..\n"
                              "....p...\n"
                              "........\n"
                              "........\n"
                              "PPP..PPP\n"
                              "...RKB.R\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "f1a6"s );
}

TEST( Tests_MateInOneMove, Solver_Sample_Input3 )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "rnbq..kr\n"
                              ".p.n..pp\n"
                              "p...p...\n"
                              "...pP...\n"
                              "......Q.\n"
                              "B.PB....\n"
                              "P.P..PPP\n"
                              "R....RK.\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "g4e6"s );
}

TEST( Tests_MateInOneMove, Solver_Sample_Input4 )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "r.bqkb.r\n"
                              "pp.npppp\n"
                              ".....n..\n"
                              ".....N..\n"
                              "...PN...\n"
                              "........\n"
                              "PPPBQPPP\n"
                              "R...KB.R\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "e4d6"s );
}

TEST( Tests_MateInOneMove, Solver_Sample_Input5 )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              ".....p..\n"
                              "...p....\n"
                              "b...Q.K.\n"
                              "k.nq....\n"
                              "p..NR..r\n"
                              "..P..P..\n"
                              "R..Bn...\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "e5e8"s );
}

TEST( Tests_MateInOneMove, Solver_Sample_Input6 )
{
   using namespace std::literals;

   auto board = std::string{ 
                              ".rbq..r.\n"
                              "p.Pk.K.b\n"
                              ".P.bnp..\n"
                              "..n....p\n"
                              "........\n"
                              "........\n"
                              "....p...\n"
                              "...R....\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "c7b8"s );
}

// https://korpalskichess.com/?page_id=2013#1
TEST( Tests_MateInOneMove, RookAndKing )
{
   using namespace std::literals;

   auto board = std::string{ 
                              ".k......\n"
                              "......R.\n"
                              ".K......\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "g7g8"s );
}

// https://korpalskichess.com/?page_id=2025#1
TEST( Tests_MateInOneMove, TwoRooksAndKing )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              "........\n"
                              "........\n"
                              "...K....\n"
                              ".......k\n"
                              "........\n"
                              "......R.\n"
                              ".....R..\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "f1h1"s );
}

// https://korpalskichess.com/?page_id=6954#1
TEST( Tests_MateInOneMove, KingQueenAndPawns )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              "........\n"
                              "........\n"
                              ".p.Q....\n"
                              "k...K...\n"
                              "..P.....\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "d5a2"s );
}

// https://korpalskichess.com/?page_id=3316#1
TEST( Tests_MateInOneMove, KingAndPawns )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "....k...\n"
                              "....P...\n"
                              "....KP..\n"
                              ".......p\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "f6f7"s );
}

// https://korpalskichess.com/?page_id=7004#1
TEST( Tests_MateInOneMove, KingAndFourBishops )
{
   using namespace std::literals;

   auto board = std::string{ 
                              ".k......\n"
                              ".....K..\n"
                              ".....B..\n"
                              "..BB.B..\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "f6e5"s );
}


// https://korpalskichess.com/?page_id=7006#1
TEST( Tests_MateInOneMove, KingAndTwoKnights )
{
   using namespace std::literals;

   auto board = std::string{ 
                              ".......k\n"
                              "........\n"
                              ".....NKN\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "....q...\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "h6f7"s );
}

// https://korpalskichess.com/?page_id=7010#1
TEST( Tests_MateInOneMove, KingBishopKnight )
{
   using namespace std::literals;

   auto board = std::string{ 
                              ".......k\n"
                              "........\n"
                              "......KN\n"
                              "..B.....\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "c5d4"s );
}

// https://korpalskichess.com/?page_id=3674#1
TEST( Tests_MateInOneMove, KingQueenRook )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              "........\n"
                              "...K...k\n"
                              "......R.\n"
                              ".....Q..\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "f4h4"s );
}

// https://korpalskichess.com/?page_id=6863#1
TEST( Tests_MateInOneMove, KingTwoQueens )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "......Q.\n"
                              "........\n"
                              "...Q....\n"
                              "........\n"
                              "kp......\n"
                              "........\n"
                              "..K.....\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "d6a6"s );
}


// https://korpalskichess.com/?page_id=3056#1
TEST( Tests_MateInOneMove, KingRookBishop )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              "k.B.....\n"
                              "..K.....\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              ".......R\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "h2a2"s );
}


// https://korpalskichess.com/?page_id=3041#1
TEST( Tests_MateInOneMove, KingQueenBishop )
{
   using namespace std::literals;

   auto board = std::string{ 
                              ".Q......\n"
                              "..K.....\n"
                              "........\n"
                              "........\n"
                              "k.......\n"
                              "........\n"
                              "........\n"
                              "....B...\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "b8b4"s );
}

// https://korpalskichess.com/?page_id=3062#1
TEST( Tests_MateInOneMove, KingQueenKnight )
{
   // Failure of this test indicates wrong move was chosen because stalemate was not taken into account e4c3
   // Stalemate is a situation in chess where the player whose turn it is to move is not in check and has no legal move. 
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              ".K......\n"
                              "........\n"
                              "........\n"
                              "....N...\n"
                              "......Q.\n"
                              "........\n"
                              ".....k..\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "g3f2"s );
}



// https://korpalskichess.com/?page_id=3049#1
TEST( Tests_MateInOneMove, KingRookKnight )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "......k.\n"
                              ".....R..\n"
                              "....N.K.\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "f7f8"s );  // wrong solution f7h7
}


TEST( Tests_MateInOneMove, NoSolution )
{
   using namespace std::literals;

   auto board = std::string{ 
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                              "........\n"
                           };

   auto input_stream = std::istringstream( board );
   auto solver       = Solver();

   solver.load_board( input_stream );

   auto move     = solver.solve();
   auto solution = output_format( move );

   EXPECT_EQ( solution, "no solution"s );
}
