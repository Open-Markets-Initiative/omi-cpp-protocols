#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Type of market data entry.
struct MdEntryType {

    static constexpr auto name = "Md Entry Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

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
