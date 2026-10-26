#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// open_close_settl_flag
struct open_close_settl_flag {

    enum class enum_type : std::uint8_t {
        no_value = 255,
        daily_open_price = 0,
        indicative_opening_price = 5,
        intraday_vwap = 100,
        repo_average_830_am = 101,
        repo_average_10_am = 102,
        prev_session_repo_average_10_am = 103
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Daily Open Price", enum_type::daily_open_price},
        {"Indicative Opening Price", enum_type::indicative_opening_price},
        {"Intraday Vwap", enum_type::intraday_vwap},
        {"No Value", enum_type::no_value},
        {"Prev Session Repo Average 10 Am", enum_type::prev_session_repo_average_10_am},
        {"Repo Average 10 Am", enum_type::repo_average_10_am},
        {"Repo Average 830 Am", enum_type::repo_average_830_am}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_value: return "No Value";
            case enum_type::daily_open_price: return "Daily Open Price";
            case enum_type::indicative_opening_price: return "Indicative Opening Price";
            case enum_type::intraday_vwap: return "Intraday Vwap";
            case enum_type::repo_average_830_am: return "Repo Average 830 Am";
            case enum_type::repo_average_10_am: return "Repo Average 10 Am";
            case enum_type::prev_session_repo_average_10_am: return "Prev Session Repo Average 10 Am";
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

    static constexpr const char* name = "open_close_settl_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<open_close_settl_flag::enum_type>;
    using storage_type = result_type;

    constexpr open_close_settl_flag()
     : value{ enum_type{} } {}

    constexpr open_close_settl_flag(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
