#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// lastIncomingSeqNo
struct LastIncomingSeqNo {

    static constexpr const char* name = "Last Incoming Seq No";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastIncomingSeqNo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastIncomingSeqNo(const std::uint32_t value)
     : value{ value } {}

    // get value of LastIncomingSeqNo field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
