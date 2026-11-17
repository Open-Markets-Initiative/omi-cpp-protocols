// Siac.Cqs.Output.Cta.v1.91: types/ParticipantTimestampOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// participant_timestamp_optional
struct participant_timestamp_optional {

    static constexpr const char* name = "participant_timestamp_optional";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0ULL;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr participant_timestamp_optional()
     : value{ null_value } {}

    constexpr participant_timestamp_optional(std::uint64_t v)
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
