/**
 * @file    aaah.cpp
 * @author  William Weston
 * @brief   Spavanac Problem from Kattis
 * @version 0.1
 * @date    2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/spavanac
 */

#include <cmath>
#include <cstdlib>   
#include <iostream>
#include <string>

struct Time
{
	int hours   = 0;
	int minutes = 0;
};
auto operator<<( std::ostream& out, Time const& time ) -> std::ostream&;

auto forty_five_minutes_earlier( int hours, int minutes ) -> Time;

auto 
main() -> int
{
	int hours;
	int minutes;

	while( std::cin >> hours >> minutes )
		std::cout << forty_five_minutes_earlier( hours, minutes ) << '\n';
	
   return EXIT_SUCCESS;
}


auto 
forty_five_minutes_earlier( int hours, int minutes  ) -> Time
{
	if ( minutes >= 45 )
		return { hours, minutes - 45 };

	auto const new_minutes = 60 - std::abs( minutes - 45 );

	return ( hours > 0 )
		? Time{ --hours, new_minutes }
		: Time{ 23, new_minutes }; 
}

auto 
operator<<( std::ostream& out, Time const& time ) -> std::ostream&
{
	using namespace std::literals;

	out << time.hours 
		 << ' ' // << ( ( time.minutes < 10 ) ? " 0"s  : " "s )
		 << time.minutes;
	
	return out;
}