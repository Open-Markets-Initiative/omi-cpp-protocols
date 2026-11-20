// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/SourceId.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// source_id
struct source_id {

    enum class enum_type : char {
        non_source_related = '0',
        tsx = 'Q',
        tsx_venture = 'V',
        alpha = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Alpha", enum_type::alpha},
        {"Non Source Related", enum_type::non_source_related},
        {"TSX", enum_type::tsx},
        {"TSX Venture", enum_type::tsx_venture}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::non_source_related: return "Non Source Related";
            case enum_type::tsx: return "TSX";
            case enum_type::tsx_venture: return "TSX Venture";
            case enum_type::alpha: return "Alpha";
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

    static constexpr const char* name = "source_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<source_id::enum_type>;
    using storage_type = result_type;

    constexpr source_id()
     : value{ enum_type{} } {}

    constexpr source_id(enum_type v)
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
            set(enum_type::alpha);
    }

  protected:
    enum_type value;
};
}
