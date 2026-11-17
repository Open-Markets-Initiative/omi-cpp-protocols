// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: types/MinTradeVol.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// minTradeVol
struct MinTradeVol {

    static constexpr const char* name = "Min Trade Vol";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor: the null the model states, where it states one
    constexpr MinTradeVol()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MinTradeVol(const std::int64_t value)
     : value{ value } {}

    // get value of MinTradeVol field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
