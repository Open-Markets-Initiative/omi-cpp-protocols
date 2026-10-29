#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// execRefID
struct ExecRefId {

    static constexpr const char* name = "Exec Ref Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr ExecRefId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecRefId(const std::uint64_t value)
     : value{ value } {}

    // get value of ExecRefId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
