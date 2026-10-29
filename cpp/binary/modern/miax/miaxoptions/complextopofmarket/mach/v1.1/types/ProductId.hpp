#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// MIAX Product ID mapped to a given option. It is assigned per trading session and is valid for that session.
struct ProductId {

    static constexpr const char* name = "Product Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ProductId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProductId(const std::uint32_t value)
     : value{ value } {}

    // get value of ProductId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
