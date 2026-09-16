#pragma once

#include <cstddef>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// First byte of the Tcp packet identifying the packet type used as dispatch key
struct PacketType {

    static constexpr auto name = "Packet Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketType(const char &value)
     : value{ value } {}

    // get value of PacketType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
