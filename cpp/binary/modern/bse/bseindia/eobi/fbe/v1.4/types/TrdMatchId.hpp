#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Unique identifier for each price level of a match event.
struct TrdMatchId {

    static constexpr const char* name = "Trd Match Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TrdMatchId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TrdMatchId(const std::uint32_t value)
     : value{ value } {}

    // get value of TrdMatchId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
