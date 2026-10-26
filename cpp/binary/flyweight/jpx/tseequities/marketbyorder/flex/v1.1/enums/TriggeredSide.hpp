#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates the side whose order triggered the execution
enum class TriggeredSide : char {
    SellOrder = 'S',        // Sell Order
    BuyOrder = 'B',         // Buy Order
    ItayoseExecution = ' ', // Itayose Execution
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TriggeredSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TriggeredSide value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
