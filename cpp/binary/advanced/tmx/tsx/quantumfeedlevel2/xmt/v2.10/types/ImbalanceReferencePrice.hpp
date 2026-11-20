// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/ImbalanceReferencePrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// imbalance_reference_price
struct imbalance_reference_price {

    static constexpr const char* name = "imbalance_reference_price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0ULL;
    static constexpr int exponent = -6;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr imbalance_reference_price()
     : value{ null_value } {}

    constexpr imbalance_reference_price(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint64_t value;
};
}
