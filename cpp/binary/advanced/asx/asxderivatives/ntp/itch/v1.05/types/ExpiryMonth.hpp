#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// expiry_month
struct expiry_month {

    enum class enum_type : std::uint8_t {
        jan = 1,
        feb = 2,
        mar = 3,
        apr = 4,
        may = 5,
        jun = 6,
        jul = 7,
        aug = 8,
        sep = 9,
        oct = 10,
        nov = 11,
        dec = 12
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Apr", enum_type::apr},
        {"Aug", enum_type::aug},
        {"Dec", enum_type::dec},
        {"Feb", enum_type::feb},
        {"Jan", enum_type::jan},
        {"Jul", enum_type::jul},
        {"Jun", enum_type::jun},
        {"Mar", enum_type::mar},
        {"May", enum_type::may},
        {"Nov", enum_type::nov},
        {"Oct", enum_type::oct},
        {"Sep", enum_type::sep}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::jan: return "Jan";
            case enum_type::feb: return "Feb";
            case enum_type::mar: return "Mar";
            case enum_type::apr: return "Apr";
            case enum_type::may: return "May";
            case enum_type::jun: return "Jun";
            case enum_type::jul: return "Jul";
            case enum_type::aug: return "Aug";
            case enum_type::sep: return "Sep";
            case enum_type::oct: return "Oct";
            case enum_type::nov: return "Nov";
            case enum_type::dec: return "Dec";
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

    static constexpr const char* name = "expiry_month";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<expiry_month::enum_type>;
    using storage_type = result_type;

    constexpr expiry_month()
     : value{ enum_type{} } {}

    constexpr expiry_month(enum_type v)
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
            set(enum_type::dec);
    }

  protected:
    enum_type value;
};
}
