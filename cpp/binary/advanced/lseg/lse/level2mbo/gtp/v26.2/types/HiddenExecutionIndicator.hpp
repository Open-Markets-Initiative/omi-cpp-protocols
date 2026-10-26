#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// hidden_execution_indicator
struct hidden_execution_indicator {

    enum class enum_type : std::uint8_t {
        na = 0,
        visible = 1,
        hidden = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Hidden", enum_type::hidden},
        {"Na", enum_type::na},
        {"Visible", enum_type::visible}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::na: return "Na";
            case enum_type::visible: return "Visible";
            case enum_type::hidden: return "Hidden";
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

    static constexpr const char* name = "hidden_execution_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<hidden_execution_indicator::enum_type>;
    using storage_type = result_type;

    constexpr hidden_execution_indicator()
     : value{ enum_type{} } {}

    constexpr hidden_execution_indicator(enum_type v)
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
            set(enum_type::hidden);
    }

  protected:
    enum_type value;
};
}
