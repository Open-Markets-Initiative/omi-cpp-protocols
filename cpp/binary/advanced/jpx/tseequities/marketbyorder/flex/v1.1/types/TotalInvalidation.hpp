#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// total_invalidation
#pragma pack(push, 1)
struct total_invalidation {

    static constexpr const char* name = "total_invalidation";
    static constexpr std::size_t size = 6;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr total_invalidation()
     : value{ 0 } {}

    total_invalidation(std::uint64_t v)
     : value{ __builtin_bswap64(v << 16) } {}

    [[nodiscard]] result_type get() const {
        return result_type{__builtin_bswap64(static_cast<std::uint64_t>(value)) >> 16};
    }

    void set(std::uint64_t v) {
        value = __builtin_bswap64(v << 16);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value:48;
};
#pragma pack(pop)
}
