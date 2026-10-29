#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quoteID
struct QuoteId {

    static constexpr const char* name = "Quote Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr QuoteId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteId(const std::uint64_t value)
     : value{ value } {}

    // get value of QuoteId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
