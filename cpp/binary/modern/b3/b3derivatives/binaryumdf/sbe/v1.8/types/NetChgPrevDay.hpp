#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// netChgPrevDay
struct NetChgPrevDay {

    static constexpr const char* name = "Net Chg Prev Day";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr NetChgPrevDay()
     : value{ 0 } {}

    // constructor for NetChgPrevDay field
    constexpr explicit NetChgPrevDay(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of NetChgPrevDay field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of NetChgPrevDay field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
