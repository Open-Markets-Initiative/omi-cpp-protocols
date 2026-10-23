#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Issue Date
struct IssueDate {

    static constexpr const char* name = "Issue Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr IssueDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueDate(const std::uint16_t value)
     : value{ value } {}

    // get value of IssueDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
