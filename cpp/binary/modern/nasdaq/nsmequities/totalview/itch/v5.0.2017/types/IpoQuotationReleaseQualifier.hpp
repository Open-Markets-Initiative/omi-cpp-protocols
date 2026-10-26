#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {


// Anticipated quotation release time. This value would be used when NASDAQ Market Operations initially enters the IPO instrument for release.IPO release canceled/postponed.This value would be used when NASDAQ Market Operations cancels or postpones the release of the IPO instrument.
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
