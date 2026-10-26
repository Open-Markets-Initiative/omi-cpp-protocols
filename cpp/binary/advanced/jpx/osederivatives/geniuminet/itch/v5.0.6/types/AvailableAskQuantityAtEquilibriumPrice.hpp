#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// available_ask_quantity_at_equilibrium_price
struct available_ask_quantity_at_equilibrium_price {

    static constexpr const char* name = "available_ask_quantity_at_equilibrium_price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr available_ask_quantity_at_equilibrium_price()
     : value{ 0 } {}

    available_ask_quantity_at_equilibrium_price(std::uint64_t v)
     : value{ static_cast<std::uint64_t>(__builtin_bswap64(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint64_t>(__builtin_bswap64(value))};
    }

    void set(std::uint64_t v) {
        value = __builtin_bswap64(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
