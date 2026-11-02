#pragma once

#include <cstddef>
#include <array>
#include <span>
#include <algorithm>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// metadata_reserved
struct metadata_reserved {

    static constexpr const char* name = "metadata_reserved";
    static constexpr std::size_t size = 47;
    static constexpr bool is_optional = false;

    using result_type = required<const std::array<std::uint8_t, 47>&>;
    using storage_type = result_type;

    constexpr metadata_reserved()
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
    std::array<std::uint8_t, 47> value;
};
}
