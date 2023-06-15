#ifndef _random_value_provider_hpp_
#define _random_value_provider_hpp_

#include <concepts>
#include <random>

template< std::unsigned_integral T >
class random_value_provider
{
public:
  T next_value( T from, T to )
  {
    std::uniform_int_distribution< T > distribution{ from, to };

    return distribution( dre_ );
  }

private:
  std::random_device         rd_;
  std::default_random_engine dre_{ rd_() };
};

#endif // _random_value_provider_hpp_
