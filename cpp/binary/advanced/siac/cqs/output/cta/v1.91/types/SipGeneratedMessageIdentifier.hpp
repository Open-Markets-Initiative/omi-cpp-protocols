#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// sip_generated_message_identifier
struct sip_generated_message_identifier {

    enum class enum_type : char {
        not_applicable = ' ',
        consolidated_quotation_system = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Consolidated Quotation System", enum_type::consolidated_quotation_system},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::consolidated_quotation_system: return "Consolidated Quotation System";
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

    static constexpr const char* name = "sip_generated_message_identifier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<sip_generated_message_identifier::enum_type>;
    using storage_type = result_type;

    constexpr sip_generated_message_identifier()
     : value{ enum_type{} } {}

    constexpr sip_generated_message_identifier(enum_type v)
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
            set(enum_type::consolidated_quotation_system);
    }

  protected:
    enum_type value;
};
}
