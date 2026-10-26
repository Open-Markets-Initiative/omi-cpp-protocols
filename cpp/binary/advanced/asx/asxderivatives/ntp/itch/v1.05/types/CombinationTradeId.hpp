#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// combination_trade_id
struct combination_trade_id {

    static constexpr const char* name = "combination_trade_id";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr combination_trade_id()
     : value{ 0 } {}

    combination_trade_id(std::uint64_t v)
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
