#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// broken_date_guid
struct broken_date_guid {

    static constexpr const char* name = "broken_date_guid";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr broken_date_guid()
     : value{ 0 } {}

    constexpr broken_date_guid(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
