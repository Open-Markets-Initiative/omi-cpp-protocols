#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Message Size
struct MessageSize {

    static constexpr const char* name = "Message Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageSize(const std::uint16_t value)
     : value{ value } {}

    // get value of MessageSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
