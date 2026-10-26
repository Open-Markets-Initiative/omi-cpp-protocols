#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Max number of substitutions allowed. The value of 0 indicates that substitutions are not allowed
struct MaxNoOfSubstitutions {

    static constexpr auto name = "Max No Of Substitutions";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MaxNoOfSubstitutions()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaxNoOfSubstitutions(const std::uint8_t &value)
     : value{ value } {}

    // get value of MaxNoOfSubstitutions field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
