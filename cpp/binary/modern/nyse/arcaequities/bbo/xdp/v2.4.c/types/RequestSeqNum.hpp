#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// The sequence number of the request message sent by the client.
struct RequestSeqNum {

    static constexpr const char* name = "Request Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr RequestSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RequestSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of RequestSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
