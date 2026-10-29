#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// auction_status
struct auction_status {

    enum class enum_type : std::uint8_t {
        will_run_open_close = 0,
        will_run_interest = 1,
        will_not_run_imbalance = 2,
        will_not_run_transition_to_closing = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Will Not Run Imbalance", enum_type::will_not_run_imbalance},
        {"Will Not Run Transition To Closing", enum_type::will_not_run_transition_to_closing},
        {"Will Run Interest", enum_type::will_run_interest},
        {"Will Run Open Close", enum_type::will_run_open_close}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::will_run_open_close: return "Will Run Open Close";
            case enum_type::will_run_interest: return "Will Run Interest";
            case enum_type::will_not_run_imbalance: return "Will Not Run Imbalance";
            case enum_type::will_not_run_transition_to_closing: return "Will Not Run Transition To Closing";
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

    static constexpr const char* name = "auction_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_status::enum_type>;
    using storage_type = result_type;

    constexpr auction_status()
     : value{ enum_type{} } {}

    constexpr auction_status(enum_type v)
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
            set(enum_type::will_not_run_transition_to_closing);
    }

  protected:
    enum_type value;
};
}
