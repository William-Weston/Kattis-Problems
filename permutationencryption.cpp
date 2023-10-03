/**
 * @file    permutationencryption.cpp
 * @author  William Weston
 * @brief   Permutation Encryption Problem From Kattis
 * @version 0.1
 * @date    2023-08-14
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source: https://open.kattis.com/problems/permutationencryption
 */


#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>


auto chunkify( std::string_view msg, int chunk_size )                   -> std::vector<std::string_view>;
auto create_keys( std::string const& key )                              -> std::vector<int>;
auto encrypt( std::vector<std::string_view> msg, std::vector<int> key ) -> std::string;
auto catenate( std::vector<std::string> const& blocks )                 -> std::string;


auto main() -> int
{
   while ( std::cin.peek() != '0'  )
   {
      auto line = std::string(); 
      std::getline( std::cin, line ); 

      auto iss              = std::istringstream( line );
      auto const key_length = [] ( std::istream& in ) { int tmp; in >> tmp; return tmp; }( iss );
      auto const key        = [] ( std::istream& in ) { auto tmp = std::string(); std::getline( in >> std::ws, tmp ); return tmp; }( iss );
      auto const message    = [] ( int key_length ) 
                              { 
                                 auto tmp = std::string(); 
                                 std::getline( std::cin, tmp ); 
                                 auto const msg_length = static_cast<int>( tmp.length() );
                                 auto const mod        = msg_length % key_length;
                                 auto const extra      = mod ? ( key_length - mod ): 0;
                                 auto const spaces     = std::string( extra, ' ' );
                                 return tmp + spaces; 
                              }( key_length );

      auto const chunks = chunkify( message, key_length );
      auto const keys   = create_keys( key );
      auto const result = encrypt( chunks, keys );

      std::cout << '\'' << result << "'\n";
   }

   return EXIT_SUCCESS;
}

auto chunkify( std::string_view msg, int chunk_size ) -> std::vector<std::string_view>
{
   auto ret = std::vector<std::string_view>();
   auto const end = msg.end();

   for ( auto it = msg.cbegin(); it != end; std::advance( it, chunk_size ) )
   {
      auto const chunk = std::string_view( it, chunk_size );
      ret.push_back( chunk );
   }
   return ret;
}

auto create_keys( std::string const& key ) -> std::vector<int>
{
   auto iss = std::istringstream( key );
   auto ret = std::vector<int>();
   ret.reserve( key.size() );
   for ( int tmp; iss >> tmp; )
   {
      ret.push_back( tmp );
   }
   return ret;
}

// todo edit for vector<int> instead of string_view
auto encrypt( std::vector<std::string_view> msg, std::vector<int> key) -> std::string
{
   auto blocks           = std::vector<std::string>();
   auto const block_size = key.size();

   for ( auto elem : msg )
   {
      auto block = std::string( block_size, ' ' );
      for ( auto i = 0; i < block_size; ++i )
      {
         block[i] = elem[key[i] - 1];    // "-'0'" to convert char to int and "-1" to bring it in range base 0
      }
      blocks.push_back( block );
   }
   return catenate( blocks );
}

auto catenate( std::vector<std::string> const& blocks ) -> std::string
{
   auto ret = std::string();
   
   for ( auto const& block : blocks )
   {
      ret.append( block );
   }
  
   return ret;
}