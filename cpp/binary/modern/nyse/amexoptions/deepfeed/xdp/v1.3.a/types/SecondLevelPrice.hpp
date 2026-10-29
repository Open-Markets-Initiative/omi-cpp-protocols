#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Price of second buy level
struct SecondLevelPrice {

    static constexpr const char* name = "Second Level Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr SecondLevelPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondLevelPrice(const std::int32_t value)
     : value{ value } {}

    // get value of SecondLevelPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
