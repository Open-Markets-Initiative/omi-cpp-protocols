#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The data record schema; no value for a file of mixed schemas
struct Schema {

    static constexpr const char* name = "Schema";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor: the null the model states, where it states one
    constexpr Schema()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit Schema(const std::uint16_t value)
     : value{ value } {}

    // get value of Schema field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
