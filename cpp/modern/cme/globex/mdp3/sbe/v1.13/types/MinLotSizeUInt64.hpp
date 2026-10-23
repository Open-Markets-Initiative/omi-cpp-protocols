#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// For FX instruments in the repeating group with Tag 1093-LotType=2, Tag 1231-MinLotSize provides a Regular Amount - a default order size on the Workstation screen. With tag 1093-LotType= 5, Tag 1231-MinLotSize value represents standard min order qty increment. With tag 1093-LotType=6 tag 1231-MinLotSize contains SizePriorityQty for instruments trading with Match Algorithm = P (Size Priority)
struct MinLotSizeUInt64 {

    static constexpr const char* name = "Min Lot Size u Int 64";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MinLotSizeUInt64()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinLotSizeUInt64(const std::uint64_t value)
     : value{ value } {}

    // get value of MinLotSizeUInt64 field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
