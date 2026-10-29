#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {

// SBE template identifier of the packet header (e.g., 13004 RefreshHeader / 13005 BeaconMessage)
struct TemplateId {

    static constexpr const char* name = "Template Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0xFFFF;
static const type maximum_value = 65534;
static const type minimum_value = 0;

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
