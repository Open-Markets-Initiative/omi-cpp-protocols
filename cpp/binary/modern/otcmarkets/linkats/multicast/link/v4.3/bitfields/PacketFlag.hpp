// OtcMarkets.LinkAts.Multicast.Link.v4.3: bitfields/PacketFlag.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Packet Flags
struct PacketFlag {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Packet Flag";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Heartbeat = 0x01;
        static const type SeqNumReset = 0x02;
        static const type Replay = 0x40;
        static const type Test = 0x80;
    };

    // default constructor
    constexpr PacketFlag()
     : value{ 0 } {}

    // A Heartbeat is sent if no business level message has been published for more than a second
    [[nodiscard]] constexpr bool Heartbeat() const {
        return value & mask::Heartbeat;
    }

    // indicates that the channel sequence numbers are being reset to 1
    [[nodiscard]] constexpr bool SeqNumReset() const {
        return value & mask::SeqNumReset;
    }

    // Packet contains replay messages
    [[nodiscard]] constexpr bool Replay() const {
        return value & mask::Replay;
    }

    // Packet contains test messages
    [[nodiscard]] constexpr bool Test() const {
        return value & mask::Test;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
