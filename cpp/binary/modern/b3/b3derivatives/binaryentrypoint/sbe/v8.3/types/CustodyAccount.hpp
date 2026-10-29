#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// custodyAccount
struct CustodyAccount {

    static constexpr const char* name = "Custody Account";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CustodyAccount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CustodyAccount(const std::uint32_t value)
     : value{ value } {}

    // get value of CustodyAccount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
