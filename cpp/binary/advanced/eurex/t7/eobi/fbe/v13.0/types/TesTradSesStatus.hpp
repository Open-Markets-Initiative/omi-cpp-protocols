#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// tes_trad_ses_status
struct tes_trad_ses_status {

    enum class enum_type : std::uint8_t {
        halted = 1,
        open = 2,
        closed = 3,
        pre_close = 5,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Closed", enum_type::closed},
        {"Halted", enum_type::halted},
        {"No Value", enum_type::no_value},
        {"Open", enum_type::open},
        {"Pre Close", enum_type::pre_close}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halted: return "Halted";
            case enum_type::open: return "Open";
            case enum_type::closed: return "Closed";
            case enum_type::pre_close: return "Pre Close";
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

    static constexpr const char* name = "tes_trad_ses_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<tes_trad_ses_status::enum_type>;
    using storage_type = result_type;

    constexpr tes_trad_ses_status()
     : value{ enum_type{} } {}

    constexpr tes_trad_ses_status(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
