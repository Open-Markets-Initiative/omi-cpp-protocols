// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SeqNum.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// seq_num
struct seq_num {

    static constexpr const char* name = "seq_num";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr seq_num()
     : value{ 0 } {}

    seq_num(std::uint32_t v)
     : value{ static_cast<std::uint32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint32_t>(__builtin_bswap32(value))};
    }

    void set(std::uint32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
