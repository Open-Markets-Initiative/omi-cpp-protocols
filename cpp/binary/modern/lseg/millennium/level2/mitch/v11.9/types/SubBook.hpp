#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {


// Sub Book
struct SubBook {

    static constexpr auto name = "Sub Book";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SubBook()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SubBook(const std::uint8_t &value)
     : value{ value } {}

    // get value of SubBook field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
