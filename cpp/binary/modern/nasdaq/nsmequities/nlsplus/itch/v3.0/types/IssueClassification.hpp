#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Identifies the security class for the issue as assigned by Nasdaq
struct IssueClassification {

    static constexpr auto name = "Issue Classification";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IssueClassification()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IssueClassification(const char &value)
     : value{ value } {}

    // get value of IssueClassification field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
