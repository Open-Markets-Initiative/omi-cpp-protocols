// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/ProtocolName.hpp
#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// protocol_name
struct protocol_name {

    static constexpr const char* name = "protocol_name";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr protocol_name()
     : value{ 0 } {}

    constexpr protocol_name(char v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(char v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    char value;
};
}
