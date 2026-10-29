#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// The Face Value Of A Debenture
struct FaceValue {

    static constexpr const char* name = "Face Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr FaceValue()
     : value{ 0 } {}

    // constructor for FaceValue field
    constexpr explicit FaceValue(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of FaceValue field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of FaceValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
