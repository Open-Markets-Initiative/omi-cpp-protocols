#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        stock_directory_message = 'R',
        stock_trading_action_message = 'H',
        reg_sho_restriction_message = 'Y',
        mwcb_decline_level_message = 'V',
        mwcb_breach_message = 'W',
        operational_halt_message = 'h',
        bbo_quotation_message = 'Q',
        price_improvement_message = 'N',
        ipo_quoting_period_update_message = 'K'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Bbo Quotation Message", enum_type::bbo_quotation_message},
        {"Ipo Quoting Period Update Message", enum_type::ipo_quoting_period_update_message},
        {"Mwcb Breach Message", enum_type::mwcb_breach_message},
        {"Mwcb Decline Level Message", enum_type::mwcb_decline_level_message},
        {"Operational Halt Message", enum_type::operational_halt_message},
        {"Price Improvement Message", enum_type::price_improvement_message},
        {"Reg Sho Restriction Message", enum_type::reg_sho_restriction_message},
        {"Stock Directory Message", enum_type::stock_directory_message},
        {"Stock Trading Action Message", enum_type::stock_trading_action_message},
        {"System Event Message", enum_type::system_event_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::stock_directory_message: return "Stock Directory Message";
            case enum_type::stock_trading_action_message: return "Stock Trading Action Message";
            case enum_type::reg_sho_restriction_message: return "Reg Sho Restriction Message";
            case enum_type::mwcb_decline_level_message: return "Mwcb Decline Level Message";
            case enum_type::mwcb_breach_message: return "Mwcb Breach Message";
            case enum_type::operational_halt_message: return "Operational Halt Message";
            case enum_type::bbo_quotation_message: return "Bbo Quotation Message";
            case enum_type::price_improvement_message: return "Price Improvement Message";
            case enum_type::ipo_quoting_period_update_message: return "Ipo Quoting Period Update Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::ipo_quoting_period_update_message);
    }

  protected:
    enum_type value;
};
}
