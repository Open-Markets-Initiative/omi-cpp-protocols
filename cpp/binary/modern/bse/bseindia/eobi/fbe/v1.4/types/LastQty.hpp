#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// The potential matchable quantity for the auction.
struct LastQty {

    static constexpr const char* name = "Last Qty";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr LastQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastQty(const std::int64_t value)
     : value{ value } {}

    // get value of LastQty field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
