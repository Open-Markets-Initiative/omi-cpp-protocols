// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: types/PriceBandType.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// price_band_type
struct price_band_type {

    enum class enum_type : std::uint8_t {
        hard_limit = 1,
        auction_limits = 2,
        rejection_band = 3,
        static_limits = 4,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Auction Limits", enum_type::auction_limits},
        {"Hard Limit", enum_type::hard_limit},
        {"No Value", enum_type::no_value},
        {"Rejection Band", enum_type::rejection_band},
        {"Static Limits", enum_type::static_limits}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::hard_limit: return "Hard Limit";
            case enum_type::auction_limits: return "Auction Limits";
            case enum_type::rejection_band: return "Rejection Band";
            case enum_type::static_limits: return "Static Limits";
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

    static constexpr const char* name = "price_band_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr enum_type null_value = static_cast<enum_type>(255);

    using result_type = std::optional<price_band_type::enum_type>;
    using storage_type = result_type;

    constexpr price_band_type()
     : value{ static_cast<enum_type>(255) } {}

    constexpr price_band_type(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        const enum_type held = value;
        return held == null_value ? std::nullopt : result_type{held};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        set(null_value);
    }

  protected:
    enum_type value;
};
}
