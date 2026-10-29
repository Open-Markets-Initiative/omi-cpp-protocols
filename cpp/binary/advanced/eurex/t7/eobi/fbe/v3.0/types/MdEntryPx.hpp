#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// md_entry_px
struct md_entry_px {

    static constexpr const char* name = "md_entry_px";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::int64_t null_value = 0x8000000000000000LL;
    static constexpr int exponent = -8;

    using result_type = std::optional<std::int64_t>;
    using storage_type = result_type;

    constexpr md_entry_px()
     : value{ 0 } {}

    constexpr md_entry_px(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::int64_t v) {
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
    std::int64_t value;
};
}
