#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// requested_message_count
#pragma pack(push, 1)
struct requested_message_count {

    static constexpr const char* name = "requested_message_count";
    static constexpr std::size_t size = 3;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr requested_message_count()
     : value{ 0 } {}

    requested_message_count(std::uint32_t v)
     : value{ static_cast<std::uint32_t>(__builtin_bswap64(static_cast<std::uint64_t>(v) << 40)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint32_t>(__builtin_bswap64(static_cast<std::uint64_t>(value)) >> 40)};
    }

    void set(std::uint32_t v) {
        value = static_cast<std::uint32_t>(__builtin_bswap64(static_cast<std::uint64_t>(v) << 40));
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value:24;
};
#pragma pack(pop)
}
