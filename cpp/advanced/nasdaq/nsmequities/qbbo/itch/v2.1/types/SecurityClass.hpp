#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// security_class
struct security_class {

    enum class enum_type : char {
        nasdaq_listed_issue = 'Q',
        nyse = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        nyse_texas = 'M',
        bats = 'Z',
        iexg = 'V'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Bats", enum_type::bats},
        {"Iexg", enum_type::iexg},
        {"Nasdaq Listed Issue", enum_type::nasdaq_listed_issue},
        {"Nyse", enum_type::nyse},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse Texas", enum_type::nyse_texas}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nasdaq_listed_issue: return "Nasdaq Listed Issue";
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nyse_texas: return "Nyse Texas";
            case enum_type::bats: return "Bats";
            case enum_type::iexg: return "Iexg";
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

    static constexpr const char* name = "security_class";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_class::enum_type>;
    using storage_type = result_type;

    constexpr security_class()
     : value{ enum_type{} } {}

    constexpr security_class(enum_type v)
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
            set(enum_type::iexg);
    }

  protected:
    enum_type value;
};
}
