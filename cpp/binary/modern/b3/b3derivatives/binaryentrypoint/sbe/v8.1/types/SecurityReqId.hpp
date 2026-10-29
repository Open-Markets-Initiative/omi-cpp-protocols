#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// securityReqID
struct SecurityReqId {

    static constexpr const char* name = "Security Req Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SecurityReqId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityReqId(const std::uint64_t value)
     : value{ value } {}

    // get value of SecurityReqId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
