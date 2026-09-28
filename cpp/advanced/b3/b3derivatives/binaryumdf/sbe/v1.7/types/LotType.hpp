#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// lot_type
struct lot_type {

    enum class enum_type : std::uint8_t {
        odd_lot = 1,
        round_lot = 2,
        block_lot = 3,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Block Lot", enum_type::block_lot},
        {"No Value", enum_type::no_value},
        {"Odd Lot", enum_type::odd_lot},
        {"Round Lot", enum_type::round_lot}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::odd_lot: return "Odd Lot";
            case enum_type::round_lot: return "Round Lot";
            case enum_type::block_lot: return "Block Lot";
            case enum_type::no_value: return "No Value";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "lot_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<lot_type::enum_type>;
    using storage_type = result_type;

    constexpr lot_type()
     : value{ enum_type::odd_lot } {}

    constexpr lot_type(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
