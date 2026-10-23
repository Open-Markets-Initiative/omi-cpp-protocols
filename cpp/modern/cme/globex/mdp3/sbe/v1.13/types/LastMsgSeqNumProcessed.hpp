#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Sequence number of the last Incremental feed packet processed. This value is used to synchronize the snapshot loop with the real-time feed
struct LastMsgSeqNumProcessed {

    static constexpr const char* name = "Last Msg Seq Num Processed";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastMsgSeqNumProcessed()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastMsgSeqNumProcessed(const std::uint32_t value)
     : value{ value } {}

    // get value of LastMsgSeqNumProcessed field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
