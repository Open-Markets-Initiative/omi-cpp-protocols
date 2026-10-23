#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// SesM protocol packet type
struct SesmPacketType {

    static constexpr auto name = "Sesm Packet Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SesmPacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SesmPacketType(const char &value)
     : value{ value } {}

    // get value of SesmPacketType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
