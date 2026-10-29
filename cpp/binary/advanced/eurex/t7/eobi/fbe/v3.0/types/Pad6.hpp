#pragma once

#include <cstddef>
#include <array>
#include <span>
#include <algorithm>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// pad6
struct pad6 {

    static constexpr const char* name = "pad6";
    static constexpr std::size_t size = 6;
    static constexpr bool is_optional = false;

    using result_type = required<const std::array<std::uint8_t, 6>&>;
    using storage_type = result_type;

    constexpr pad6()
     : value{} {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::span<const std::uint8_t> src) {
        auto len = std::min(src.size(), value.size());
        std::copy_n(src.begin(), len, value.begin());
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(std::span<const std::uint8_t>(v.value().data(), v.value().size()));
    }

  protected:
    std::array<std::uint8_t, 6> value;
};
}
