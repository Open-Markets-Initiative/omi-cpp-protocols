#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// The Index Value represents a statistical composite that measures changes in the economy or in financial markets
struct IndexValue {

    static constexpr const char* name = "Index Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr IndexValue()
     : value{ 0 } {}

    // constructor for IndexValue field
    constexpr explicit IndexValue(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of IndexValue field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of IndexValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
