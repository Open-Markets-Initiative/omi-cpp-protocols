#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// mDEntryInterestRate
struct MdEntryInterestRate {

    static constexpr const char* name = "Md Entry Interest Rate";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = 0;

    // default constructor
    constexpr MdEntryInterestRate()
     : value{ 0 } {}

    // constructor for MdEntryInterestRate field
    constexpr explicit MdEntryInterestRate(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MdEntryInterestRate field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MdEntryInterestRate field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
