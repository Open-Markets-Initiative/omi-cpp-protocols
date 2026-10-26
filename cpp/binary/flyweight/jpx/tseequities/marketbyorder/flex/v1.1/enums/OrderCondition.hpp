#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates the order condition
enum class OrderCondition : std::uint8_t {
    Nonconditional = 0, // Nonconditional
    Onopen = 2,         // Onopen
    Onclose = 4,        // Onclose
    Funari = 6,         // Funari
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderCondition value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
