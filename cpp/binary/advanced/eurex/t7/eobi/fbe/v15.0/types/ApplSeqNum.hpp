// Eurex.T7.Eobi.Fbe.v15.0: types/ApplSeqNum.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// appl_seq_num
struct appl_seq_num {

    static constexpr const char* name = "appl_seq_num";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::uint32_t null_value = 0xFFFFFFFF;

    using result_type = std::optional<std::uint32_t>;
    using storage_type = result_type;

    constexpr appl_seq_num()
     : value{ null_value } {}

    constexpr appl_seq_num(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint32_t value;
};
}
