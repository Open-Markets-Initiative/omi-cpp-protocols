#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// The sequence number of this message in the set of all messages for this symbol
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
