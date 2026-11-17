// Databento.MarketData.Normalized.Dbn.v3: types/UnitOfMeasureQty.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The unit of measure qty, where every 1 unit corresponds to 1e-9
struct UnitOfMeasureQty {

    static constexpr const char* name = "Unit Of Measure Qty";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr UnitOfMeasureQty()
     : value{ no_value } {}

    // constructor for UnitOfMeasureQty field
    constexpr explicit UnitOfMeasureQty(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UnitOfMeasureQty field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of UnitOfMeasureQty field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
