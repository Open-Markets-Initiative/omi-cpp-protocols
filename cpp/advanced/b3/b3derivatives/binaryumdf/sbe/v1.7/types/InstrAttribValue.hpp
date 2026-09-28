#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// instr_attrib_value
struct instr_attrib_value {

    enum class enum_type : std::uint8_t {
        electronic_match_or_gtd_gtc_eligible = 1,
        order_cross_eligible = 2,
        block_trade_eligible = 3,
        flag_rfq_for_cross_eligible = 14,
        negotiated_quote_eligible = 17
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Block Trade Eligible", enum_type::block_trade_eligible},
        {"Electronic Match Or Gtd Gtc Eligible", enum_type::electronic_match_or_gtd_gtc_eligible},
        {"Flag Rfq For Cross Eligible", enum_type::flag_rfq_for_cross_eligible},
        {"Negotiated Quote Eligible", enum_type::negotiated_quote_eligible},
        {"Order Cross Eligible", enum_type::order_cross_eligible}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::electronic_match_or_gtd_gtc_eligible: return "Electronic Match Or Gtd Gtc Eligible";
            case enum_type::order_cross_eligible: return "Order Cross Eligible";
            case enum_type::block_trade_eligible: return "Block Trade Eligible";
            case enum_type::flag_rfq_for_cross_eligible: return "Flag Rfq For Cross Eligible";
            case enum_type::negotiated_quote_eligible: return "Negotiated Quote Eligible";
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

    static constexpr const char* name = "instr_attrib_value";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<instr_attrib_value::enum_type>;
    using storage_type = result_type;

    constexpr instr_attrib_value()
     : value{ enum_type::electronic_match_or_gtd_gtc_eligible } {}

    constexpr instr_attrib_value(enum_type v)
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
            set(enum_type::negotiated_quote_eligible);
    }

  protected:
    enum_type value;
};
}
