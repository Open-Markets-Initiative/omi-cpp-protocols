#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// mDEntryPx
struct MdCorporatePrice {

    static constexpr const char* name = "Md Corporate Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr MdCorporatePrice()
     : value{ 0 } {}

    // constructor for MdCorporatePrice field
    constexpr explicit MdCorporatePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdCorporatePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdCorporatePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
