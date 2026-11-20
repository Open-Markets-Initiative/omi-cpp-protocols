// Eurex.T7.Eobi.Fbe.v15.0: types/TradingSessionSubId.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// trading_session_sub_id
struct trading_session_sub_id {

    enum class enum_type : std::uint8_t {
        pre_trading = 1,
        continuous = 3,
        closing = 4,
        post_trading = 5,
        quiescent = 7,
        out_of_main_session_trading = 10,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Closing", enum_type::closing},
        {"Continuous", enum_type::continuous},
        {"No Value", enum_type::no_value},
        {"Out Of Main Session Trading", enum_type::out_of_main_session_trading},
        {"Post Trading", enum_type::post_trading},
        {"Pre Trading", enum_type::pre_trading},
        {"Quiescent", enum_type::quiescent}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::pre_trading: return "Pre Trading";
            case enum_type::continuous: return "Continuous";
            case enum_type::closing: return "Closing";
            case enum_type::post_trading: return "Post Trading";
            case enum_type::quiescent: return "Quiescent";
            case enum_type::out_of_main_session_trading: return "Out Of Main Session Trading";
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

    static constexpr const char* name = "trading_session_sub_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr enum_type null_value = static_cast<enum_type>(0xFF);

    using result_type = std::optional<trading_session_sub_id::enum_type>;
    using storage_type = result_type;

    constexpr trading_session_sub_id()
     : value{ static_cast<enum_type>(0xFF) } {}

    constexpr trading_session_sub_id(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        const enum_type held = value;
        return held == null_value ? std::nullopt : result_type{held};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        set(null_value);
    }

  protected:
    enum_type value;
};
}
