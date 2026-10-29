#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {

// Identifies the daily established drop level value (trigger value) associated with each Decline Level 7%
struct MwcbLevel1 {

    static constexpr const char* name = "Mwcb Level 1";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr MwcbLevel1()
     : value{ 0 } {}

    // constructor for MwcbLevel1 field
    constexpr explicit MwcbLevel1(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of MwcbLevel1 field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of MwcbLevel1 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
