#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// New limit price of the order.
struct NewPrice {

    static constexpr const char* name = "New Price";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr NewPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewPrice(const std::int64_t value)
     : value{ value } {}

    // get value of NewPrice field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
