#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Optionally used in tailor made repo contracts and defines the type of broken dates as requested by trader. Null = Not applicable, 0 = Custom, 1 = Quarterly, 2 = Monthly
struct BrokenDateTermType {

    static constexpr auto name = "Broken Date Term Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr BrokenDateTermType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BrokenDateTermType(const std::uint8_t &value)
     : value{ value } {}

    // get value of BrokenDateTermType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
