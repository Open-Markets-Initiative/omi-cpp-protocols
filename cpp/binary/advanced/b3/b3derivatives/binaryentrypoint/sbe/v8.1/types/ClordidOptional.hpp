// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/ClOrdIdOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// cl_ord_id_optional
struct cl_ord_id_optional {

    static constexpr const char* name = "cl_ord_id_optional";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0ULL;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr cl_ord_id_optional()
     : value{ null_value } {}

    constexpr cl_ord_id_optional(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint64_t v) {
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
    std::uint64_t value;
};
}
