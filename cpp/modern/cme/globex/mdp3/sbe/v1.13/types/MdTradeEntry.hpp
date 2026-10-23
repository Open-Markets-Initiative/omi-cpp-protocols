#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Market Data Trade Entry ID
struct MdTradeEntry {

    static constexpr const char* name = "Md Trade Entry";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MdTradeEntry()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdTradeEntry(const std::uint32_t value)
     : value{ value } {}

    // get value of MdTradeEntry field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
