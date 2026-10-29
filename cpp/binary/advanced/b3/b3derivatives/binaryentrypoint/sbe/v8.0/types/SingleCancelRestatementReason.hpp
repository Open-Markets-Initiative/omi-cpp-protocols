#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// single_cancel_restatement_reason
struct single_cancel_restatement_reason {

    enum class enum_type : std::uint8_t {
        cancel_order_due_to_operational_error = 203,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Cancel Order Due To Operational Error", enum_type::cancel_order_due_to_operational_error},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cancel_order_due_to_operational_error: return "Cancel Order Due To Operational Error";
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

    static constexpr const char* name = "single_cancel_restatement_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<single_cancel_restatement_reason::enum_type>;
    using storage_type = result_type;

    constexpr single_cancel_restatement_reason()
     : value{ enum_type{} } {}

    constexpr single_cancel_restatement_reason(enum_type v)
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
