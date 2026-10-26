#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Maximum allowable width for a quote for this Option during regular trading in order to be considered as Priority Quote. 0 when Priority Quote Width is not applicable.
struct PriorityQuoteWidth {

    static constexpr const char* name = "Priority Quote Width";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr PriorityQuoteWidth()
     : value{ 0 } {}

    // constructor for PriorityQuoteWidth field
    constexpr explicit PriorityQuoteWidth(const std::uint32_t value)
     : value{ value } {}

    // get underlying integer of PriorityQuoteWidth field
    [[nodiscard]] std::uint32_t integer() const {
        return value;
    }

    // decimal value of PriorityQuoteWidth field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
