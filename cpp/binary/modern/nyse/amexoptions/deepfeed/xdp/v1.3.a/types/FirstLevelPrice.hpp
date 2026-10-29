#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Price of first buy level
struct FirstLevelPrice {

    static constexpr const char* name = "First Level Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr FirstLevelPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirstLevelPrice(const std::int32_t value)
     : value{ value } {}

    // get value of FirstLevelPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
