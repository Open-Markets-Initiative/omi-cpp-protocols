#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {


// Book Type
struct BookType {

    static constexpr auto name = "Book Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr BookType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BookType(const std::uint8_t &value)
     : value{ value } {}

    // get value of BookType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
