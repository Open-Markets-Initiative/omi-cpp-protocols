#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

// price_tick_size_table_id
struct price_tick_size_table_id {

    static constexpr const char* name = "price_tick_size_table_id";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr price_tick_size_table_id()
     : value{ 0 } {}

    price_tick_size_table_id(std::uint32_t v)
     : value{ static_cast<std::uint32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint32_t>(__builtin_bswap32(value))};
    }

    void set(std::uint32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
