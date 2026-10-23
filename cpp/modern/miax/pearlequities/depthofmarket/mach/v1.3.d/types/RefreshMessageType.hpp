#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Identifies the data set the firm is requesting a refresh of.
struct RefreshMessageType {

    static constexpr auto name = "Refresh Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RefreshMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RefreshMessageType(const char &value)
     : value{ value } {}

    // get value of RefreshMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
