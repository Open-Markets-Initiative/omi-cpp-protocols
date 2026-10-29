#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// account
struct Account {

    static constexpr const char* name = "Account";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr Account()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Account(const std::uint32_t value)
     : value{ value } {}

    // get value of Account field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
