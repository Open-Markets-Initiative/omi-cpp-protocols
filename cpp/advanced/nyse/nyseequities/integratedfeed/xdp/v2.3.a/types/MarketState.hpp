#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// market_state
struct market_state {

    enum class enum_type : char {
        preopening = 'P',
        early_session = 'E',
        core_session = 'O',
        late_session = 'L',
        closed = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Closed", enum_type::closed},
        {"Core Session", enum_type::core_session},
        {"Early Session", enum_type::early_session},
        {"Late Session", enum_type::late_session},
        {"Preopening", enum_type::preopening}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::preopening: return "Preopening";
            case enum_type::early_session: return "Early Session";
            case enum_type::core_session: return "Core Session";
            case enum_type::late_session: return "Late Session";
            case enum_type::closed: return "Closed";
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

    static constexpr const char* name = "market_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_state::enum_type>;
    using storage_type = result_type;

    constexpr market_state()
     : value{ enum_type{} } {}

    constexpr market_state(enum_type v)
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
            set(enum_type::closed);
    }

  protected:
    enum_type value;
};
}
