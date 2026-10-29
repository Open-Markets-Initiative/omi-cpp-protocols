#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// document
struct Document {

    static constexpr const char* name = "Document";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Document()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Document(const std::uint32_t value)
     : value{ value } {}

    // get value of Document field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
