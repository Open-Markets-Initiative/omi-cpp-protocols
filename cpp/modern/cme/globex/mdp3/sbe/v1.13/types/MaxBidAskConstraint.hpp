#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Maximum bid/ask spread for which sub-tick orders will be accepted (Sub tick orders will be rejected if bid/ask spread is greater than this value)
struct MaxBidAskConstraint {

    static constexpr const char* name = "Max Bid Ask Constraint";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr MaxBidAskConstraint()
     : value{ 0 } {}

    // constructor for MaxBidAskConstraint field
    constexpr explicit MaxBidAskConstraint(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MaxBidAskConstraint field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MaxBidAskConstraint field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
