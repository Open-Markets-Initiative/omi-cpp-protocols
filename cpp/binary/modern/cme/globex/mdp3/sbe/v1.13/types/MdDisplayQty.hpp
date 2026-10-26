#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Visible order qty
struct MdDisplayQty {

    static constexpr const char* name = "Md Display Qty";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MdDisplayQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdDisplayQty(const std::int32_t value)
     : value{ value } {}

    // get value of MdDisplayQty field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
