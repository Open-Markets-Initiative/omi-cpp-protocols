#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// trd_reg_ts_time_priority
struct trd_reg_ts_time_priority {

    static constexpr const char* name = "trd_reg_ts_time_priority";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0xFFFFFFFFFFFFFFFFULL;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr trd_reg_ts_time_priority()
     : value{ 0 } {}

    constexpr trd_reg_ts_time_priority(std::uint64_t v)
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
