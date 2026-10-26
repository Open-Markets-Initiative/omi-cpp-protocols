#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Reserved for future use. Ignore any content.
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
