#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Market Data Trade entry ID
struct MdTradeEntryOptional {

    static constexpr const char* name = "Md Trade Entry Optional";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 4294967295;

    // default constructor
    constexpr MdTradeEntryOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdTradeEntryOptional(const std::uint32_t value)
     : value{ value } {}

    // get value of MdTradeEntryOptional field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
