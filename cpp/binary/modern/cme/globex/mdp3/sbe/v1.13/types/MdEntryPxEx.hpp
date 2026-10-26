#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Trade price
struct MdEntryPxEx {

    static constexpr const char* name = "Md Entry Px Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr MdEntryPxEx()
     : value{ 0 } {}

    // constructor for MdEntryPxEx field
    constexpr explicit MdEntryPxEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdEntryPxEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdEntryPxEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
