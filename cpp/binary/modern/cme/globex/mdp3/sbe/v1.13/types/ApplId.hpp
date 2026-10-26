#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// The channel ID as defined in the XML Configuration file
struct ApplId {

    static constexpr const char* name = "Appl Id";
    static constexpr std::size_t size =  2;
    using type = std::int16_t;

    // default constructor
    constexpr ApplId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ApplId(const std::int16_t value)
     : value{ value } {}

    // get value of ApplId field
    [[nodiscard]] std::int16_t get() const {
        return value;
    }

  protected:
    std::int16_t value;
};
}
