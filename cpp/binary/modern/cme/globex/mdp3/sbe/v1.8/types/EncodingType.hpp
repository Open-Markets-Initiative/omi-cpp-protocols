#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Encoding Type
struct EncodingType {

    static constexpr const char* name = "Encoding Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type static_value = 51966;

    // default constructor
    constexpr EncodingType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EncodingType(const std::uint16_t value)
     : value{ value } {}

    // get value of EncodingType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
