/**
 * @file    bard.cpp
 * @author  William Weston
 * @brief   Bard Problem From Kattis
 * @version 0.1
 * @date    2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/bard
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>        // insert_iterator
#include <map>
#include <numeric>         // iota
#include <set>
#include <vector>

constexpr auto BARD = 1;

using song_map = std::map<int, std::set<int>>;

auto create_song_map( int number_of_villagers ) -> song_map;

auto exchange_songs( song_map& songs_known, std::vector<int> const& present ) -> void;
auto add_new_song( song_map& songs_known, std::vector<int> const& present, int song_number ) -> void;
auto know_all_songs( song_map const& songs_known, int total_songs ) -> std::vector<int>;
auto is_present( std::vector<int> const& villagers, int villager ) -> bool;
auto print( std::vector<int> const& villagers ) -> void;

auto main() -> int
{
   auto const number_of_villagers = [] { int tmp; std::cin >> tmp; return tmp; }();
   auto const number_of_evenings  = [] { int tmp; std::cin >> tmp; return tmp; }();

   auto songs_known = create_song_map( number_of_villagers );

   for ( auto evening = 0; evening < number_of_evenings; ++evening )
   {
      auto const number_present = [] { int tmp; std::cin >> tmp; return tmp; }();

      auto present = std::vector<int>();

      for ( auto count = 0; count < number_present; ++count )
      {
         int villager;
         std::cin >> villager;
         present.push_back( villager );
      }
      std::sort( present.begin(), present.end() );

      if ( is_present( present, BARD ) )
      {
         add_new_song( songs_known, present, evening );
      }
      else
      {
         exchange_songs( songs_known, present );
      }
   }

   auto const total_songs = songs_known[1].size();
   auto knows_all = know_all_songs( songs_known, total_songs );

   print( knows_all );
   
   return EXIT_SUCCESS;
}

auto 
create_song_map( int const number_of_villagers ) -> song_map
{
   auto result = song_map();
   for ( auto count = 1; count < number_of_villagers + 1; ++count )
   {
      result[count];
   }
   return result;
}

auto 
exchange_songs( song_map& songs_known, std::vector<int> const& present ) -> void
{
   auto song_book = std::set<int>();

   // get list of all songs known between those present
   for ( auto const villager : present )
   {
      auto const iter = songs_known.find( villager );
      if ( iter != songs_known.end() )
      {
         auto const& song_set = iter->second;
         song_book.insert( song_set.begin(), song_set.end() );
      }
   }

   // add the song book to each villager present's set of songs
   for ( auto const villager : present )
   {
      songs_known[villager].insert( song_book.begin(), song_book.end() );
   }
}

auto 
add_new_song( song_map& songs_known, std::vector<int> const& present, int const song_number ) -> void
{
   for ( auto villager : present )
   {
      songs_known[villager].insert( song_number );
   }
}

auto 
know_all_songs( song_map const& songs_known, int const total_songs ) -> std::vector<int>
{
   auto result = std::vector<int>();
   
   for ( auto const& [villager, songs] : songs_known )
   {
      if ( songs.size() == total_songs )
         result.push_back( villager );
   }

   return result;
}
auto 
is_present( std::vector<int> const& villagers, int const villager ) -> bool
{
   return std::binary_search( villagers.begin(), villagers.end(), villager );
}

auto
print( std::vector<int> const& villagers ) -> void
{
   for ( auto const elem : villagers )
   {
      std::cout << elem << '\n';
   }
}

