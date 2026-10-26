#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// issueDate
struct IssueDate {

    static constexpr const char* name = "Issue Date";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr IssueDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueDate(const std::int32_t value)
     : value{ value } {}

    // get value of IssueDate field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
