#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// 
struct BlockLength {

    static constexpr const char* name = "Block Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BlockLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockLength(const std::uint16_t value)
     : value{ value } {}

    // get value of BlockLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
