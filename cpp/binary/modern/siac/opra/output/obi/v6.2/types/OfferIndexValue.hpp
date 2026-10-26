#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// The Offer Index Value represents the value of the index’s calculation formula using the current Offer values of the component securities.
struct OfferIndexValue {

    static constexpr const char* name = "Offer Index Value";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr OfferIndexValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferIndexValue(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OfferIndexValue field
    [[nodiscard]] std::int64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int64_t value;
};
}
