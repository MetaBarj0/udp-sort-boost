#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <fmt/core.h>
#include <ranges>

using boost::asio::ip::udp;

class udp_server
{
public:
  explicit udp_server( boost::asio::io_context &io_context ) :
    socket_( io_context, udp::endpoint( udp::v4(), SERVER_PORT ) )
  {
    start_receive();
  }

private:
  void start_receive()
  {
    socket_.async_receive_from(
      boost::asio::buffer( recv_buffer_ ), remote_endpoint_,
      boost::bind( &udp_server::handle_receive, this,
                   boost::asio::placeholders::error,
                   boost::asio::placeholders::bytes_transferred ) );
  }

  void handle_receive( const boost::system::error_code &error,
                       std::size_t                      bytes_transferred )
  {
    if( !error )
    {
      const size_t max_elements = bytes_transferred / sizeof( uint16_t );

      std::vector< uint16_t > short_array;

      auto r = recv_buffer_ | std::ranges::views::take( max_elements );

      std::ranges::copy( r, std::back_inserter( short_array ) );

      std::sort( short_array.begin(), short_array.end() );

      socket_.async_send_to(
        boost::asio::buffer( short_array ), remote_endpoint_,
        boost::bind( &udp_server::handle_send, this, short_array,
                     boost::asio::placeholders::error,
                     boost::asio::placeholders::bytes_transferred ) );

      start_receive();
    }
  }

  void handle_send( std::vector< uint16_t > /*message*/,
                    const boost::system::error_code & /*error*/,
                    std::size_t /*bytes_transferred*/ )
  {
  }

  static constexpr unsigned short SERVER_PORT                       = 50000;
  static constexpr unsigned short MAX_ARRAY_ELEMENT_COUNT           = 20;
  udp::endpoint                   remote_endpoint_                  = {};
  std::array< std::uint16_t, MAX_ARRAY_ELEMENT_COUNT > recv_buffer_ = {};
  udp::socket                                          socket_;
};

int main()
{
  try
  {
    boost::asio::io_context io_context;
    udp_server              server( io_context );
    io_context.run();
  }
  catch( std::exception &e )
  {
    fmt::print( stderr, "{}\n", e.what() );
  }

  return 0;
}
