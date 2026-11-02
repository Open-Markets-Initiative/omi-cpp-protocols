#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// clOrdID
struct ClordidOptional {

    static constexpr const char* name = "ClOrdId Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr ClordidOptional()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit ClordidOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of ClordidOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
