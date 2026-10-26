#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Order ID
struct OrderIdOptional {

    static constexpr const char* name = "Order Id Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr OrderIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderIdOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of OrderIdOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
