#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Market-data Refresh request/response discriminator carried over the ESesM unsequenced channel (Request Type R, Response Type r, End of Refresh E)
struct UnsequencedMessageType {

    static constexpr auto name = "Unsequenced Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UnsequencedMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnsequencedMessageType(const char &value)
     : value{ value } {}

    // get value of UnsequencedMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
