#pragma once

#include <cstddef>
#include <array>
#include <string_view>
#include <algorithm>
#include "../cache/Required.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// market_day_identifier
struct market_day_identifier {

    static constexpr const char* name = "market_day_identifier";
    static constexpr std::size_t size = 9;
    static constexpr char fill_char = '0';
    static constexpr bool is_optional = false;

    using result_type = required<std::string_view>;
    using storage_type = required<std::array<char, 9>>;

    constexpr market_day_identifier() {
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
    std::array<char, 9> value;
};
}
