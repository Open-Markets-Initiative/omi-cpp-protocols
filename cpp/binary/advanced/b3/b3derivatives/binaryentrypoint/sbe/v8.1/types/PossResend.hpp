#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// poss_resend
struct poss_resend {

    static constexpr const char* name = "poss_resend";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint8_t>;
    using storage_type = result_type;

    constexpr poss_resend()
     : value{ 0 } {}

    constexpr poss_resend(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint8_t value;
};
}
