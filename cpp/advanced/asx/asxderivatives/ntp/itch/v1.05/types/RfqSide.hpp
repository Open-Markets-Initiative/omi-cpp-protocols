#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// rfq_side
struct rfq_side {

    enum class enum_type : char {
        two_sided_quote = 'T',
        bid_quote = 'B',
        ask_quote = 'S',
        crossing = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Ask Quote", enum_type::ask_quote},
        {"Bid Quote", enum_type::bid_quote},
        {"Crossing", enum_type::crossing},
        {"Two Sided Quote", enum_type::two_sided_quote}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::two_sided_quote: return "Two Sided Quote";
            case enum_type::bid_quote: return "Bid Quote";
            case enum_type::ask_quote: return "Ask Quote";
            case enum_type::crossing: return "Crossing";
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

    static constexpr const char* name = "rfq_side";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<rfq_side::enum_type>;
    using storage_type = result_type;

    constexpr rfq_side()
     : value{ enum_type{} } {}

    constexpr rfq_side(enum_type v)
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
            set(enum_type::crossing);
    }

  protected:
    enum_type value;
};
}
