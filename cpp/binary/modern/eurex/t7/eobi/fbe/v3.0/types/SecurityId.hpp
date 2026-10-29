#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {

// 
struct SecurityId {

    static constexpr const char* name = "Security Id";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;
static const type maximum_value = 9223372036854775807;
static const type minimum_value = -9223372036854775807;

    // default constructor
    constexpr SecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityId(const std::int64_t value)
     : value{ value } {}

    // get value of SecurityId field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
