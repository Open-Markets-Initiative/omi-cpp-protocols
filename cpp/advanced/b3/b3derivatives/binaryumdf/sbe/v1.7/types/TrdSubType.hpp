#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// trd_sub_type
struct trd_sub_type {

    enum class enum_type : std::uint8_t {
        multi_asset_trade = 101,
        leg_trade = 102,
        midpoint_trade = 103,
        block_book_trade = 104,
        rf_trade = 105,
        rlp_trade = 106,
        tac_trade = 107,
        taa_trade = 108,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Block Book Trade", enum_type::block_book_trade},
        {"Leg Trade", enum_type::leg_trade},
        {"Midpoint Trade", enum_type::midpoint_trade},
        {"Multi Asset Trade", enum_type::multi_asset_trade},
        {"No Value", enum_type::no_value},
        {"Rf Trade", enum_type::rf_trade},
        {"Rlp Trade", enum_type::rlp_trade},
        {"Taa Trade", enum_type::taa_trade},
        {"Tac Trade", enum_type::tac_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::multi_asset_trade: return "Multi Asset Trade";
            case enum_type::leg_trade: return "Leg Trade";
            case enum_type::midpoint_trade: return "Midpoint Trade";
            case enum_type::block_book_trade: return "Block Book Trade";
            case enum_type::rf_trade: return "Rf Trade";
            case enum_type::rlp_trade: return "Rlp Trade";
            case enum_type::tac_trade: return "Tac Trade";
            case enum_type::taa_trade: return "Taa Trade";
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

    static constexpr const char* name = "trd_sub_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trd_sub_type::enum_type>;
    using storage_type = result_type;

    constexpr trd_sub_type()
     : value{ enum_type::multi_asset_trade } {}

    constexpr trd_sub_type(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
