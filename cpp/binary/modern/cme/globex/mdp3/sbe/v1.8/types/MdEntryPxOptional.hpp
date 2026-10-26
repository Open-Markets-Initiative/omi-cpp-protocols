#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Market Data entry price
struct MdEntryPxOptional {

    static constexpr const char* name = "Md Entry Px Optional";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 7;
    static constexpr double denominator = 10000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr MdEntryPxOptional()
     : value{ 0 } {}

    // constructor for MdEntryPxOptional field
    constexpr explicit MdEntryPxOptional(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdEntryPxOptional field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdEntryPxOptional field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
