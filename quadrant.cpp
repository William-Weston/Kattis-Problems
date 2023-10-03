/**
 * @file    aaah.cpp
 * @author  William Weston
 * @brief   Quadrant Selection Problem from Kattis
 * @version 0.1
 * @date    2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/quadrant
 */


#include <cstdlib>   
#include <iostream>

auto quadrant( int x, int y ) -> int;

auto 
main() -> int
{
	int x, y;
	
	while ( std::cin >> x >> y )
	{
		std::cout << quadrant( x, y ) << '\n';
	}
   return EXIT_SUCCESS;
}

auto 
quadrant( int x, int y ) -> int
{
	return ( x < 0 )
		? ( y < 0 )	? 3 : 2
		: ( y < 0 ) ? 4 : 1;
}
