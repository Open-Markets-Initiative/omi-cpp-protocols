#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// 
struct MdEntryType {

    static constexpr auto name = "Md Entry Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 203;
static const type minimum_value = 2;

    // default constructor
    constexpr MdEntryType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdEntryType(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdEntryType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
