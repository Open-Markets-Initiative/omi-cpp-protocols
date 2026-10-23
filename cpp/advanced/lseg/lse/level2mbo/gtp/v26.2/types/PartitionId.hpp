#pragma once

#include <cstddef>
#include <optional>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// partition_id
struct partition_id {

    static constexpr const char* name = "partition_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;

    using result_type = std::optional<char>;
    using storage_type = result_type;

    constexpr partition_id()
     : value{ 0 } {}

    constexpr partition_id(char v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(char v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    char value;
};
}
