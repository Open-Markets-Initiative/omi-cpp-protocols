#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Quantity bought or sold on this last fill
struct LastQty {

    static constexpr const char* name = "Last Qty";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LastQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastQty(const std::int32_t value)
     : value{ value } {}

    // get value of LastQty field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
