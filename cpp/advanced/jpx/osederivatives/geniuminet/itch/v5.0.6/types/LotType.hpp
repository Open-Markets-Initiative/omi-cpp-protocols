#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// lot_type
struct lot_type {

    enum class enum_type : std::uint8_t {
        undefined = 0,
        odd_lot = 1,
        round_lot = 2,
        block_lot = 3,
        all_or_none_lot = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"All Or None Lot", enum_type::all_or_none_lot},
        {"Block Lot", enum_type::block_lot},
        {"Odd Lot", enum_type::odd_lot},
        {"Round Lot", enum_type::round_lot},
        {"Undefined", enum_type::undefined}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::undefined: return "Undefined";
            case enum_type::odd_lot: return "Odd Lot";
            case enum_type::round_lot: return "Round Lot";
            case enum_type::block_lot: return "Block Lot";
            case enum_type::all_or_none_lot: return "All Or None Lot";
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
     : value{ enum_type{} } {}

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
            set(enum_type::all_or_none_lot);
    }

  protected:
    enum_type value;
};
}
