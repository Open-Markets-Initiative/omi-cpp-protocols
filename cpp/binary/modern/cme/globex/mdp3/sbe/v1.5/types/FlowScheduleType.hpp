#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


// The schedule according to which the electricity is delivered in a physical contract, or priced in a financial contract. Specifies whether the contract is defined according to the Easter Peak, Eastern Off-Peak, Western Peak or Western Off-Peak.
struct FlowScheduleType {

    static constexpr auto name = "Flow Schedule Type";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 127;

    // default constructor
    constexpr FlowScheduleType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FlowScheduleType(const std::int8_t &value)
     : value{ value } {}

    // get value of FlowScheduleType field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
