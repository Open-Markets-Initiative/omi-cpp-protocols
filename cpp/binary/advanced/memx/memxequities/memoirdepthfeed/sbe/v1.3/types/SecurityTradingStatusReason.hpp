#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// security_trading_status_reason
struct security_trading_status_reason {

    enum class enum_type : char {
        none = 'X',
        regulatory = 'R',
        administrative = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Administrative", enum_type::administrative},
        {"None", enum_type::none},
        {"Regulatory", enum_type::regulatory}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::regulatory: return "Regulatory";
            case enum_type::administrative: return "Administrative";
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

    static constexpr const char* name = "security_trading_status_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_trading_status_reason::enum_type>;
    using storage_type = result_type;

    constexpr security_trading_status_reason()
     : value{ enum_type{} } {}

    constexpr security_trading_status_reason(enum_type v)
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
            set(enum_type::administrative);
    }

  protected:
    enum_type value;
};
}
