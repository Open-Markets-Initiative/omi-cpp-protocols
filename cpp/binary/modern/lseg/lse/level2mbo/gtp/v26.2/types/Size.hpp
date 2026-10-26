#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Displayed size of the order.
struct Size {

    static constexpr const char* name = "Size";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Size()
     : value{ 0 } {}

    // constructor for Size field
    constexpr explicit Size(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of Size field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of Size field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
