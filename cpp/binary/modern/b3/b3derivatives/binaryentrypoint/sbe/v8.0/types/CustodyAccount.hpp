// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.0: types/CustodyAccount.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// custodyAccount
struct CustodyAccount {

    static constexpr const char* name = "Custody Account";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr CustodyAccount()
     : value{ no_value } {}

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
