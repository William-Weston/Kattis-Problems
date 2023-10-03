/**
 * @file    aaah.cpp
 * @author  William Weston
 * @brief   Take Two Stones Problem from Kattis
 * @version 0.1
 * @date    2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/twostones
 */


#include <cstdlib>   
#include <iostream>
#include <string>


auto 
main() -> int
{
	using namespace std::literals;

	int N;
	
	while ( std::cin >> N )
	{
		std::cout << ( ( N % 2 == 0 ) ? "Bob"s : "Alice"s ) << '\n';
	}

   return EXIT_SUCCESS;
}
