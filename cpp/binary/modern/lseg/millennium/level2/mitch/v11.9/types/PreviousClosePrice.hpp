#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Previous Close Price of instrument
struct PreviousClosePrice {

    static constexpr const char* name = "Previous Close Price";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr PreviousClosePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PreviousClosePrice(const std::int64_t value)
     : value{ value } {}

    // get value of PreviousClosePrice field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
