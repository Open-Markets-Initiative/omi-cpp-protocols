#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// pos_maint_rpt_ref_id
struct pos_maint_rpt_ref_id {

    static constexpr const char* name = "pos_maint_rpt_ref_id";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0ULL;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr pos_maint_rpt_ref_id()
     : value{ 0 } {}

    constexpr pos_maint_rpt_ref_id(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint64_t v) {
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
    std::uint64_t value;
};
}
