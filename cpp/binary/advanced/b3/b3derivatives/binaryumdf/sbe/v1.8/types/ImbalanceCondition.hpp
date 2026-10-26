#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// imbalance_condition
struct imbalance_condition {

    using type = uint16_t;

    static constexpr type imbalance_more_buyers = type{1} << 8;
    static constexpr type imbalance_more_sellers = type{1} << 9;

    static constexpr const char* name = "imbalance_condition";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<uint16_t>;
    using storage_type = result_type;

    constexpr imbalance_condition()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint16_t v) {
        value = v;
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(v.value());
        else
            set(type{0});
    }

    [[nodiscard]] constexpr bool has(type bit) const { return (value & bit) != 0; }
    constexpr void set(type bit, bool enabled) { if (enabled) value |= bit; else value &= static_cast<type>(~bit); }

    [[nodiscard]] constexpr bool has_imbalance_more_buyers() const { return has(imbalance_more_buyers); }
    [[nodiscard]] constexpr bool has_imbalance_more_sellers() const { return has(imbalance_more_sellers); }

    constexpr void set_imbalance_more_buyers(bool v) { set(imbalance_more_buyers, v); }
    constexpr void set_imbalance_more_sellers(bool v) { set(imbalance_more_sellers, v); }

  protected:
    type value;
};
}
