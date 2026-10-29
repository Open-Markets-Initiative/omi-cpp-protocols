#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Symbol Index
struct SymbolId {

    static constexpr const char* name = "Symbol Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SymbolId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolId(const std::uint16_t value)
     : value{ value } {}

    // get value of SymbolId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
