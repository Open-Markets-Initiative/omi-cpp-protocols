// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: types/GoodbyeReason.hpp
#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// GoodBye Packet Reason
struct GoodbyeReason {

    static constexpr auto name = "Goodbye Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr GoodbyeReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit GoodbyeReason(const char &value)
     : value{ value } {}

    // get value of GoodbyeReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
