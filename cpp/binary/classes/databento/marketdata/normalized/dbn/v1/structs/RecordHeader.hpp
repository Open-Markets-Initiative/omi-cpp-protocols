#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/Rtype.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// DBN common header of every record
class RecordHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    RecordHeader() = default;
    RecordHeader(std::uint8_t record_length, Rtype rtype, std::uint16_t publisher_id, std::uint32_t instrument_id, std::optional<std::chrono::nanoseconds> ts_event);

    // Record Length: The length of the record in 32-bit words, including this header and any
    // ts_out trailer
    std::uint8_t record_length() const;
    void set_record_length(std::uint8_t value);

    // Rtype: The record type, which selects the record that follows the header
    Rtype rtype() const;
    void set_rtype(Rtype value);

    // Publisher Id: The publisher ID assigned by Databento, which denotes the dataset and
    // venue
    std::uint16_t publisher_id() const;
    void set_publisher_id(std::uint16_t value);

    // Instrument Id: The numeric instrument ID
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Ts Event: The matching-engine-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_event() const;
    void set_ts_event(std::optional<std::chrono::nanoseconds> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RecordHeader& other) const;
    bool operator!=(const RecordHeader& other) const;

  private:
    std::uint8_t record_length_{};
    Rtype rtype_{};
    std::uint16_t publisher_id_{};
    std::uint32_t instrument_id_{};
    std::optional<std::chrono::nanoseconds> ts_event_{};
};

std::ostream& operator<<(std::ostream& out, const RecordHeader& value);

} // namespace databento::marketdata::normalized::dbn::v1
