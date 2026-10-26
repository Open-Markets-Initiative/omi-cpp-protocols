#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// The ID of the symbol in the Symbol Index msg
struct SymbolIndex {

    static constexpr const char* name = "Symbol Index";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SymbolIndex()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolIndex(const std::uint32_t value)
     : value{ value } {}

    // get value of SymbolIndex field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
