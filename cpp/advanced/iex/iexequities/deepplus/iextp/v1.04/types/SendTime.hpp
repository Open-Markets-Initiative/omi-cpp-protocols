#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

// send_time
struct send_time {

    static constexpr const char* name = "send_time";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr send_time()
     : value{ 0 } {}

    constexpr send_time(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
