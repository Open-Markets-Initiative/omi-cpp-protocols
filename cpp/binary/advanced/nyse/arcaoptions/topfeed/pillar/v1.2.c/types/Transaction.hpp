#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// transaction
struct transaction {

    enum class enum_type : char {
        opening_trade_in_sequence = 'H',
        opening_trade_out_of_sequence = 'F',
        in_sequence = 'D',
        out_of_sequence = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"In Sequence", enum_type::in_sequence},
        {"Opening Trade In Sequence", enum_type::opening_trade_in_sequence},
        {"Opening Trade Out Of Sequence", enum_type::opening_trade_out_of_sequence},
        {"Out Of Sequence", enum_type::out_of_sequence}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_trade_in_sequence: return "Opening Trade In Sequence";
            case enum_type::opening_trade_out_of_sequence: return "Opening Trade Out Of Sequence";
            case enum_type::in_sequence: return "In Sequence";
            case enum_type::out_of_sequence: return "Out Of Sequence";
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

    static constexpr const char* name = "transaction";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<transaction::enum_type>;
    using storage_type = result_type;

    constexpr transaction()
     : value{ enum_type{} } {}

    constexpr transaction(enum_type v)
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
            set(enum_type::out_of_sequence);
    }

  protected:
    enum_type value;
};
}
