#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Market Data entry price
struct MdEntryPx {

    static constexpr const char* name = "Md Entry Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 7;
    static constexpr double denominator = 10000000;
    using type = std::int64_t;

    // default constructor
    constexpr MdEntryPx()
     : value{ 0 } {}

    // constructor for MdEntryPx field
    constexpr explicit MdEntryPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdEntryPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdEntryPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
