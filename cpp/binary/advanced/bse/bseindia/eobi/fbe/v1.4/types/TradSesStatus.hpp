#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// trad_ses_status
struct trad_ses_status {

    enum class enum_type : std::uint8_t {
        halted = 1,
        open = 2,
        closed = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Closed", enum_type::closed},
        {"Halted", enum_type::halted},
        {"Open", enum_type::open}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halted: return "Halted";
            case enum_type::open: return "Open";
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

    static constexpr const char* name = "trad_ses_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trad_ses_status::enum_type>;
    using storage_type = result_type;

    constexpr trad_ses_status()
     : value{ enum_type{} } {}

    constexpr trad_ses_status(enum_type v)
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
