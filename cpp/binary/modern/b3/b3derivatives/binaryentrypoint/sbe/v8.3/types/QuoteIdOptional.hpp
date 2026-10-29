#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// quoteID
struct QuoteIdOptional {

    static constexpr const char* name = "Quote Id Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr QuoteIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteIdOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of QuoteIdOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
