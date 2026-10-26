#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// trans_bkd_time
struct trans_bkd_time {

    static constexpr const char* name = "trans_bkd_time";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0xFFFFFFFFFFFFFFFFULL;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr trans_bkd_time()
     : value{ 0 } {}

    constexpr trans_bkd_time(std::uint64_t v)
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
