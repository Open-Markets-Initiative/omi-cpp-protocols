#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// totNumOffers
struct TotNumOffers {

    static constexpr const char* name = "Tot Num Offers";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotNumOffers()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNumOffers(const std::uint32_t value)
     : value{ value } {}

    // get value of TotNumOffers field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
