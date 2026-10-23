#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// market_state
struct market_state {

    enum class enum_type : std::uint8_t {
        pre_opening = 1,
        early_trading_session = 2,
        regular_trading_session = 3,
        late_trading_session = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Early Trading Session", enum_type::early_trading_session},
        {"Late Trading Session", enum_type::late_trading_session},
        {"Pre Opening", enum_type::pre_opening},
        {"Regular Trading Session", enum_type::regular_trading_session}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::pre_opening: return "Pre Opening";
            case enum_type::early_trading_session: return "Early Trading Session";
            case enum_type::regular_trading_session: return "Regular Trading Session";
            case enum_type::late_trading_session: return "Late Trading Session";
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

    static constexpr const char* name = "market_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_state::enum_type>;
    using storage_type = result_type;

    constexpr market_state()
     : value{ enum_type{} } {}

    constexpr market_state(enum_type v)
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
            set(enum_type::late_trading_session);
    }

  protected:
    enum_type value;
};
}
