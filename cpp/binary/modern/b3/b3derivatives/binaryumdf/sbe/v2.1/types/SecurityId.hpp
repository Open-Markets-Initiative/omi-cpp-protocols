#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// securityID
struct SecurityId {

    static constexpr const char* name = "Security Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityId(const std::uint64_t value)
     : value{ value } {}

    // get value of SecurityId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
