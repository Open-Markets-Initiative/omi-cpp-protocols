#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// auction_type
struct auction_type {

    enum class enum_type : char {
        opening = 'O',
        closing = 'C',
        halt = 'H',
        ipo = 'I',
        close = 'M',
        sum = 'T',
        bam = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Bam", enum_type::bam},
        {"Close", enum_type::close},
        {"Closing", enum_type::closing},
        {"Halt", enum_type::halt},
        {"Ipo", enum_type::ipo},
        {"Opening", enum_type::opening},
        {"Sum", enum_type::sum}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening: return "Opening";
            case enum_type::closing: return "Closing";
            case enum_type::halt: return "Halt";
            case enum_type::ipo: return "Ipo";
            case enum_type::close: return "Close";
            case enum_type::sum: return "Sum";
            case enum_type::bam: return "Bam";
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

    static constexpr const char* name = "auction_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_type::enum_type>;
    using storage_type = result_type;

    constexpr auction_type()
     : value{ enum_type{} } {}

    constexpr auction_type(enum_type v)
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
            set(enum_type::bam);
    }

  protected:
    enum_type value;
};
}
