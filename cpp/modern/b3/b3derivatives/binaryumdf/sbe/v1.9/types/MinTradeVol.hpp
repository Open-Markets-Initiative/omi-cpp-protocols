#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// minTradeVol
struct MinTradeVol {

    static constexpr const char* name = "Min Trade Vol";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr MinTradeVol()
     : value{ 0 } {}

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
