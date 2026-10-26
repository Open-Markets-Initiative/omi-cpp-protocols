#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// If this tag is present, 35=f message is sent for the instrument
struct SecurityIdOptional {

    static constexpr const char* name = "Security Id Optional";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr SecurityIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityIdOptional(const std::int32_t value)
     : value{ value } {}

    // get value of SecurityIdOptional field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
