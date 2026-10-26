#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Workup price
struct MdEntryPxOptionalEx {

    static constexpr const char* name = "Md Entry Px Optional Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr MdEntryPxOptionalEx()
     : value{ 0 } {}

    // constructor for MdEntryPxOptionalEx field
    constexpr explicit MdEntryPxOptionalEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdEntryPxOptionalEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdEntryPxOptionalEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
