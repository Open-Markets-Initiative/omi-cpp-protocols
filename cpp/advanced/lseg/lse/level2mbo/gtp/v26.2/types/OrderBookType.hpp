#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// order_book_type
struct order_book_type {

    enum class enum_type : std::uint8_t {
        firm_quote_book = 1,
        offbook = 2,
        electronic_order_book = 3,
        private_rfq = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Electronic Order Book", enum_type::electronic_order_book},
        {"Firm Quote Book", enum_type::firm_quote_book},
        {"Offbook", enum_type::offbook},
        {"Private Rfq", enum_type::private_rfq}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::firm_quote_book: return "Firm Quote Book";
            case enum_type::offbook: return "Offbook";
            case enum_type::electronic_order_book: return "Electronic Order Book";
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

    static constexpr const char* name = "order_book_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_book_type::enum_type>;
    using storage_type = result_type;

    constexpr order_book_type()
     : value{ enum_type{} } {}

    constexpr order_book_type(enum_type v)
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
