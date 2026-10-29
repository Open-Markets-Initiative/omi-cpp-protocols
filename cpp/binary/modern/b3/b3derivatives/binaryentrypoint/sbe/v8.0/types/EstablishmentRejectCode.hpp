#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// establishmentRejectCode
struct EstablishmentRejectCode {

    static constexpr auto name = "Establishment Reject Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr EstablishmentRejectCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EstablishmentRejectCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of EstablishmentRejectCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
