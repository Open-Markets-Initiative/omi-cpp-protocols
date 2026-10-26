#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// newsSource
struct NewsSource {

    static constexpr auto name = "News Source";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NewsSource()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewsSource(const std::uint8_t &value)
     : value{ value } {}

    // get value of NewsSource field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
