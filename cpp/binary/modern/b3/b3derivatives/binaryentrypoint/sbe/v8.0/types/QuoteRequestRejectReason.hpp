#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quoteRequestRejectReason
struct QuoteRequestRejectReason {

    static constexpr const char* name = "Quote Request Reject Reason";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr QuoteRequestRejectReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteRequestRejectReason(const std::uint32_t value)
     : value{ value } {}

    // get value of QuoteRequestRejectReason field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
