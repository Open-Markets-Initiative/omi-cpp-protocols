#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Tick Rule
struct TickRule {

    static constexpr auto name = "Tick Rule";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 127;

    // default constructor
    constexpr TickRule()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TickRule(const std::int8_t &value)
     : value{ value } {}

    // get value of TickRule field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
