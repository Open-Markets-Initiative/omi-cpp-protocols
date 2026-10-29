#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// exchange_code
struct exchange_code {

    enum class enum_type : char {
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        nyse_mkt = 'A',
        global_otc = '1',
        arca_local_non_tape_b_index = '2'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Arca Local Non Tape B Index", enum_type::arca_local_non_tape_b_index},
        {"Global Otc", enum_type::global_otc},
        {"Nasdaq", enum_type::nasdaq},
        {"Nyse", enum_type::nyse},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse Mkt", enum_type::nyse_mkt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::nyse_mkt: return "Nyse Mkt";
            case enum_type::global_otc: return "Global Otc";
            case enum_type::arca_local_non_tape_b_index: return "Arca Local Non Tape B Index";
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
            set(enum_type::arca_local_non_tape_b_index);
    }

  protected:
    enum_type value;
};
}
