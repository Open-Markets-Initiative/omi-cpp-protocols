#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cqs::output::cta::v2_10_a {


// Contains the FINRA Market Maker ID of the quoting participant on FINRA's Alternative Display Facility or the FINRA ADF Identifier 'FNRA'
struct FinraMarketMakerId {

    static constexpr auto name = "Finra Market Maker Id";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FinraMarketMakerId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraMarketMakerId(const type &value)
     : value{ value } {}

    // get value of FinraMarketMakerId field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
