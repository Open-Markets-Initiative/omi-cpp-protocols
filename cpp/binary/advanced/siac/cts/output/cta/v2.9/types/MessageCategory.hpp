#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// message_category
struct message_category {

    enum class enum_type : char {
        administrative = 'A',
        control = 'C',
        indices = 'I',
        market_status = 'M',
        prior_day = 'P',
        summary = 'S',
        trade = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Administrative", enum_type::administrative},
        {"Control", enum_type::control},
        {"Indices", enum_type::indices},
        {"Market Status", enum_type::market_status},
        {"Prior Day", enum_type::prior_day},
        {"Summary", enum_type::summary},
        {"Trade", enum_type::trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::administrative: return "Administrative";
            case enum_type::control: return "Control";
            case enum_type::indices: return "Indices";
            case enum_type::market_status: return "Market Status";
            case enum_type::prior_day: return "Prior Day";
            case enum_type::summary: return "Summary";
            case enum_type::trade: return "Trade";
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

    static constexpr const char* name = "message_category";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_category::enum_type>;
    using storage_type = result_type;

    constexpr message_category()
     : value{ enum_type{} } {}

    constexpr message_category(enum_type v)
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
            set(enum_type::trade);
    }

  protected:
    enum_type value;
};
}
