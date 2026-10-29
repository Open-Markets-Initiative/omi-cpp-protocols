#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Board Lot Size in Shares
struct BoardLotSize {

    static constexpr const char* name = "Board Lot Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BoardLotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BoardLotSize(const std::uint32_t value)
     : value{ value } {}

    // get value of BoardLotSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
