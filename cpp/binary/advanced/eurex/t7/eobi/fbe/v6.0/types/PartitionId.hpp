#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

// partition_id
struct partition_id {

    static constexpr const char* name = "partition_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr std::uint8_t null_value = 0xFF;

    using result_type = std::optional<std::uint8_t>;
    using storage_type = result_type;

    constexpr partition_id()
     : value{ 0 } {}

    constexpr partition_id(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint8_t v) {
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
    std::uint8_t value;
};
}
