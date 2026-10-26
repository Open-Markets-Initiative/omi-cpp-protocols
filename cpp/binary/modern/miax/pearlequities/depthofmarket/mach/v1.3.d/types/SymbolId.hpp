#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Symbol ID mapped to a given symbol. It is assigned per trading session and is valid for that session.
struct SymbolId {

    static constexpr const char* name = "Symbol Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SymbolId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolId(const std::uint32_t value)
     : value{ value } {}

    // get value of SymbolId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
