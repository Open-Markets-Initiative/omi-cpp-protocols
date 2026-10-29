#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// trading_session_sub_id
struct trading_session_sub_id {

    enum class enum_type : std::uint8_t {
        pre_trading = 1,
        trading = 3,
        closing = 4,
        post_trading = 5,
        post_closing = 6,
        quiescent = 7
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Closing", enum_type::closing},
        {"Post Closing", enum_type::post_closing},
        {"Post Trading", enum_type::post_trading},
        {"Pre Trading", enum_type::pre_trading},
        {"Quiescent", enum_type::quiescent},
        {"Trading", enum_type::trading}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::pre_trading: return "Pre Trading";
            case enum_type::trading: return "Trading";
            case enum_type::closing: return "Closing";
            case enum_type::post_trading: return "Post Trading";
            case enum_type::post_closing: return "Post Closing";
            case enum_type::quiescent: return "Quiescent";
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

    static constexpr const char* name = "trading_session_sub_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_session_sub_id::enum_type>;
    using storage_type = result_type;

    constexpr trading_session_sub_id()
     : value{ enum_type{} } {}

    constexpr trading_session_sub_id(enum_type v)
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
            set(enum_type::quiescent);
    }

  protected:
    enum_type value;
};
}
