#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// mass_cancel_restatement_reason
struct mass_cancel_restatement_reason {

    enum class enum_type : std::uint8_t {
        order_mass_action_from_client_request = 202,
        mass_cancel_order_due_to_operational_error_request = 207,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Mass Cancel Order Due To Operational Error Request", enum_type::mass_cancel_order_due_to_operational_error_request},
        {"No Value", enum_type::no_value},
        {"Order Mass Action From Client Request", enum_type::order_mass_action_from_client_request}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::order_mass_action_from_client_request: return "Order Mass Action From Client Request";
            case enum_type::mass_cancel_order_due_to_operational_error_request: return "Mass Cancel Order Due To Operational Error Request";
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

    static constexpr const char* name = "mass_cancel_restatement_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<mass_cancel_restatement_reason::enum_type>;
    using storage_type = result_type;

    constexpr mass_cancel_restatement_reason()
     : value{ enum_type{} } {}

    constexpr mass_cancel_restatement_reason(enum_type v)
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
