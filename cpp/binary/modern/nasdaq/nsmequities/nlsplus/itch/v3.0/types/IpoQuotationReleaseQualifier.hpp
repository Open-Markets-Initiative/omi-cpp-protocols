#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Denotes whether the release time is anticipated or the release has been cancelled or postponed
struct IpoQuotationReleaseQualifier {

    static constexpr auto name = "Ipo Quotation Release Qualifier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IpoQuotationReleaseQualifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IpoQuotationReleaseQualifier(const char &value)
     : value{ value } {}

    // get value of IpoQuotationReleaseQualifier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
