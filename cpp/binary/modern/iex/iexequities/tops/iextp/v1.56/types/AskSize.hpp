#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {

// Aggregate quoted best ask size
struct AskSize {

    static constexpr const char* name = "Ask Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSize(const std::uint32_t value)
     : value{ value } {}

    // get value of AskSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
