// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BusinessHeader.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/SourceId.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Xmt Business Header
class BusinessHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    BusinessHeader() = default;
    BusinessHeader(std::uint8_t msg_version, SourceId source_id, std::uint16_t stream_id, std::uint8_t sequence_0, std::uint32_t sequence_1);

    // Msg Version: Message version number
    std::uint8_t msg_version() const;
    void set_msg_version(std::uint8_t value);

    // Source Id: Source Id of the Business message
    SourceId source_id() const;
    void set_source_id(SourceId value);

    // Stream Id: Stream Id per Source Id of the Business message
    std::uint16_t stream_id() const;
    void set_stream_id(std::uint16_t value);

    // Sequence 0: Reserved for future expansion, Value is 0
    std::uint8_t sequence_0() const;
    void set_sequence_0(std::uint8_t value);

    // Sequence 1: Sequence per Stream Id of the Business message
    std::uint32_t sequence_1() const;
    void set_sequence_1(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BusinessHeader& other) const;
    bool operator!=(const BusinessHeader& other) const;

  private:
    std::uint8_t msg_version_{};
    SourceId source_id_{};
    std::uint16_t stream_id_{};
    std::uint8_t sequence_0_{};
    std::uint32_t sequence_1_{};
};

std::ostream& operator<<(std::ostream& out, const BusinessHeader& value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
