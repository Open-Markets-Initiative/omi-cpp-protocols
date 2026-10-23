#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Security ID
struct SecurityId {

    static constexpr const char* name = "Security Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr SecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityId(const std::int32_t value)
     : value{ value } {}

    // get value of SecurityId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
