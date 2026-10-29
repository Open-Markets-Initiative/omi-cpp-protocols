#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// last_seq_num
struct last_seq_num {

    static constexpr const char* name = "last_seq_num";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr last_seq_num()
     : value{ 0 } {}

    constexpr last_seq_num(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
