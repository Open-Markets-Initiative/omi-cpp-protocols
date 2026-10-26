#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// book_type
struct book_type {

    enum class enum_type : std::uint8_t {
        on_book = 1,
        off_book = 2,
        private_rfq = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Off Book", enum_type::off_book},
        {"On Book", enum_type::on_book},
        {"Private Rfq", enum_type::private_rfq}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::on_book: return "On Book";
            case enum_type::off_book: return "Off Book";
            case enum_type::private_rfq: return "Private Rfq";
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

    static constexpr const char* name = "book_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<book_type::enum_type>;
    using storage_type = result_type;

    constexpr book_type()
     : value{ enum_type{} } {}

    constexpr book_type(enum_type v)
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
            set(enum_type::private_rfq);
    }

  protected:
    enum_type value;
};
}
