#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// bid_size
struct bid_size {

    static constexpr const char* name = "bid_size";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr bid_size()
     : value{ 0 } {}

    bid_size(std::uint32_t v)
     : value{ static_cast<std::uint32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint32_t>(__builtin_bswap32(value))};
    }

    void set(std::uint32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
