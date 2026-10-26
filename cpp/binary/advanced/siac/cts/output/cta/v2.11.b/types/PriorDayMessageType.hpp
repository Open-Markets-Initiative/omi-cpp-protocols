#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// prior_day_message_type
struct prior_day_message_type {

    enum class enum_type : char {
        prior_day_trade_correction = 'C',
        fractional_prior_day_trade_correction = 'O',
        prior_day_trade = 'T',
        fractional_prior_day_trade = 'R',
        prior_day_trade_cancel_error = 'X',
        fractional_prior_day_trade_cancel_error = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Fractional Prior Day Trade", enum_type::fractional_prior_day_trade},
        {"Fractional Prior Day Trade Cancel Error", enum_type::fractional_prior_day_trade_cancel_error},
        {"Fractional Prior Day Trade Correction", enum_type::fractional_prior_day_trade_correction},
        {"Prior Day Trade", enum_type::prior_day_trade},
        {"Prior Day Trade Cancel Error", enum_type::prior_day_trade_cancel_error},
        {"Prior Day Trade Correction", enum_type::prior_day_trade_correction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::prior_day_trade_correction: return "Prior Day Trade Correction";
            case enum_type::fractional_prior_day_trade_correction: return "Fractional Prior Day Trade Correction";
            case enum_type::prior_day_trade: return "Prior Day Trade";
            case enum_type::fractional_prior_day_trade: return "Fractional Prior Day Trade";
            case enum_type::prior_day_trade_cancel_error: return "Prior Day Trade Cancel Error";
            case enum_type::fractional_prior_day_trade_cancel_error: return "Fractional Prior Day Trade Cancel Error";
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
            set(enum_type::fractional_prior_day_trade_cancel_error);
    }

  protected:
    enum_type value;
};
}
