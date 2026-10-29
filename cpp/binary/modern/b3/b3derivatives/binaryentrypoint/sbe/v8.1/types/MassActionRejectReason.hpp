#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// massActionRejectReason
struct MassActionRejectReason {

    static constexpr auto name = "Mass Action Reject Reason";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MassActionRejectReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MassActionRejectReason(const std::uint8_t &value)
     : value{ value } {}

    // get value of MassActionRejectReason field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
