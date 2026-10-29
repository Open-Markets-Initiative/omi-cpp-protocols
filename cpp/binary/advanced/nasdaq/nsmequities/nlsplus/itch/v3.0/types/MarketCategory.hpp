#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// market_category
struct market_category {

    enum class enum_type : char {
        nasdaq_global_select_market = 'Q',
        nasdaq_global_market = 'G',
        nasdaq_capital_market = 'S',
        nyse = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        nyse_texas = 'M',
        bats = 'Z',
        iex = 'V'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Bats", enum_type::bats},
        {"Iex", enum_type::iex},
        {"Nasdaq Capital Market", enum_type::nasdaq_capital_market},
        {"Nasdaq Global Market", enum_type::nasdaq_global_market},
        {"Nasdaq Global Select Market", enum_type::nasdaq_global_select_market},
        {"Nyse", enum_type::nyse},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse Texas", enum_type::nyse_texas}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nasdaq_global_select_market: return "Nasdaq Global Select Market";
            case enum_type::nasdaq_global_market: return "Nasdaq Global Market";
            case enum_type::nasdaq_capital_market: return "Nasdaq Capital Market";
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nyse_texas: return "Nyse Texas";
            case enum_type::bats: return "Bats";
            case enum_type::iex: return "Iex";
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

    static constexpr const char* name = "market_category";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_category::enum_type>;
    using storage_type = result_type;

    constexpr market_category()
     : value{ enum_type{} } {}

    constexpr market_category(enum_type v)
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
            set(enum_type::iex);
    }

  protected:
    enum_type value;
};
}
