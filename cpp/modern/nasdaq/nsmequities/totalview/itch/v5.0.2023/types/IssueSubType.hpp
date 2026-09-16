#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Identifies the security sub-type for the issue as assigned by NASDAQ
struct IssueSubType {

    static constexpr auto name = "Issue Sub Type";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IssueSubType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueSubType(const type &value)
     : value{ value } {}

    // get value of IssueSubType field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
