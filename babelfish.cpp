/**
 * @file    babelfish.cpp
 * @author  William Weston
 * @brief   Babelfish Problem From Kattis
 * @version 0.1
 * @date    2023-07-04
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/babelfish
 */


#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Translator final
{
public:
   auto load_dictionary( std::istream& in )       -> void;
   auto translate( std::istream&, std::ostream& ) -> void;

private:
   std::unordered_map<std::string, std::string> dictionary_ = {};
};


auto main() -> int
{
   auto translator = Translator();

   translator.load_dictionary( std::cin );
   translator.translate( std::cin, std::cout );

   return EXIT_SUCCESS;
}

auto Translator::load_dictionary( std::istream& in ) -> void
{
   for ( auto line = std::string(); std::getline( in, line ) ; )
   {
      if ( line == "" )
         break;
      
      auto stream       = std::istringstream( line );
      auto english_word = std::string();
      auto foreign_word = std::string();

      stream >> english_word >> foreign_word;

      dictionary_.emplace( foreign_word, english_word );
   }
}

auto Translator::translate( std::istream& in, std::ostream& out ) -> void
{
   for ( auto foreign_word = std::string(); in >> foreign_word ; )
   {
      if ( auto result = dictionary_.find( foreign_word ); result != dictionary_.end() )
      {
         out << (*result).second << '\n';
      }
      else
      {
         out << "eh\n";
      }
   }
}