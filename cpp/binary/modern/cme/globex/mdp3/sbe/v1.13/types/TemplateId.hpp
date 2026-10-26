#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// 
struct TemplateId {

    static constexpr const char* name = "Template Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TemplateId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TemplateId(const std::uint16_t value)
     : value{ value } {}

    // get value of TemplateId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
