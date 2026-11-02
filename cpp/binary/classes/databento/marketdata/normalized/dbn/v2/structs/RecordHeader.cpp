#include "RecordHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

RecordHeader::RecordHeader(std::uint8_t record_length, Rtype rtype, std::uint16_t publisher_id, std::uint32_t instrument_id, std::optional<std::chrono::nanoseconds> ts_event)
  : record_length_(record_length), rtype_(rtype), publisher_id_(publisher_id), instrument_id_(instrument_id), ts_event_(ts_event) {}

std::uint8_t RecordHeader::record_length() const { return record_length_; }
void RecordHeader::set_record_length(std::uint8_t value) { record_length_ = value; }

Rtype RecordHeader::rtype() const { return rtype_; }
void RecordHeader::set_rtype(Rtype value) { rtype_ = value; }

std::uint16_t RecordHeader::publisher_id() const { return publisher_id_; }
void RecordHeader::set_publisher_id(std::uint16_t value) { publisher_id_ = value; }

std::uint32_t RecordHeader::instrument_id() const { return instrument_id_; }
void RecordHeader::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

std::optional<std::chrono::nanoseconds> RecordHeader::ts_event() const { return ts_event_; }
void RecordHeader::set_ts_event(std::optional<std::chrono::nanoseconds> value) { ts_event_ = value; }

std::size_t RecordHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecordHeader", wire_size, length);

    record_length_ = wire::read_u8(data + offset);
    offset += 1;

    rtype_ = static_cast<Rtype>(wire::read_u8(data + offset));
    offset += 1;

    publisher_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    ts_event_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    return offset;
}

std::size_t RecordHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecordHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(record_length_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(rtype_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(publisher_id_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_u64_le(data + offset, ts_event_ ? static_cast<std::uint64_t>(ts_event_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    return offset;
}

std::size_t RecordHeader::encoded_size() const {
    return wire_size;
}

void RecordHeader::print(std::ostream& out) const {
    out << "RecordHeader{";
    out << "record_length=";
    out << static_cast<int>(record_length_);
    out << ", rtype=";
    out << rtype_;
    out << ", publisher_id=";
    out << publisher_id_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", ts_event=";
    print::optional_duration(out, ts_event_);
    out << '}';
}

bool RecordHeader::operator==(const RecordHeader& other) const {
    return record_length_ == other.record_length_
        && rtype_ == other.rtype_
        && publisher_id_ == other.publisher_id_
        && instrument_id_ == other.instrument_id_
        && ts_event_ == other.ts_event_;
}

bool RecordHeader::operator!=(const RecordHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RecordHeader& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
