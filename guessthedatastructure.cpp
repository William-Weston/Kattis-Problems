  /**
 * @file    guessthedatastructure.cpp
 * @author  William Weston
 * @brief   I Can Guess the Data Structure! Problem from Kattis
 * @version 0.1
 * @date    2023-06-19
 *
 * @copyright Copyright (c) 2023
 *
 * Source: https: //open.kattis.com/problems/guessthedatastructure
 */


#include <cstdlib>
#include <iostream>
#include <queue>              // priority_queue, queue
#include <stack>              // stack
#include <string>
//#include <type_traits>        // same_as
#include <tuple>
#include <utility>
#include <vector>


struct Command final
{
   enum operation
   {
      in,
      out
   };

   operation op;
   int       param;
};

auto operator>>( std::istream& in, Command& cmd )->std::istream&;


class Solver final
{
public:
   explicit Solver( std::vector<Command>&& cmds ) noexcept
      : cmds_( std::move( cmds) ) {}
   
   auto solve() -> void;

private:
   std::vector<Command> cmds_ = {};
};


struct Results final
{
   bool is_pq;
   bool is_stack;
   bool is_queue;
};

struct Containers final
{
   std::priority_queue<int> pq_    = {};
   std::stack<int>          stack_ = {};
   std::queue<int>          queue_ = {};

   auto add( int value )       -> void;
   auto remove( int expected ) -> Results;

};

template <typename... Args> constexpr auto
XOR( Args... args ) -> bool
//   requires ( std::same_as<bool, Args> && ... )
{
   return ( ( args != ... ) && !( args && ...) );
}

auto
main() -> int
{

   auto N = 0;       // number of commands for a given test case

   while ( std::cin >> N )
   {
      auto cmds = std::vector<Command>();

      for ( auto idx = 0; idx < N; ++idx )
      {
         auto tmp = Command();

         std::cin >> tmp;
         cmds.push_back( tmp );
      }

      auto solver = Solver( std::move( cmds ) );

      solver.solve();
   }

   return EXIT_SUCCESS;
}

auto
operator>>( std::istream& in, Command& cmd ) -> std::istream&
{
   int i;
   in >> i >> cmd.param;

   switch ( i )
   {
      case 1:
         cmd.op = Command::in;
         break;
      case 2:
         cmd.op = Command::out;
         break;
      defaule:
         std::cerr << "Error! Unknown Operation";
         break;
   }

   return in;
}


auto 
Solver::solve() -> void
{
   using namespace std::literals;

   auto containers = Containers();

   bool is_pq, is_stack, is_queue = true;

   for ( auto cmd : cmds_ )
   {
      auto [op, param] = cmd;

      switch( op )
      {
         case Command::in:
         {
            containers.add( param );
         }
         break;

         case Command::out:
         {
            auto const [pq_result, stack_result, queue_result] = containers.remove( param );
            
            is_pq    = ( is_pq )    ? pq_result    : false;
            is_stack = ( is_stack ) ? stack_result : false;
            is_queue = ( is_queue ) ? queue_result : false;
         }
         break;

         default:
         {
            std::cerr << "Error: Unknown Command";
         }
      }  // switch
   } // for

   // case impossible: is_pq && is_stack && is_queue == false 
   if ( !( is_pq || is_stack || is_queue ) )
   {
      std::cout << "impossible\n";
   }

   // case only 1 correct answer
   else if ( XOR( is_pq, is_stack, is_queue ) )                                 // (  ( is_pq ^ is_stack ^ is_queue ) ^ ( is_pq && is_stack && is_queue ) )				// WRONG!!! Requires logical XOR
   {
      std::cout << ( ( is_pq )     ? "priority queue\n"s :
                     ( is_stack )  ? "stack\n"s 
                                   : "queue\n"s );
                 
   }
   
   // case not sure ( multiple correct answers)
   else
   {
      std::cout << "not sure\n";
   }
}

auto 
Containers::add( int value ) -> void
{
   pq_.push( value );
   stack_.push( value );
   queue_.push( value );
}

auto 
Containers::remove( int expected ) -> Results
{
   if ( !pq_.size() )                              // access attempt on empty containers
      return Results{ false, false, false };

   auto const pq_result    = pq_.top();
   auto const stack_result = stack_.top();
   auto const queue_result = queue_.front();

   pq_.pop();
   stack_.pop();
   queue_.pop();

   return Results{ pq_result == expected, stack_result == expected, queue_result == expected };
}
