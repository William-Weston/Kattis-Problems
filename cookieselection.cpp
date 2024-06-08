#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <queue>



class Holding_Area final
{
public:
   auto add( int diameter ) -> void;
   auto request()           -> int;

private:
   using max_heap = std::priority_queue<int, std::vector<int>, std::less<int>>;
   using min_heap = std::priority_queue<int, std::vector<int>, std::greater<int>>;

   max_heap max_queue = {};
   min_heap min_queue = {};
};

auto
Holding_Area::add( int diameter ) -> void
{
   if ( max_queue.empty() || diameter >= max_queue.top() )
   {
      min_queue.push( diameter );
   }
   else
   {
      max_queue.push( diameter );
      min_queue.push( max_queue.top() );
      max_queue.pop();
   }
   if ( min_queue.size() > ( max_queue.size() + 1 ) )
   {
     max_queue.push( min_queue.top() );
     min_queue.pop();
   }
}

auto
Holding_Area::request()  -> int
{
   assert( min_queue.size() );

   auto cookie = min_queue.top();
   min_queue.pop();

   if ( max_queue.size() > min_queue.size() )
   {
      min_queue.push( max_queue.top() );
      max_queue.pop();
   }

   return cookie;
}

auto
main() -> int
{
   auto holding_area = Holding_Area{};

   for ( std::string input; std::cin >> input; )
   {
      if ( input == "#" )        // request
      {
         std::cout << holding_area.request() << '\n';
      }
      else                       // cookie arrival
      {
         int const diameter = std::stoi( input );
         holding_area.add( diameter );
      }
   }

   return EXIT_SUCCESS;
}
