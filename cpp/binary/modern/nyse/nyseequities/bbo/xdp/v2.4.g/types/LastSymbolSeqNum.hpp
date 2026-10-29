#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// The last symbol sequence number sent for this symbol. The refresh is the symbol state of this symbol as of this symbol sequence number.
struct LastSymbolSeqNum {

    static constexpr const char* name = "Last Symbol Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastSymbolSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastSymbolSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of LastSymbolSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
