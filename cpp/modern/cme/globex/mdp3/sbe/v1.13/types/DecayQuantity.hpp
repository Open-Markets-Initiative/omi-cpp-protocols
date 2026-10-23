#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Indicates the quantity that a contract will decay daily by once the decay start date is reached
struct DecayQuantity {

    static constexpr const char* name = "Decay Quantity";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr DecayQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DecayQuantity(const std::int32_t value)
     : value{ value } {}

    // get value of DecayQuantity field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
