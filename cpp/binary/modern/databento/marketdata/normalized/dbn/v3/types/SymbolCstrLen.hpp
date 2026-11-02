#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The number of bytes in fixed-length symbol strings, including a null terminator byte; 71 in version 3
struct SymbolCstrLen {

    static constexpr const char* name = "Symbol Cstr Len";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SymbolCstrLen()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolCstrLen(const std::uint16_t value)
     : value{ value } {}

    // get value of SymbolCstrLen field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
