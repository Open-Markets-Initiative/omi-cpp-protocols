#pragma once

#include <cstddef>
#include <array>
#include <span>
#include <cstring>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// padding_2
struct padding_2 {

    static constexpr const char* name = "padding_2";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<const std::array<std::uint8_t, 2>&>;
    using storage_type = result_type;

    constexpr padding_2()
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
    std::array<std::uint8_t, 2> value;
};
}
