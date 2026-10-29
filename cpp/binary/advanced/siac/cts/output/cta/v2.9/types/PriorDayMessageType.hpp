#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// prior_day_message_type
struct prior_day_message_type {

    enum class enum_type : char {
        prior_day_trade_correction_message = 'C',
        prior_day_trade_message = 'T',
        prior_day_trade_cancel_error_message = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Prior Day Trade Cancel Error Message", enum_type::prior_day_trade_cancel_error_message},
        {"Prior Day Trade Correction Message", enum_type::prior_day_trade_correction_message},
        {"Prior Day Trade Message", enum_type::prior_day_trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::prior_day_trade_correction_message: return "Prior Day Trade Correction Message";
            case enum_type::prior_day_trade_message: return "Prior Day Trade Message";
            case enum_type::prior_day_trade_cancel_error_message: return "Prior Day Trade Cancel Error Message";
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

    static constexpr const char* name = "prior_day_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<prior_day_message_type::enum_type>;
    using storage_type = result_type;

    constexpr prior_day_message_type()
     : value{ enum_type{} } {}

    constexpr prior_day_message_type(enum_type v)
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
            set(enum_type::prior_day_trade_cancel_error_message);
    }

  protected:
    enum_type value;
};
}
