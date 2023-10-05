/**
 * @file    main.cpp
 * @author  William Weston
 * @brief   Mate in One Move Solver
 * @version 0.1
 * @date 	2023-06-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Solver.h"

#include <cstdlib>
#include <iostream>

// ------------------------------------------------------------------------------------------------

auto main() -> int
{
   auto solver = Solver();

   while ( solver.load_board( std::cin ) )
   {
      auto solution = solver.solve( );
      std::cout << output_format( solution ) << "\n";
   }

   return EXIT_SUCCESS;
}

// ------------------------------------------------------------------------------------------------

