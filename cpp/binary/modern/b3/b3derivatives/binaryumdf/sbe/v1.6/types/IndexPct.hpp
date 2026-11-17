// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: types/IndexPct.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// Required if this is an equity index instrument. Indicates the percentage that this underlying composes the index.
struct IndexPct {

    static constexpr const char* name = "Index Pct";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr IndexPct()
     : value{ no_value } {}

    // constructor for IndexPct field
    constexpr explicit IndexPct(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of IndexPct field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of IndexPct field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
