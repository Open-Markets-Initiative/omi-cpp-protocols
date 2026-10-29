#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Priority timestamp.
struct TrdRegTsTimePriority {

    static constexpr auto name = "Trd Reg Ts Time Priority";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr TrdRegTsTimePriority()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TrdRegTsTimePriority(const std::uint64_t &value)
     : value{ value } {}

    // get value of TrdRegTsTimePriority field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
