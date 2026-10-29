#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// Length of free format text field defined by client.
struct MemoLength {

    static constexpr auto name = "Memo Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MemoLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MemoLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of MemoLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
