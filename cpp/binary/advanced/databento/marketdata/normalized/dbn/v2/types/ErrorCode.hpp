#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// error_code
struct error_code {

    enum class enum_type : std::uint8_t {
        auth_failed = 1,
        api_key_deactivated = 2,
        connection_limit_exceeded = 3,
        symbol_resolution_failed = 4,
        invalid_subscription = 5,
        internal_error = 6,
        skipped_records_after_slow_reading = 7,
        replay_data_aged_out = 8,
        unset = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Api Key Deactivated", enum_type::api_key_deactivated},
        {"Auth Failed", enum_type::auth_failed},
        {"Connection Limit Exceeded", enum_type::connection_limit_exceeded},
        {"Internal Error", enum_type::internal_error},
        {"Invalid Subscription", enum_type::invalid_subscription},
        {"Replay Data Aged Out", enum_type::replay_data_aged_out},
        {"Skipped Records After Slow Reading", enum_type::skipped_records_after_slow_reading},
        {"Symbol Resolution Failed", enum_type::symbol_resolution_failed},
        {"Unset", enum_type::unset}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::auth_failed: return "Auth Failed";
            case enum_type::api_key_deactivated: return "Api Key Deactivated";
            case enum_type::connection_limit_exceeded: return "Connection Limit Exceeded";
            case enum_type::symbol_resolution_failed: return "Symbol Resolution Failed";
            case enum_type::invalid_subscription: return "Invalid Subscription";
            case enum_type::internal_error: return "Internal Error";
            case enum_type::skipped_records_after_slow_reading: return "Skipped Records After Slow Reading";
            case enum_type::replay_data_aged_out: return "Replay Data Aged Out";
            case enum_type::unset: return "Unset";
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

    static constexpr const char* name = "error_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<error_code::enum_type>;
    using storage_type = result_type;

    constexpr error_code()
     : value{ enum_type{} } {}

    constexpr error_code(enum_type v)
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
            set(enum_type::unset);
    }

  protected:
    enum_type value;
};
}
