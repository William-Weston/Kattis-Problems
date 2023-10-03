/**
 * @file    compoundwords.cpp
 * @author  William Weston
 * @brief   Compound Words
 * @version 0.1
 * @date    2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/compoundwords
 */


#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

auto load_word_list()                                           -> std::vector<std::string>;
auto generate_compounds( std::vector<std::string> const& data ) -> std::set<std::string>;
auto print( std::set<std::string> const& list )                 -> void;


auto main() -> int
{
   auto const word_list      = load_word_list();
   auto const compound_words = generate_compounds( word_list );
   print( compound_words );

   return EXIT_SUCCESS;
}

auto load_word_list() -> std::vector<std::string>
{
   auto word_list = std::vector<std::string>();

   for ( auto word = std::string(); std::cin >> word; )
   {
      word_list.push_back( std::move( word ) );
   }

   return word_list;
}

auto generate_compounds( std::vector<std::string> const& data ) -> std::set<std::string>
{
   auto compound_words = std::set<std::string>();
   auto const end      = data.end();

   for ( auto begin = data.begin(); begin != end; ++begin )
   {
      for ( auto first = data.begin(); first != end; ++first )
      {
         if ( begin == first )
            continue;
         
         auto tmp = *begin + *first;
         compound_words.insert( std::move( tmp ) );
      }
   }
   return compound_words;
}

auto print( std::set<std::string> const& list ) -> void
{
   for ( auto const& word : list )
      std::cout << word << '\n';
}