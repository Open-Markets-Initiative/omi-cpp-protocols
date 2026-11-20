// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/SettlementTerms.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// settlement_terms
struct settlement_terms {

    enum class enum_type : char {
        cash = 'C',
        nn = 'N',
        ms = 'M',
        ct = 'T',
        valid_settlement_date = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Cash", enum_type::cash},
        {"Ct", enum_type::ct},
        {"Ms", enum_type::ms},
        {"Nn", enum_type::nn},
        {"Valid Settlement Date", enum_type::valid_settlement_date}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cash: return "Cash";
            case enum_type::nn: return "Nn";
            case enum_type::ms: return "Ms";
            case enum_type::ct: return "Ct";
            case enum_type::valid_settlement_date: return "Valid Settlement Date";
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

    static constexpr const char* name = "settlement_terms";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<settlement_terms::enum_type>;
    using storage_type = result_type;

    constexpr settlement_terms()
     : value{ enum_type{} } {}

    constexpr settlement_terms(enum_type v)
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
            set(enum_type::valid_settlement_date);
    }

  protected:
    enum_type value;
};
}
