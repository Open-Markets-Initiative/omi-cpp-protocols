#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_04 {

// IEX Generated Identifier
struct TradeId {

    static constexpr const char* name = "Trade Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeId(const std::uint64_t value)
     : value{ value } {}

    // get value of TradeId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
