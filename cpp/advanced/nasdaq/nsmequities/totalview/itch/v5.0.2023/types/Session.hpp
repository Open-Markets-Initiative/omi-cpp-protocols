#pragma once

#include <cstddef>
#include <array>
#include <string_view>
#include <cstring>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// session
struct session {

    static constexpr const char* name = "session";
    static constexpr std::size_t size = 10;
    static constexpr char fill_char = '\0';
    static constexpr bool is_optional = false;

    using result_type = required<std::string_view>;
    using storage_type = required<std::array<char, 10>>;

    constexpr session() {
        value.fill(fill_char);
    }

    [[nodiscard]] result_type get() const {
        return result_type{std::string_view(value.data(), value.size())};
    }

    [[nodiscard]] result_type get_trimmed() const {
        return result_type{trim(std::string_view(value.data(), value.size()))};
    }

    [[nodiscard]] static std::string_view trim(const std::string_view& value) {
        auto end = value.size();
        while (end > 0 && value[end - 1] == fill_char) --end;
        return std::string_view(value.data(), end);
    }

    [[nodiscard]] static result_type trim(const result_type& value) {
        return result_type{trim(value.value())};
    }

    void set(std::string_view str) {
        value.fill(fill_char);
        auto len = std::min(str.size(), value.size());
        std::memcpy(value.data(), str.data(), len);
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set("");
    }

  protected:
    std::array<char, 10> value;
};
}
