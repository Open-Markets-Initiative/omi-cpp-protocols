#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Side requested
struct SideOptional {

    static constexpr auto name = "Side Optional";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 127;

    // default constructor
    constexpr SideOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SideOptional(const std::int8_t &value)
     : value{ value } {}

    // get value of SideOptional field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
