#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Indicating the potential Auction price for a crossed order book.
struct LastPx {

    static constexpr const char* name = "Last Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr LastPx()
     : value{ 0 } {}

    // constructor for LastPx field
    constexpr explicit LastPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LastPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LastPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
