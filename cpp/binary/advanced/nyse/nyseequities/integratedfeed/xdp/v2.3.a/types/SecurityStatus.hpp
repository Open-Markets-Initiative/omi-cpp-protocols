#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// security_status
struct security_status {

    enum class enum_type : char {
        trading_halt = '4',
        resume = '5',
        short_sale_restriction_activated_day_1 = 'A',
        short_sale_restriction_continued_day_2 = 'C',
        short_sale_restriction_deactivated = 'D',
        pre_opening = 'P',
        early_session = 'E',
        core_session = 'O',
        late_session_non_nyse_only = 'L',
        closed = 'X',
        price_indication = 'I',
        pre_opening_price_indication = 'G'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Closed", enum_type::closed},
        {"Core Session", enum_type::core_session},
        {"Early Session", enum_type::early_session},
        {"Late Session Non Nyse Only", enum_type::late_session_non_nyse_only},
        {"Pre Opening", enum_type::pre_opening},
        {"Pre Opening Price Indication", enum_type::pre_opening_price_indication},
        {"Price Indication", enum_type::price_indication},
        {"Resume", enum_type::resume},
        {"Short Sale Restriction Activated Day 1", enum_type::short_sale_restriction_activated_day_1},
        {"Short Sale Restriction Continued Day 2", enum_type::short_sale_restriction_continued_day_2},
        {"Short Sale Restriction Deactivated", enum_type::short_sale_restriction_deactivated},
        {"Trading Halt", enum_type::trading_halt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::resume: return "Resume";
            case enum_type::short_sale_restriction_activated_day_1: return "Short Sale Restriction Activated Day 1";
            case enum_type::short_sale_restriction_continued_day_2: return "Short Sale Restriction Continued Day 2";
            case enum_type::short_sale_restriction_deactivated: return "Short Sale Restriction Deactivated";
            case enum_type::pre_opening: return "Pre Opening";
            case enum_type::early_session: return "Early Session";
            case enum_type::core_session: return "Core Session";
            case enum_type::late_session_non_nyse_only: return "Late Session Non Nyse Only";
            case enum_type::closed: return "Closed";
            case enum_type::price_indication: return "Price Indication";
            case enum_type::pre_opening_price_indication: return "Pre Opening Price Indication";
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
            set(enum_type::pre_opening_price_indication);
    }

  protected:
    enum_type value;
};
}
