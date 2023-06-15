#include "random_value_provider.hpp"

#include <boost/asio.hpp>
#include <fmt/core.h>
#include <ranges>
#include <vector>

using boost::asio::ip::udp;

class udp_client
{
public:
  udp_client( std::string_view host, unsigned short port )
  {
    udp::resolver resolver( io_context_ );
    receiver_endpoint_ =
      *resolver.resolve( udp::v4(), host, fmt::format( "{}", port ) ).begin();

    socket_.open( udp::v4() );
  }

  void send_data( std::vector< std::uint16_t > data )
  {
    socket_.send_to( boost::asio::buffer( data ), receiver_endpoint_ );
  }

  std::vector< uint16_t > receive_data()
  {
    constexpr std::size_t                   MAX_BUFFER_SIZE = 128;
    std::array< uint16_t, MAX_BUFFER_SIZE > recv_buf{};
    udp::endpoint                           sender_endpoint;

    size_t element_count =
      socket_.receive_from( boost::asio::buffer( recv_buf ), sender_endpoint ) /
      sizeof( uint16_t );

    auto r = recv_buf | std::ranges::views::take( element_count );

    std::vector< uint16_t > result;
    std::ranges::copy( r, std::back_inserter( result ) );

    return result;
  }

private:
  boost::asio::io_context io_context_;
  udp::socket             socket_{ io_context_ };
  udp::endpoint           receiver_endpoint_;
};

int main( int /*unused*/, char * /*unused*/[] )
{
  try
  {
    constexpr uint16_t SERVER_PORT      = 50000;
    constexpr uint16_t MAX_RANDOM_VALUE = 100;
    udp_client         client( "localhost", SERVER_PORT );

    random_value_provider< std::uint16_t > rvp;

    std::vector< std::uint16_t > send_buf;
    const auto                   length = rvp.next_value( 10, 20 );
    for( std::size_t i = 0; i <= length; ++i )
      send_buf.emplace_back( rvp.next_value( 1, MAX_RANDOM_VALUE ) );

    fmt::print( "about to send: " );
    for( const auto n : send_buf )
      fmt::print( "{} ", n );

    client.send_data( std::move( send_buf ) );

    fmt::print( "\nreceived from the server: " );
    for( const auto n : client.receive_data() )
      fmt::print( "{} ", n );
  }
  catch( std::exception &e )
  {
    fmt::print( stderr, "{}\n", e.what() );
  }

  return 0;
}
