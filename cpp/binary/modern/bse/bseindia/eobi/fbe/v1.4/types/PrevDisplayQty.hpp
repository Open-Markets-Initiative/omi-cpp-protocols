#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Previous display quantity
struct PrevDisplayQty {

    static constexpr const char* name = "Prev Display Qty";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr PrevDisplayQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrevDisplayQty(const std::int64_t value)
     : value{ value } {}

    // get value of PrevDisplayQty field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
