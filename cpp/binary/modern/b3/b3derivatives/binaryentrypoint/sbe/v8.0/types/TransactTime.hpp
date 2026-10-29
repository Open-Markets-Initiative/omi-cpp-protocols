#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// transactTime
struct TransactTime {

    static constexpr auto name = "Transact Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr TransactTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TransactTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of TransactTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
