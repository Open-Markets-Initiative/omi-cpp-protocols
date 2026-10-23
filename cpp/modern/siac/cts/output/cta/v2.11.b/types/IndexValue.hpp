#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents a statistical composite that measures changes in the economy or in financial markets. Has implied 6 decimal places
struct IndexValue {

    static constexpr const char* name = "Index Value";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr IndexValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndexValue(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get value of IndexValue field
    [[nodiscard]] std::int64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int64_t value;
};
}
