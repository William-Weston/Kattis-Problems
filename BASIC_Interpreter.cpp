/**
 * @file    BASIC_Interpreter.cpp
 * @author  William Weston
 * @brief   BASIC Interpreter Problem From Kattis
 * @version 0.1
 * @date    2023-09-23
 * 
 * @copyright Copyright (c) 2023
 * 
 * Link: https://open.kattis.com/problems/basicinterpreter
 */

// ------------------------------------------------------------------------------------------------
// -------------------------------------------- include -------------------------------------------

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <stdexcept>
#include <sstream>            // istringstream
#include <string>
#include <unordered_map>
#include <utility>            // move


// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------- Contants.h -----------------------------------------

constexpr auto let_t     = '|';
constexpr auto if_t      = '%';
constexpr auto print_t   = 'p';
constexpr auto println_t = 'q';
constexpr auto then_t    = 't';
constexpr auto goto_t    = 'g';
constexpr auto literal_t = 's';
constexpr auto number_t  = '#';
constexpr auto eol_t     = '?';
constexpr auto le_t      = '[';  // less than or equal to 
constexpr auto ge_t      = ']';  // greater than or equal to 
constexpr auto ne_t      = '!';  // not equal to 

constexpr auto letkey     = "LET";
constexpr auto ifkey      = "IF";
constexpr auto printkey   = "PRINT";
constexpr auto printlnkey = "PRINTLN";
constexpr auto thenkey    = "THEN";
constexpr auto gotokey    = "GOTO";

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// -------------------------------------------- Error.h -------------------------------------------

namespace wjtw
{
   
inline void error ( std::string const& msg )
{
	throw std::runtime_error( msg );
}

inline void error( std::string const& msg, int val )
{
   throw std::runtime_error( msg + std::to_string( val ) );
}

inline void error( std::string const& msg, std::string const& val )
{
   throw std::runtime_error( msg + val );
}

}

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------- safe_int_t.h ---------------------------------------

class safe_int_t final
{
public:
   constexpr safe_int_t( int value = 0 ) noexcept
      : value_{ value } {}

   constexpr auto value() const noexcept -> int;

   constexpr auto operator+= ( safe_int_t rhs ) -> safe_int_t&;
   constexpr auto operator-= ( safe_int_t rhs ) -> safe_int_t&;
   constexpr auto operator*= ( safe_int_t rhs ) -> safe_int_t&;
   constexpr auto operator/= ( safe_int_t rhs ) -> safe_int_t&;

private:
   int value_;
};

constexpr auto operator== ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool;
constexpr auto operator<  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool;

constexpr auto operator!= ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool;
constexpr auto operator>  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool;
constexpr auto operator<= ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool;
constexpr auto operator>= ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool;

constexpr auto operator+  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t;
constexpr auto operator-  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t;
constexpr auto operator*  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t;
constexpr auto operator/  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t;

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ----------------------------------------- Symbol_table.h ---------------------------------------

class Symbol_table final
{
public:
   auto get_value( char symbol )             -> int;
   auto set_value( char symbol, int value )  -> void;
   auto add_symbol( char symbol, int value ) -> void;
   auto is_declared( char symbol )  const    -> bool;

private:
   std::unordered_map<char, int> table_;
};

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------- Token.h --------------------------------------------

struct Token final
{
   constexpr Token() noexcept = default;

   Token( char aKind, int aValue = 0 )
      : kind{ aKind }, value{ aValue } {}

   Token( char aKind, std::string aName )
      : kind{ aKind }, name{ std::move( aName ) } {}

   char        kind  = eol_t;      // end-of-line
   int         value = 0;
   std::string name  = {};
};

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ---------------------------------------- Token_stream.h ----------------------------------------

class Token_stream final
{
public:
   auto reset( std::string const& expression ) -> void;
   auto get()                                  -> Token;
   auto putback( Token token )                 -> void;
   auto ignore( char ch )                      -> void;

private:
   std::istringstream stream_  = {};
   Token              buffer_  = {};
   bool               is_full_ = false;
};

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ----------------------------------------- Interpreter.h ----------------------------------------

class Interpreter final
{
   using line_pointer_t = std::map<int, std::string>::iterator;

public:
   explicit Interpreter( std::istream& in = std::cin, std::ostream& out = std::cout );

private:
   std::map<int, std::string> program_ = {};
   line_pointer_t             line_pointer_;
   Symbol_table               symbol_table_;
   Token_stream               token_stream_;
   std::ostream&              out_;
   
   auto parse_input( std::istream& in ) -> void;
   auto evaluate_program()              -> void;
   auto statement()                     -> std::optional<int>;      // optional next line to evaluate
   auto assignment()                    -> void;
   auto if_block()                      -> std::optional<int>;
   auto print()                         -> void;
   auto println()                       -> void;
   auto print_statement()               -> std::string;
   auto arithmetic_statment()           -> int;
   auto primary()                       -> int;
   auto condition()                     -> bool;
 };

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ---------------------------------------------- main ---------------------------------------------

auto 
main() -> int
{
   try
   {
      auto basic = Interpreter();
   }
   catch( std::exception const& e)
   {
      std::cerr << e.what() << '\n';
   }
   return EXIT_SUCCESS;
}

// ------------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
// --------------------------------------- safe_int_t.inl -----------------------------------------


// ------------------------------------------ details ---------------------------------------------

namespace details
{
   constexpr auto wrap( double n ) noexcept -> int;
}


auto 
is_alpha( char ch ) -> bool
{
   return std::isalpha( static_cast<unsigned char>( ch ) );
}

auto 
is_upper( char ch ) -> bool
{
   return std::isupper( static_cast<unsigned char>( ch ) );
}

auto 
is_space( char ch ) -> bool
{
   return std::isspace( static_cast<unsigned char>( ch ) );
}


// ----------------------------------------- Interface --------------------------------------------


constexpr auto 
safe_int_t::value() const noexcept -> int
{
   return value_;
}

constexpr auto 
safe_int_t::operator+= ( safe_int_t rhs ) -> safe_int_t&
{
   auto const n = static_cast<double>( value_ ) + static_cast<double>( rhs.value_ );
   value_ = details::wrap( n );
   return *this;
}

constexpr auto 
safe_int_t::operator-= ( safe_int_t rhs ) -> safe_int_t&
{
   auto const n = static_cast<double>( value_ ) - static_cast<double>( rhs.value_ );
   value_ = details::wrap( n );
   return *this;
}


constexpr auto 
safe_int_t::operator*= ( safe_int_t rhs ) -> safe_int_t&
{
   auto const n = static_cast<double>( value_ ) * static_cast<double>( rhs.value_ );
   value_ = details::wrap( n );
   return *this;
}


constexpr auto 
safe_int_t::operator/= ( safe_int_t rhs ) -> safe_int_t&
{
   value_ /= rhs.value_;
   return *this;
}

// ------------------------------------- Non-Member Interface -------------------------------------

constexpr auto 
operator== ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool
{
   return lhs.value() == rhs.value();
}

constexpr auto 
operator<  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool
{
   return lhs.value() < rhs.value();
}

constexpr auto 
operator!= ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool
{
   return !( lhs == rhs );
}

constexpr auto 
operator>  ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool
{
   return rhs < lhs;
}

constexpr auto 
operator<= ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool
{
   return !( rhs < lhs );
}

constexpr auto 
operator>= ( safe_int_t lhs, safe_int_t rhs ) noexcept -> bool
{
   return !( lhs < rhs );
}


constexpr auto 
operator+ ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t
{
   return lhs += rhs;
}

constexpr auto 
operator- ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t
{
   return lhs -= rhs; 
}

constexpr auto 
operator* ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t
{
   return lhs *= rhs;
}

constexpr auto 
operator/ ( safe_int_t lhs, safe_int_t rhs ) noexcept -> safe_int_t
{
   return lhs /= rhs;
}

// ---------------------------------------- details ------------------------------------------------

constexpr auto 
details::wrap( double n ) noexcept -> int
{
   constexpr auto const min = std::numeric_limits<int>::min();
   constexpr auto const max = std::numeric_limits<int>::max();

   while ( n < min || n > max  )
   {
      if ( n < 0 )
      {
         n = max + ( n - ( min - 1.0 ) );
      }

      else if ( n > 0 )
      {
         n = min + ( n - ( max + 1.0 ) );
      }
   }

   return static_cast<int>( std::round( n ) );
}

// ------------------------------------------------------------------------------------------------


// ---------------------------------------- Interpreter.cpp ---------------------------------------
// ------------------------------------------------------------------------------------------------

Interpreter::Interpreter( std::istream& in, std::ostream& out )
   : out_{ out }
{
   parse_input( in );
   line_pointer_ = program_.begin();
   evaluate_program();
}


auto
Interpreter::parse_input( std::istream& in ) -> void
{
   int line_no;

   while ( in >> line_no )
   {
      auto line = std::string();
      std::getline( in >> std::ws, line );
      program_[line_no] = line;
   }
}


auto
Interpreter::evaluate_program() -> void
{
   while ( line_pointer_ != program_.end() )
   {
      token_stream_.reset( line_pointer_->second );
      auto const opt_next_line = statement();

      if ( opt_next_line )
         line_pointer_ = program_.find( *opt_next_line );
      else
         ++line_pointer_;
   }
}


auto
Interpreter::statement() -> std::optional<int>
{
   auto token = token_stream_.get();

   switch ( token.kind )
   {
      case let_t:
      {
         assignment();
         return std::nullopt;
      }

      case if_t:
      {
         return if_block();
      }

      case print_t:
      {
         print();
         return std::nullopt;
      }

      case println_t:
      {
         println();
      }

   }

   return std::nullopt;
}


auto
Interpreter::if_block()   -> std::optional<int>
{
   if ( condition() )
   {
      auto const then_token = token_stream_.get();

      if ( then_token.kind != then_t )
      {
         wjtw::error( "THEN token expected after IF" );
      }

      auto const goto_token = token_stream_.get();

      if ( goto_token.kind != goto_t )
      {
         wjtw::error( "GOTO token expected after THEN" );
      }

      auto const line_token = token_stream_.get();
      if ( line_token.kind != number_t  )
      {
         wjtw::error( "Line No. expected after GOTO" );
      }

      return line_token.value;
   }

   return std::nullopt;
}


auto
Interpreter::print() -> void
{
   out_ << print_statement();
}


auto
Interpreter::println() -> void
{
   out_ << print_statement() << '\n';
}


auto
Interpreter::print_statement() -> std::string
{
   auto const token = token_stream_.get();

   if ( is_upper( token.kind ) )       // variable name
   {
      auto const value =  symbol_table_.get_value( token.kind );
      return std::to_string( value );
   }

   switch ( token.kind )
   {
      case literal_t:
      {
         return token.name;      // string literal
      }   
   }

   wjtw::error( "non-printable token" );
   return {};
}


auto
Interpreter::assignment() -> void
{
   auto const token = token_stream_.get();

   if ( !is_upper( token.kind ) )     // 
   {
      wjtw::error( "expected variable name in assignment" );
   }

   auto const equal_token = token_stream_.get();
   
   if ( equal_token.kind != '=' )
   {
      wjtw::error( "assignment expects = sign" );
   }

   auto const var_name = token.kind;
   auto const value    = arithmetic_statment();

   symbol_table_.set_value( var_name, value );
}


/**
 * @brief 
 * 
 * @return int 
 * 
 * Grammar:
 *    Primary 
 *	   Primary + Primary
 *	   Primary - Primary
 *	   Primary * Primary
 *	   Primary / Primary
 */
auto
Interpreter::arithmetic_statment() -> int
{
   auto left = primary();
   auto token = token_stream_.get();

   while ( true )
   switch ( token.kind )         // TODO: must alter to account for overflow/underflow
   {
      case '+':
      {
         auto const safe = safe_int_t( left ) + safe_int_t( primary() );
         return safe.value();
      }

      case '-':
      {
         auto const safe = safe_int_t( left ) - safe_int_t( primary() );
         return safe.value();
      }

      case '*':
      {
         auto const safe = safe_int_t( left ) * safe_int_t( primary() );
         return safe.value();
      }

      case '/':
         return left / primary();

      default:
         token_stream_.putback( std::move( token ) );
         return left;
   }
}


/**
 * @brief 
 * 
 * @return int 
 * 
 * Grammar:
 *    Number
 *    Variable
 */
auto
Interpreter::primary() -> int
{
   auto const token = token_stream_.get();

   switch ( token.kind )
   {
      case number_t:
         return token.value;
      
      case '-':
         return -primary();
      
      case '+':
         return primary();
   }

   if ( is_upper( token.kind ) )       // variable name
   {
      return symbol_table_.get_value( token.kind );
   }

   wjtw::error( "expected primary" );
   return -1;     // 
}


/**
 * @brief 
 * 
 * @return true 
 * @return false 
 * 
 * Grammar:
 *    Primary = Primary
 *	   Primary <> Primary		// inequality
 *	   Primary > Primary
 *	   Primary < Primary
 *	   Primary <= Primary
 *	   Primary >= Primary
 */
auto
Interpreter::condition() -> bool
{
   auto const left = primary();
   auto const compare = token_stream_.get();

   switch ( compare.kind )
   {
      case '<':
      {
         auto const right = primary();
         return left < right;
      }

      case le_t:
      {
         auto const right = primary();
         return left <= right;
      }

      case '>':
      {
         auto const right = primary();
         return left > right;
      }

      case ge_t:
      {
         auto const right = primary();
         return left >= right;
      }

      case '=':
      {
         auto const right = primary();
         return left == right;
      }

      case ne_t:
      {
         auto const right = primary();
         return left != right;
      }

      default:
      {
         wjtw::error( "Condition requires comparison operator" );
         return false;
      }
   }
}

// ------------------------------------------------------------------------------------------------


// --------------------------------------- Symbol_table.cpp ---------------------------------------
// ------------------------------------------------------------------------------------------------

/**
 * @brief 
 * 
 * @param symbol 
 * @return int 
 * @note Any variable that doesn't exist will be entered into the table and zero initialized
 */
auto 
Symbol_table::get_value(char symbol ) -> int
{
   if ( is_declared( symbol ) )
   {
      return table_[symbol];
   }
   
   add_symbol( symbol, 0 );
   return 0;
}


auto 
Symbol_table::set_value( char symbol, int const value ) -> void
{
   table_[symbol] = value;
}


auto 
Symbol_table::add_symbol( char symbol, int const value ) -> void
{
   table_[symbol] = value;
}


auto 
Symbol_table::is_declared( char symbol ) const -> bool
{
   return table_.count( symbol );
}

// ------------------------------------------------------------------------------------------------


// --------------------------------------- Token_stream.cpp ---------------------------------------
// ------------------------------------------------------------------------------------------------

auto
Token_stream::reset( std::string const& expression ) -> void
{
   is_full_ = false;
   stream_.str( expression );                   // equivalent to stream_.rdbuf()->str(s);
   stream_.clear();                             // clear the flags
   stream_.seekg( std::ios_base::beg );			// reposition the stream to the beginning
}


auto
Token_stream::get() -> Token
{
   if ( is_full_ )         // if there is a token in the buffer
   {
      is_full_ = false;
      return buffer_;
   }

   char tmp;
   stream_ >> tmp;

   if ( !stream_ )
      return Token();      // default is end-of-line token

   switch ( tmp )
   {
      case '=':
      case '+':
      case '-':
      case '*':
      case '/':
      {
         return Token( tmp );    // let each character represent itself
      }

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      {
         stream_.putback( tmp );				// put the digit back onto the input stream
         int value;

         stream_ >> value;					   // read an integer 
         return Token( number_t, value );
      }

      case '<':         // could be <, <=, <>
      {
         if ( stream_.get( tmp ) )
         {
            switch ( tmp )
            {
               case '=':
               {
                  return Token( le_t );        // less than or equal to
               }

               case '>':
               {
                  return Token( ne_t );        // not equal to
               }

               default:
                  stream_.putback( tmp );
            }
         }
         return Token( '<' );             // less than      
      }

      case '>':         //  >, >=
      {
         if ( stream_.get( tmp ) )
         {
            if ( tmp == '=' )
               return Token( ge_t );        // greater than or equal to

            stream_.putback( tmp );
         }

         return Token( '>' );             // greater than
      }

      case '"':
      {
         auto str = std::string();
         

         while ( stream_.get( tmp ) && tmp != '"' )
         {
            str += tmp;
         }

         if ( tmp != '"' )
            wjtw::error( "no closing quote on string literal" );
         
         return Token( literal_t, std::move( str ) );
      }

      default:       // could be variable name, or keyword ( GOTO, PRINT, PRINTLN, IF, THEN )
      {
         if ( is_alpha( tmp ) )
         {
             // check if we have a single character variable
            auto next = char{};
            if ( !stream_.get( next ) || is_space( next ) )
            {
               return Token( tmp ); 
            }

            stream_.putback( next );

            auto str = std::string();
            str += tmp;

            while ( stream_.get( tmp ) && is_alpha( tmp ) )
            {
               str += tmp;
            }

            stream_.putback( tmp );       // if we've read to far put the character back on the stream otherwise we're at eof and it doesn't matter

            if ( str == letkey )
               return Token( let_t );

            if ( str == ifkey )
               return Token( if_t );

            if ( str == printkey )
               return Token( print_t );

            if ( str == printlnkey )
               return Token( println_t );

            if ( str == thenkey )
               return Token( then_t );

            if ( str == gotokey )
               return Token( goto_t );
         }
      }
   }  // end switch

   wjtw::error( "Bad Token" );

   return {};
}


auto
Token_stream::putback( Token token ) -> void
{
   if ( is_full_ )
   {
      wjtw::error( "putback() into a full buffer" );
   }

   buffer_  = std::move( token );
   is_full_ = true;
}


auto
Token_stream::ignore( char const ch ) -> void
{
   // first look in the buffer
   if ( is_full_ && ch == buffer_.kind )
   {
      is_full_ = false;
      return;
   }

   is_full_ = false;

   char tmp;
   while ( stream_ >> tmp )      // advance the stream until we've encountered the character we wish to ignore
   {
      if ( tmp == ch )
         return;
   }
}

// ------------------------------------------------------------------------------------------------
