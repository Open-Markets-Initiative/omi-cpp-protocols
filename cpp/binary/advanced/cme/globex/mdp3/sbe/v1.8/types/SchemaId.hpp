#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// schema_id
struct schema_id {

    enum class enum_type : std::uint16_t {
        mktdata = 1,
        mdpsessionmgmt = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Mdpsessionmgmt", enum_type::mdpsessionmgmt},
        {"Mktdata", enum_type::mktdata}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::mktdata: return "Mktdata";
            case enum_type::mdpsessionmgmt: return "Mdpsessionmgmt";
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

    static constexpr const char* name = "schema_id";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<schema_id::enum_type>;
    using storage_type = result_type;

    constexpr schema_id()
     : value{ enum_type{} } {}

    constexpr schema_id(enum_type v)
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
            set(enum_type::mdpsessionmgmt);
    }

  protected:
    enum_type value;
};
}
