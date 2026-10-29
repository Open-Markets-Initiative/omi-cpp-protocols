#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {


// Identifies the number of manual or automatic extensions the applicable auction has received
struct NumberOfExtensions {

    static constexpr auto name = "Number Of Extensions";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfExtensions()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfExtensions(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfExtensions field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
