#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Number of entries in Market Data message for MDEntryGrp.
struct NoMdEntries {

    static constexpr auto name = "No Md Entries";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NoMdEntries()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoMdEntries(const std::uint8_t &value)
     : value{ value } {}

    // get value of NoMdEntries field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
