#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// businessRejectReason
struct BusinessRejectReason {

    static constexpr const char* name = "Business Reject Reason";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BusinessRejectReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BusinessRejectReason(const std::uint32_t value)
     : value{ value } {}

    // get value of BusinessRejectReason field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
