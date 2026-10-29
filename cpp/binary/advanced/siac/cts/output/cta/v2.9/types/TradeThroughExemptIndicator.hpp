#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// trade_through_exempt_indicator
struct trade_through_exempt_indicator {

    enum class enum_type : char {
        not_a_trade_through_exemption = '0',
        trade_through_exemption = '1'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Not A Trade Through Exemption", enum_type::not_a_trade_through_exemption},
        {"Trade Through Exemption", enum_type::trade_through_exemption}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_a_trade_through_exemption: return "Not A Trade Through Exemption";
            case enum_type::trade_through_exemption: return "Trade Through Exemption";
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

    static constexpr const char* name = "trade_through_exempt_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_through_exempt_indicator::enum_type>;
    using storage_type = result_type;

    constexpr trade_through_exempt_indicator()
     : value{ enum_type{} } {}

    constexpr trade_through_exempt_indicator(enum_type v)
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
            set(enum_type::trade_through_exemption);
    }

  protected:
    enum_type value;
};
}
