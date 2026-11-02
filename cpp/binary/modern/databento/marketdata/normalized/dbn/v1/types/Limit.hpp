#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The maximum number of records to return; no value when unlimited
struct Limit {

    static constexpr const char* name = "Limit";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr Limit()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit Limit(const std::uint64_t value)
     : value{ value } {}

    // get value of Limit field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
