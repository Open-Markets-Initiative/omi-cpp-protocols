#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Total number of partial lit executions
struct NumberOfLitExecutions {

    static constexpr const char* name = "Number Of Lit Executions";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr NumberOfLitExecutions()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfLitExecutions(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of NumberOfLitExecutions field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
