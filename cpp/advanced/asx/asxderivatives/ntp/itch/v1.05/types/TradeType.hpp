#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// trade_type
struct trade_type {

    enum class enum_type : char {
        normal_trade = 'T',
        normal_cross = 't',
        auction_trade = 'L',
        auction_cross = 'l',
        combination_to_underlying_trade = 'S',
        combination_to_underlying_cross = 's',
        combination_to_combination_trade = 'R',
        combination_to_combination_cross = 'r',
        strip_to_strip_trade = 'A',
        strip_to_strip_cross = 'a',
        strip_to_outright_trade = 'B',
        strip_to_outright_cross = 'b'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Auction Cross", enum_type::auction_cross},
        {"Auction Trade", enum_type::auction_trade},
        {"Combination To Combination Cross", enum_type::combination_to_combination_cross},
        {"Combination To Combination Trade", enum_type::combination_to_combination_trade},
        {"Combination To Underlying Cross", enum_type::combination_to_underlying_cross},
        {"Combination To Underlying Trade", enum_type::combination_to_underlying_trade},
        {"Normal Cross", enum_type::normal_cross},
        {"Normal Trade", enum_type::normal_trade},
        {"Strip To Outright Cross", enum_type::strip_to_outright_cross},
        {"Strip To Outright Trade", enum_type::strip_to_outright_trade},
        {"Strip To Strip Cross", enum_type::strip_to_strip_cross},
        {"Strip To Strip Trade", enum_type::strip_to_strip_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::normal_trade: return "Normal Trade";
            case enum_type::normal_cross: return "Normal Cross";
            case enum_type::auction_trade: return "Auction Trade";
            case enum_type::auction_cross: return "Auction Cross";
            case enum_type::combination_to_underlying_trade: return "Combination To Underlying Trade";
            case enum_type::combination_to_underlying_cross: return "Combination To Underlying Cross";
            case enum_type::combination_to_combination_trade: return "Combination To Combination Trade";
            case enum_type::combination_to_combination_cross: return "Combination To Combination Cross";
            case enum_type::strip_to_strip_trade: return "Strip To Strip Trade";
            case enum_type::strip_to_strip_cross: return "Strip To Strip Cross";
            case enum_type::strip_to_outright_trade: return "Strip To Outright Trade";
            case enum_type::strip_to_outright_cross: return "Strip To Outright Cross";
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

    static constexpr const char* name = "trade_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_type::enum_type>;
    using storage_type = result_type;

    constexpr trade_type()
     : value{ enum_type{} } {}

    constexpr trade_type(enum_type v)
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
            set(enum_type::strip_to_outright_cross);
    }

  protected:
    enum_type value;
};
}
