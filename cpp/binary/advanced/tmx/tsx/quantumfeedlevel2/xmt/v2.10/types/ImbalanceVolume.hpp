// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/ImbalanceVolume.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// imbalance_volume
struct imbalance_volume {

    static constexpr const char* name = "imbalance_volume";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::uint32_t null_value = 0;

    using result_type = std::optional<std::uint32_t>;
    using storage_type = result_type;

    constexpr imbalance_volume()
     : value{ null_value } {}

    constexpr imbalance_volume(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint32_t v) {
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
    std::uint32_t value;
};
}
