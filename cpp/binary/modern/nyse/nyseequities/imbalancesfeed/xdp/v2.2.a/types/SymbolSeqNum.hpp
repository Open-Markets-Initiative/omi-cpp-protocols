#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// The unique ID of this message in the sequence of messages published for this specific symbol.
struct SymbolSeqNum {

    static constexpr const char* name = "Symbol Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SymbolSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of SymbolSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
