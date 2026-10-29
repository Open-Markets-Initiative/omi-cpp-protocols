#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// executeUnderlyingTrade
struct ExecuteUnderlyingTrade {

    static constexpr auto name = "Execute Underlying Trade";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr ExecuteUnderlyingTrade()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecuteUnderlyingTrade(const char &value)
     : value{ value } {}

    // get value of ExecuteUnderlyingTrade field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
