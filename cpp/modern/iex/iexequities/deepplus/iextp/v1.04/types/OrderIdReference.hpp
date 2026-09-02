#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_04 {

// Order ID of the referenced order
struct OrderIdReference {

    static constexpr const char* name = "Order Id Reference";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderIdReference()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderIdReference(const std::uint64_t value)
     : value{ value } {}

    // get value of OrderIdReference field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
