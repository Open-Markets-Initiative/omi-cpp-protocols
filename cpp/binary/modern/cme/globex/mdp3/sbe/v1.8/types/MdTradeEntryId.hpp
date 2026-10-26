#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Market Data Trade entry ID
struct MdTradeEntryId {

    static constexpr const char* name = "Md Trade Entry Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 4294967295;

    // default constructor
    constexpr MdTradeEntryId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdTradeEntryId(const std::uint32_t value)
     : value{ value } {}

    // get value of MdTradeEntryId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
