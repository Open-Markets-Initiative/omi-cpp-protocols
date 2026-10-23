#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// security_reference_data_supplement
struct security_reference_data_supplement {

    static constexpr const char* name = "security_reference_data_supplement";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::uint32_t null_value = 0xFFFFFFFF;

    using result_type = std::optional<std::uint32_t>;
    using storage_type = result_type;

    constexpr security_reference_data_supplement()
     : value{ 0 } {}

    constexpr security_reference_data_supplement(std::uint32_t v)
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
