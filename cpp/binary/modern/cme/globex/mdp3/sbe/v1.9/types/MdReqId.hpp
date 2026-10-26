#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Unique identifier for Market Data Request. Must be unique per session so it can be referenced in Request Ack or Request Reject responses from the exchange
struct MdReqId {

    static constexpr const char* name = "Md Req Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MdReqId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdReqId(const std::uint32_t value)
     : value{ value } {}

    // get value of MdReqId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
