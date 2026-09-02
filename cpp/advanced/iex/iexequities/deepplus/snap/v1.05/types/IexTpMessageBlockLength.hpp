#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

// iex_tp_message_block_length
struct iex_tp_message_block_length {

    static constexpr const char* name = "iex_tp_message_block_length";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr iex_tp_message_block_length()
     : value{ 0 } {}

    constexpr iex_tp_message_block_length(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
