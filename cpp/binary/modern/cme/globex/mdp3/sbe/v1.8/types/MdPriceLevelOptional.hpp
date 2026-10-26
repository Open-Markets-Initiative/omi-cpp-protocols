#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Aggregate book position
struct MdPriceLevelOptional {

    static constexpr auto name = "Md Price Level Optional";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 127;

    // default constructor
    constexpr MdPriceLevelOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdPriceLevelOptional(const std::int8_t &value)
     : value{ value } {}

    // get value of MdPriceLevelOptional field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
