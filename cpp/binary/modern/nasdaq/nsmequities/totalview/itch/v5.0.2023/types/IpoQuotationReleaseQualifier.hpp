#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// IPO Quotation Release Qualifier
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
