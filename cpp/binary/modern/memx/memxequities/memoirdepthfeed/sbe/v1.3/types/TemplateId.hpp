#pragma once

#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// T8 Identifier of the message template
struct TemplateId {

    static constexpr auto name = "Template Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TemplateId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TemplateId(const std::uint8_t &value)
     : value{ value } {}

    // get value of TemplateId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
