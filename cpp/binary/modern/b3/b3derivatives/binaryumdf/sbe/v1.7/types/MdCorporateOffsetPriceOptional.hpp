// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: types/MdCorporateOffsetPriceOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// mDEntryPx
struct MdCorporateOffsetPriceOptional {

    static constexpr const char* name = "Md Corporate Offset Price Optional";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor: the null the model states, where it states one
    constexpr MdCorporateOffsetPriceOptional()
     : value{ no_value } {}

    // constructor for MdCorporateOffsetPriceOptional field
    constexpr explicit MdCorporateOffsetPriceOptional(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdCorporateOffsetPriceOptional field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does MdCorporateOffsetPriceOptional hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of MdCorporateOffsetPriceOptional field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
