#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The flow schedule type
struct FlowScheduleType {

    static constexpr auto name = "Flow Schedule Type";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

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
