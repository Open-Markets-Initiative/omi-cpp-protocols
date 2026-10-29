#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// indices_message_type
struct indices_message_type {

    enum class enum_type : char {
        index_message = 'I',
        bid_and_offer_index_message = 'Q'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Bid And Offer Index Message", enum_type::bid_and_offer_index_message},
        {"Index Message", enum_type::index_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::index_message: return "Index Message";
            case enum_type::bid_and_offer_index_message: return "Bid And Offer Index Message";
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

    static constexpr const char* name = "indices_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<indices_message_type::enum_type>;
    using storage_type = result_type;

    constexpr indices_message_type()
     : value{ enum_type{} } {}

    constexpr indices_message_type(enum_type v)
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
            set(enum_type::bid_and_offer_index_message);
    }

  protected:
    enum_type value;
};
}
