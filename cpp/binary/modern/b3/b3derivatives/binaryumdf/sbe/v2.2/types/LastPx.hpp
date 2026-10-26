#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// lastPx
struct LastPx {

    static constexpr const char* name = "Last Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr LastPx()
     : value{ 0 } {}

    // constructor for LastPx field
    constexpr explicit LastPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LastPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LastPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
