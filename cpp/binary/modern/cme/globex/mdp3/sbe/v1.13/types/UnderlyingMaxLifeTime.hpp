#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Max life time of the underlying instruments qualifying for the GC basket in number of year. Will contain null value for Repo specials
struct UnderlyingMaxLifeTime {

    static constexpr auto name = "Underlying Max Life Time";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr UnderlyingMaxLifeTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingMaxLifeTime(const std::uint8_t &value)
     : value{ value } {}

    // get value of UnderlyingMaxLifeTime field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
