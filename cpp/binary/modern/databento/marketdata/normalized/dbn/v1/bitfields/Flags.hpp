#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// A bit field indicating event end, message characteristics, and data quality; declared least significant bit first
struct Flags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type ReservedFlag = 0x01;
        static const type PublisherSpecific = 0x02;
        static const type MaybeBadBook = 0x04;
        static const type BadTsRecv = 0x08;
        static const type Mbp = 0x10;
        static const type Snapshot = 0x20;
        static const type Tob = 0x40;
        static const type Last = 0x80;
    };

    // default constructor
    constexpr Flags()
     : value{ 0 } {}

    // Bit 0, unused
    [[nodiscard]] constexpr bool ReservedFlag() const {
        return value & mask::ReservedFlag;
    }

    // Indicates a publisher-specific event (bit 1)
    [[nodiscard]] constexpr bool PublisherSpecific() const {
        return value & mask::PublisherSpecific;
    }

    // Indicates an unrecoverable gap was detected in the channel (bit 2)
    [[nodiscard]] constexpr bool MaybeBadBook() const {
        return value & mask::MaybeBadBook;
    }

    // Indicates the ts_recv value is inaccurate due to clock issues or packet reordering (bit 3)
    [[nodiscard]] constexpr bool BadTsRecv() const {
        return value & mask::BadTsRecv;
    }

    // Indicates an aggregated price level message, not an individual order (bit 4)
    [[nodiscard]] constexpr bool Mbp() const {
        return value & mask::Mbp;
    }

    // Indicates the message was sourced from a replay, such as a snapshot server (bit 5)
    [[nodiscard]] constexpr bool Snapshot() const {
        return value & mask::Snapshot;
    }

    // Indicates a top-of-book message, not an individual order (bit 6)
    [[nodiscard]] constexpr bool Tob() const {
        return value & mask::Tob;
    }

    // Marks the last record in a single event for a given instrument_id (bit 7)
    [[nodiscard]] constexpr bool Last() const {
        return value & mask::Last;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
