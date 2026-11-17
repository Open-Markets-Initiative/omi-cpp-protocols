// Databento.MarketData.Normalized.Dbn.v3: bitfields/Flags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace databento::marketdata::normalized::dbn::v3 {

// A bit field indicating event end, message characteristics, and data quality; declared least
// significant bit first
class Flags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    Flags() = default;
    explicit Flags(std::uint8_t raw);

    // Reserved Flag: Bit 0, unused
    bool reserved_flag() const;
    void set_reserved_flag(bool value);

    // Publisher Specific: Indicates a publisher-specific event (bit 1)
    bool publisher_specific() const;
    void set_publisher_specific(bool value);

    // Maybe Bad Book: Indicates an unrecoverable gap was detected in the channel (bit 2)
    bool maybe_bad_book() const;
    void set_maybe_bad_book(bool value);

    // Bad Ts Recv: Indicates the ts_recv value is inaccurate due to clock issues or packet
    // reordering (bit 3)
    bool bad_ts_recv() const;
    void set_bad_ts_recv(bool value);

    // Mbp: Indicates an aggregated price level message, not an individual order (bit 4)
    bool mbp() const;
    void set_mbp(bool value);

    // Snapshot: Indicates the message was sourced from a replay, such as a snapshot server
    // (bit 5)
    bool snapshot() const;
    void set_snapshot(bool value);

    // Tob: Indicates a top-of-book message, not an individual order (bit 6)
    bool tob() const;
    void set_tob(bool value);

    // Last: Marks the last record in a single event for a given instrument_id (bit 7)
    bool last() const;
    void set_last(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Flags& other) const;
    bool operator!=(const Flags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const Flags& value);

} // namespace databento::marketdata::normalized::dbn::v3
