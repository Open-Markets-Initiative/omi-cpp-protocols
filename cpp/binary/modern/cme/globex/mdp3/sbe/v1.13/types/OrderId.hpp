#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Unique Order ID
struct OrderId {

    static constexpr const char* name = "Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderId(const std::uint64_t value)
     : value{ value } {}

    // get value of OrderId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
