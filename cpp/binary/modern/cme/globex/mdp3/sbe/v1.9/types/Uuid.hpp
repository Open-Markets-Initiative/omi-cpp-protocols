#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Session Identifier defined as type long uInt64, recommended to use timestamp as number of microseconds since Unix epoch
struct Uuid {

    static constexpr const char* name = "Uuid";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Uuid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Uuid(const std::uint64_t value)
     : value{ value } {}

    // get value of Uuid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
