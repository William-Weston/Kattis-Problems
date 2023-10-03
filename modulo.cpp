/**
 * @file    modulo.cpp
 * @author  your name (you@domain.com)
 * @brief   Modulo Problem from Kattis
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/modulo
 */

#include <cstdlib>
#include <iostream>
#include <set>

struct Solver
{
   auto solve() -> int;

   std::set<int> modulos = {};
};

auto operator>>( std::istream& in, Solver& solver ) -> std::istream&;

auto 
main() -> int
{
   auto solver = Solver();
   while ( std::cin >> solver )
   {
      std::cout << solver.solve() << '\n';
   }

   return EXIT_SUCCESS;
}

auto 
operator>>( std::istream& in, Solver& solver ) -> std::istream&
{
   solver.modulos.clear();
   
   int number;
   for ( auto i = 0; i < 10; ++i )
   {
      in >> number;
      if ( !in )
         return in;
      solver.modulos.insert( number % 42 );
   }

   return in;
}

auto 
Solver::solve() -> int
{
   return modulos.size();
}