#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Identifies the Sale Condition Category level associated with a trade
struct SaleConditionCategory {

    static constexpr auto name = "Sale Condition Category";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SaleConditionCategory()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SaleConditionCategory(const char &value)
     : value{ value } {}

    // get value of SaleConditionCategory field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
