#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// market_maker_mode
struct market_maker_mode {

    enum class enum_type : char {
        normal = 'N',
        passive = 'P',
        syndicate = 'S',
        pre_syndicate = 'R',
        penalty = 'L'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Normal", enum_type::normal},
        {"Passive", enum_type::passive},
        {"Penalty", enum_type::penalty},
        {"Pre Syndicate", enum_type::pre_syndicate},
        {"Syndicate", enum_type::syndicate}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::normal: return "Normal";
            case enum_type::passive: return "Passive";
            case enum_type::syndicate: return "Syndicate";
            case enum_type::pre_syndicate: return "Pre Syndicate";
            case enum_type::penalty: return "Penalty";
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

    static constexpr const char* name = "market_maker_mode";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_maker_mode::enum_type>;
    using storage_type = result_type;

    constexpr market_maker_mode()
     : value{ enum_type::normal } {}

    constexpr market_maker_mode(enum_type v)
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
            set(enum_type::penalty);
    }

  protected:
    enum_type value;
};
}
