#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// ESesM protocol packet type
struct EsesmPacketType {

    static constexpr auto name = "Esesm Packet Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EsesmPacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EsesmPacketType(const char &value)
     : value{ value } {}

    // get value of EsesmPacketType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
