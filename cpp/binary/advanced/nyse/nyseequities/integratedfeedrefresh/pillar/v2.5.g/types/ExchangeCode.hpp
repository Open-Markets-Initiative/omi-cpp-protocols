#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// exchange_code
struct exchange_code {

    enum class enum_type : char {
        nyse_american = 'A',
        ltse = 'L',
        nyse_texas = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        iex = 'V',
        cboe = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Cboe", enum_type::cboe},
        {"Iex", enum_type::iex},
        {"Ltse", enum_type::ltse},
        {"Nasdaq", enum_type::nasdaq},
        {"Nyse", enum_type::nyse},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse Texas", enum_type::nyse_texas}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::ltse: return "Ltse";
            case enum_type::nyse_texas: return "Nyse Texas";
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::iex: return "Iex";
            case enum_type::cboe: return "Cboe";
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

    static constexpr const char* name = "exchange_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<exchange_code::enum_type>;
    using storage_type = result_type;

    constexpr exchange_code()
     : value{ enum_type{} } {}

    constexpr exchange_code(enum_type v)
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
            set(enum_type::cboe);
    }

  protected:
    enum_type value;
};
}
