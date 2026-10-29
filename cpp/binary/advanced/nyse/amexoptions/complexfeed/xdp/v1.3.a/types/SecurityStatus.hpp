#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// security_status
struct security_status {

    enum class enum_type : char {
        light_up_a_dark_series = 'L',
        open_a_dark_series = 'N',
        open = 'O',
        close = 'X',
        halt = 'S',
        unhalt = 'U',
        unhalt_a_dark_series = 'T',
        end_of_rfq_auction = 'Q'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Close", enum_type::close},
        {"End Of Rfq Auction", enum_type::end_of_rfq_auction},
        {"Halt", enum_type::halt},
        {"Light Up A Dark Series", enum_type::light_up_a_dark_series},
        {"Open", enum_type::open},
        {"Open A Dark Series", enum_type::open_a_dark_series},
        {"Unhalt", enum_type::unhalt},
        {"Unhalt A Dark Series", enum_type::unhalt_a_dark_series}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::light_up_a_dark_series: return "Light Up A Dark Series";
            case enum_type::open_a_dark_series: return "Open A Dark Series";
            case enum_type::open: return "Open";
            case enum_type::close: return "Close";
            case enum_type::halt: return "Halt";
            case enum_type::unhalt: return "Unhalt";
            case enum_type::unhalt_a_dark_series: return "Unhalt A Dark Series";
            case enum_type::end_of_rfq_auction: return "End Of Rfq Auction";
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

    static constexpr const char* name = "security_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_status::enum_type>;
    using storage_type = result_type;

    constexpr security_status()
     : value{ enum_type{} } {}

    constexpr security_status(enum_type v)
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
            set(enum_type::end_of_rfq_auction);
    }

  protected:
    enum_type value;
};
}
