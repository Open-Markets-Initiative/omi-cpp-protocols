#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Denotes the sale condition associated with a trade
struct SaleCondition1 {

    static constexpr auto name = "Sale Condition 1";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SaleCondition1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SaleCondition1(const char &value)
     : value{ value } {}

    // get value of SaleCondition1 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
