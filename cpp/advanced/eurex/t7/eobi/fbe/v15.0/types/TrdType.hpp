#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// trd_type
struct trd_type {

    enum class enum_type : std::uint16_t {
        block_trade = 1,
        efp = 2,
        efs = 12,
        otc = 54,
        exchange_basis_facility = 55,
        vola_trade = 1000,
        efp_fin_trade = 1001,
        efp_index_futures_trade = 1002,
        block_trade_at_market = 1004,
        xetra_eurex_enlight_triggered_trade = 1006,
        block_qtpip_trade = 1007,
        no_value = 0xFFFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Block Qtpip Trade", enum_type::block_qtpip_trade},
        {"Block Trade", enum_type::block_trade},
        {"Block Trade At Market", enum_type::block_trade_at_market},
        {"Efp", enum_type::efp},
        {"Efp Fin Trade", enum_type::efp_fin_trade},
        {"Efp Index Futures Trade", enum_type::efp_index_futures_trade},
        {"Efs", enum_type::efs},
        {"Exchange Basis Facility", enum_type::exchange_basis_facility},
        {"No Value", enum_type::no_value},
        {"Otc", enum_type::otc},
        {"Vola Trade", enum_type::vola_trade},
        {"Xetra Eurex Enlight Triggered Trade", enum_type::xetra_eurex_enlight_triggered_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::block_trade: return "Block Trade";
            case enum_type::efp: return "Efp";
            case enum_type::efs: return "Efs";
            case enum_type::otc: return "Otc";
            case enum_type::exchange_basis_facility: return "Exchange Basis Facility";
            case enum_type::vola_trade: return "Vola Trade";
            case enum_type::efp_fin_trade: return "Efp Fin Trade";
            case enum_type::efp_index_futures_trade: return "Efp Index Futures Trade";
            case enum_type::block_trade_at_market: return "Block Trade At Market";
            case enum_type::xetra_eurex_enlight_triggered_trade: return "Xetra Eurex Enlight Triggered Trade";
            case enum_type::block_qtpip_trade: return "Block Qtpip Trade";
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

    static constexpr const char* name = "trd_type";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<trd_type::enum_type>;
    using storage_type = result_type;

    constexpr trd_type()
     : value{ enum_type{} } {}

    constexpr trd_type(enum_type v)
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
            set(static_cast<enum_type>(0xFFFF));
    }

  protected:
    enum_type value;
};
}
