#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// workup_trading_status
struct workup_trading_status {

    enum class enum_type : std::uint8_t {
        ready_to_trade = 17,
        not_available_for_trading = 18,
        private_workup = 201,
        public_workup = 202
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Not Available For Trading", enum_type::not_available_for_trading},
        {"Private Workup", enum_type::private_workup},
        {"Public Workup", enum_type::public_workup},
        {"Ready To Trade", enum_type::ready_to_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::ready_to_trade: return "Ready To Trade";
            case enum_type::not_available_for_trading: return "Not Available For Trading";
            case enum_type::private_workup: return "Private Workup";
            case enum_type::public_workup: return "Public Workup";
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

    static constexpr const char* name = "workup_trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<workup_trading_status::enum_type>;
    using storage_type = result_type;

    constexpr workup_trading_status()
     : value{ enum_type{} } {}

    constexpr workup_trading_status(enum_type v)
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
            set(enum_type::public_workup);
    }

  protected:
    enum_type value;
};
}
