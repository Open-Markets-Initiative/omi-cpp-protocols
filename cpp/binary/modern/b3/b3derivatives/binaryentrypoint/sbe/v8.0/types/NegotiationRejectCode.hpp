#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// negotiationRejectCode
struct NegotiationRejectCode {

    static constexpr auto name = "Negotiation Reject Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NegotiationRejectCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NegotiationRejectCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of NegotiationRejectCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
