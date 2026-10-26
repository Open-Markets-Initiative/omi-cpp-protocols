#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct SecurityReferenceDataSupplement {

    static constexpr const char* name = "Security Reference Data Supplement";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0xFFFFFFFF;
static const type maximum_value = 99991231;
static const type minimum_value = 18000101;

    // default constructor
    constexpr SecurityReferenceDataSupplement()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityReferenceDataSupplement(const std::uint32_t value)
     : value{ value } {}

    // get value of SecurityReferenceDataSupplement field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
