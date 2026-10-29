#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Packet sequence number, contiguous and incremented per multicast address and port
struct ApplSeqNum {

    static constexpr const char* name = "Appl Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ApplSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ApplSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of ApplSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
