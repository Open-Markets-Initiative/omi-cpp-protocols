#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// allocAccount
struct AllocAccount {

    static constexpr const char* name = "Alloc Account";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AllocAccount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocAccount(const std::uint32_t value)
     : value{ value } {}

    // get value of AllocAccount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
