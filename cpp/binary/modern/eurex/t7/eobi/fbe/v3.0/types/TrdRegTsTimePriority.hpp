#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// 
struct TrdRegTsTimePriority {

    static constexpr auto name = "Trd Reg Ts Time Priority";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0xFFFFFFFFFFFFFFFF;
static const type maximum_value = 18446744073709551614ULL;
static const type minimum_value = 0;

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
