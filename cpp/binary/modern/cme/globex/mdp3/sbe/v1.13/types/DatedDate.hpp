#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Dated Date
struct DatedDate {

    static constexpr const char* name = "Dated Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr DatedDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DatedDate(const std::uint16_t value)
     : value{ value } {}

    // get value of DatedDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
