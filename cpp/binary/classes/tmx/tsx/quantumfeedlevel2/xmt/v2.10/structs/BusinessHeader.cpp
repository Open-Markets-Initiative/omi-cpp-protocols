// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: structs/BusinessHeader.cpp
#include "BusinessHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

BusinessHeader::BusinessHeader(std::uint8_t msg_version, SourceId source_id, std::uint16_t stream_id, std::uint8_t sequence_0, std::uint32_t sequence_1)
  : msg_version_(msg_version), source_id_(source_id), stream_id_(stream_id), sequence_0_(sequence_0), sequence_1_(sequence_1) {}

std::uint8_t BusinessHeader::msg_version() const { return msg_version_; }
void BusinessHeader::set_msg_version(std::uint8_t value) { msg_version_ = value; }

SourceId BusinessHeader::source_id() const { return source_id_; }
void BusinessHeader::set_source_id(SourceId value) { source_id_ = value; }

std::uint16_t BusinessHeader::stream_id() const { return stream_id_; }
void BusinessHeader::set_stream_id(std::uint16_t value) { stream_id_ = value; }

std::uint8_t BusinessHeader::sequence_0() const { return sequence_0_; }
void BusinessHeader::set_sequence_0(std::uint8_t value) { sequence_0_ = value; }

std::uint32_t BusinessHeader::sequence_1() const { return sequence_1_; }
void BusinessHeader::set_sequence_1(std::uint32_t value) { sequence_1_ = value; }

std::size_t BusinessHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BusinessHeader", wire_size, length);

    msg_version_ = wire::read_u8(data + offset);
    offset += 1;

    source_id_ = static_cast<SourceId>(wire::read_char(data + offset));
    offset += 1;

    stream_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    sequence_0_ = wire::read_u8(data + offset);
    offset += 1;

    sequence_1_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t BusinessHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BusinessHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(msg_version_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(source_id_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(stream_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sequence_0_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_1_));
    offset += 4;

    return offset;
}

std::size_t BusinessHeader::encoded_size() const {
    return wire_size;
}

void BusinessHeader::print(std::ostream& out) const {
    out << "BusinessHeader{";
    out << "msg_version=";
    out << static_cast<int>(msg_version_);
    out << ", source_id=";
    out << source_id_;
    out << ", stream_id=";
    out << stream_id_;
    out << ", sequence_0=";
    out << static_cast<int>(sequence_0_);
    out << ", sequence_1=";
    out << sequence_1_;
    out << '}';
}

bool BusinessHeader::operator==(const BusinessHeader& other) const {
    return msg_version_ == other.msg_version_
        && source_id_ == other.source_id_
        && stream_id_ == other.stream_id_
        && sequence_0_ == other.sequence_0_
        && sequence_1_ == other.sequence_1_;
}

bool BusinessHeader::operator!=(const BusinessHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
