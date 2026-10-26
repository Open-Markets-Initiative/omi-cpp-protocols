#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// tot_num_reports_optional
struct tot_num_reports_optional {

    static constexpr const char* name = "tot_num_reports_optional";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::uint32_t null_value = 4294967295;

    using result_type = std::optional<std::uint32_t>;
    using storage_type = result_type;

    constexpr tot_num_reports_optional()
     : value{ 0 } {}

    constexpr tot_num_reports_optional(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint32_t value;
};
}
