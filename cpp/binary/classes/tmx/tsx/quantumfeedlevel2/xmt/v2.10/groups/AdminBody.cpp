// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: groups/AdminBody.cpp
#include "AdminBody.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

AdminBody::AdminBody(SourceId source_id, std::uint16_t stream_id, std::uint8_t sequence_0, std::uint32_t sequence_1)
  : source_id_(source_id), stream_id_(stream_id), sequence_0_(sequence_0), sequence_1_(sequence_1) {}

SourceId AdminBody::source_id() const { return source_id_; }
void AdminBody::set_source_id(SourceId value) { source_id_ = value; }

std::uint16_t AdminBody::stream_id() const { return stream_id_; }
void AdminBody::set_stream_id(std::uint16_t value) { stream_id_ = value; }

std::uint8_t AdminBody::sequence_0() const { return sequence_0_; }
void AdminBody::set_sequence_0(std::uint8_t value) { sequence_0_ = value; }

std::uint32_t AdminBody::sequence_1() const { return sequence_1_; }
void AdminBody::set_sequence_1(std::uint32_t value) { sequence_1_ = value; }

std::size_t AdminBody::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AdminBody", wire_size, length);

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

std::size_t AdminBody::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdminBody", wire_size, capacity);

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

std::size_t AdminBody::encoded_size() const {
    return wire_size;
}

void AdminBody::print(std::ostream& out) const {
    out << "AdminBody{";
    out << "source_id=";
    out << source_id_;
    out << ", stream_id=";
    out << stream_id_;
    out << ", sequence_0=";
    out << static_cast<int>(sequence_0_);
    out << ", sequence_1=";
    out << sequence_1_;
    out << '}';
}

bool AdminBody::operator==(const AdminBody& other) const {
    return source_id_ == other.source_id_
        && stream_id_ == other.stream_id_
        && sequence_0_ == other.sequence_0_
        && sequence_1_ == other.sequence_1_;
}

bool AdminBody::operator!=(const AdminBody& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const AdminBody& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
