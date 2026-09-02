#pragma once

#include <cstddef>
#include <array>
#include <span>
#include <cstring>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

// reserved
struct reserved {

    static constexpr const char* name = "reserved";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<const std::array<std::uint8_t, 1>&>;
    using storage_type = result_type;

    constexpr reserved()
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
    std::array<std::uint8_t, 1> value;
};
}
