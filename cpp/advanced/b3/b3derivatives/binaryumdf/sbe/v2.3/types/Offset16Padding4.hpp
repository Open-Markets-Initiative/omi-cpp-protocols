#pragma once

#include <cstddef>
#include <array>
#include <span>
#include <cstring>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// offset_16_padding_4
struct offset_16_padding_4 {

    static constexpr const char* name = "offset_16_padding_4";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<const std::array<std::uint8_t, 4>&>;
    using storage_type = result_type;

    constexpr offset_16_padding_4()
     : value{} {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    void set(std::span<const std::uint8_t> src) {
        auto len = std::min(src.size(), value.size());
        std::memcpy(value.data(), src.data(), len);
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(std::span<const std::uint8_t>(v.value().data(), v.value().size()));
    }

  protected:
    std::array<std::uint8_t, 4> value;
};
}
