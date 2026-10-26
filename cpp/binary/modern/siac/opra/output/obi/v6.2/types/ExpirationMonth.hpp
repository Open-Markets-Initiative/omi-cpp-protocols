#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Indicates the expiration month and identifies the option as a Call or a Put.
struct ExpirationMonth {

    static constexpr auto name = "Expiration Month";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExpirationMonth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationMonth(const char &value)
     : value{ value } {}

    // get value of ExpirationMonth field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
