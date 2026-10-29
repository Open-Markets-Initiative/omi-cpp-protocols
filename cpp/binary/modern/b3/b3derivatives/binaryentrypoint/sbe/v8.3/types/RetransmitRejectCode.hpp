#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// retransmitRejectCode
struct RetransmitRejectCode {

    static constexpr auto name = "Retransmit Reject Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr RetransmitRejectCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RetransmitRejectCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of RetransmitRejectCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
