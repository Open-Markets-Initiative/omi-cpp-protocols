#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// crossed_indicator
struct crossed_indicator {

    enum class enum_type : std::uint16_t {
        structured_transaction = 1001,
        operational_error = 1002,
        twap_vwap = 1003,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"No Value", enum_type::no_value},
        {"Operational Error", enum_type::operational_error},
        {"Structured Transaction", enum_type::structured_transaction},
        {"Twap Vwap", enum_type::twap_vwap}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::structured_transaction: return "Structured Transaction";
            case enum_type::operational_error: return "Operational Error";
            case enum_type::twap_vwap: return "Twap Vwap";
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

    static constexpr const char* name = "crossed_indicator";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<crossed_indicator::enum_type>;
    using storage_type = result_type;

    constexpr crossed_indicator()
     : value{ enum_type{} } {}

    constexpr crossed_indicator(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
