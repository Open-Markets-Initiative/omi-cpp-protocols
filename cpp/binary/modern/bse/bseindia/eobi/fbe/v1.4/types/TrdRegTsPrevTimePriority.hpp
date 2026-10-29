#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Previous order priority timestamp.
struct TrdRegTsPrevTimePriority {

    static constexpr auto name = "Trd Reg Ts Prev Time Priority";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr TrdRegTsPrevTimePriority()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TrdRegTsPrevTimePriority(const std::uint64_t &value)
     : value{ value } {}

    // get value of TrdRegTsPrevTimePriority field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
