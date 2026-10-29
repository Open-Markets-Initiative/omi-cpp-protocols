#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Price of third buy level
struct ThirdLevelPrice {

    static constexpr const char* name = "Third Level Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr ThirdLevelPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ThirdLevelPrice(const std::int32_t value)
     : value{ value } {}

    // get value of ThirdLevelPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
