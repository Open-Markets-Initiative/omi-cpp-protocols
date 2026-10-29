#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// securityResponseID
struct SecurityResponseId {

    static constexpr const char* name = "Security Response Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SecurityResponseId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityResponseId(const std::uint64_t value)
     : value{ value } {}

    // get value of SecurityResponseId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
