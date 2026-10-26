#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// The theoretical quantity of this underlying composing the index. This tag is only used for index instruments.
struct IndexTheoreticalQty {

    static constexpr const char* name = "Index Theoretical Qty";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr IndexTheoreticalQty()
     : value{ 0 } {}

    // constructor for IndexTheoreticalQty field
    constexpr explicit IndexTheoreticalQty(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of IndexTheoreticalQty field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of IndexTheoreticalQty field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
