#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


// This tag is required to interpret the value in tag 1231-MinLotSize
struct LotType {

    static constexpr auto name = "Lot Type";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr LotType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LotType(const std::int8_t &value)
     : value{ value } {}

    // get value of LotType field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
