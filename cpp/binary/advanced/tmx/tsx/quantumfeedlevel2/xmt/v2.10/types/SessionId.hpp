// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/SessionId.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// session_id
struct session_id {

    static constexpr const char* name = "session_id";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr session_id()
     : value{ 0 } {}

    constexpr session_id(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
