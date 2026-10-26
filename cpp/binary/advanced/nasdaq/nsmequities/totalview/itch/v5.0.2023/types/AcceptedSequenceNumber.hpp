#pragma once

#include <cstddef>
#include <array>
#include <string_view>
#include <algorithm>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// accepted_sequence_number
struct accepted_sequence_number {

    static constexpr const char* name = "accepted_sequence_number";
    static constexpr std::size_t size = 20;
    static constexpr char fill_char = ' ';
    static constexpr bool is_optional = false;

    using result_type = required<std::string_view>;
    using storage_type = required<std::array<char, 20>>;

    constexpr accepted_sequence_number() {
        value.fill(fill_char);
    }

    [[nodiscard]] result_type get() const {
        return result_type{std::string_view(value.data(), value.size())};
    }

    [[nodiscard]] result_type get_trimmed() const {
        return result_type{trim(std::string_view(value.data(), value.size()))};
    }

    [[nodiscard]] static std::string_view trim(const std::string_view& value) {
        std::size_t start = 0;
        while (start < value.size() && value[start] == fill_char) ++start;
        return value.substr(start);
    }

    [[nodiscard]] static result_type trim(const result_type& value) {
        return result_type{trim(value.value())};
    }

    constexpr void set(std::string_view str) {
        value.fill(fill_char);
        auto len = std::min(str.size(), value.size());
        std::copy_n(str.data(), len, value.data() + (value.size() - len));
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set("");
    }

  protected:
    std::array<char, 20> value;
};
}
