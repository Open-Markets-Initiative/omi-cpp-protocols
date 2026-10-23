#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the type of Prior Day message
struct PriorDayMessageType {

    static constexpr auto name = "Prior Day Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PriorDayMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriorDayMessageType(const char &value)
     : value{ value } {}

    // get value of PriorDayMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
