#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// result_code
struct result_code {

    enum class enum_type : char {
        accepted = 'A',
        out_of_service = 'O',
        incorrect_user_id = 'U',
        incorrect_sequence_number = 'S',
        incorrect_packet_type = 'T',
        incorrect_mcg_number = 'M',
        other_error = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Accepted", enum_type::accepted},
        {"Incorrect Mcg Number", enum_type::incorrect_mcg_number},
        {"Incorrect Packet Type", enum_type::incorrect_packet_type},
        {"Incorrect Sequence Number", enum_type::incorrect_sequence_number},
        {"Incorrect User Id", enum_type::incorrect_user_id},
        {"Other Error", enum_type::other_error},
        {"Out Of Service", enum_type::out_of_service}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::accepted: return "Accepted";
            case enum_type::out_of_service: return "Out Of Service";
            case enum_type::incorrect_user_id: return "Incorrect User Id";
            case enum_type::incorrect_sequence_number: return "Incorrect Sequence Number";
            case enum_type::incorrect_packet_type: return "Incorrect Packet Type";
            case enum_type::incorrect_mcg_number: return "Incorrect Mcg Number";
            case enum_type::other_error: return "Other Error";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "result_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<result_code::enum_type>;
    using storage_type = result_type;

    constexpr result_code()
     : value{ enum_type::accepted } {}

    constexpr result_code(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::other_error);
    }

  protected:
    enum_type value;
};
}
