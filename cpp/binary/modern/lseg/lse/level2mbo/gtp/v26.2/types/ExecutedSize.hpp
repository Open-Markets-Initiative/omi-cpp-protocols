#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Total executed quantity.
struct ExecutedSize {

    static constexpr const char* name = "Executed Size";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ExecutedSize()
     : value{ 0 } {}

    // constructor for ExecutedSize field
    constexpr explicit ExecutedSize(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of ExecutedSize field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of ExecutedSize field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
