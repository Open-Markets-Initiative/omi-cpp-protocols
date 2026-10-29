#include "OutboundBusinessHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

OutboundBusinessHeader::OutboundBusinessHeader(std::uint32_t session_id, std::uint32_t msg_seq_num, std::optional<std::chrono::nanoseconds> sending_time, std::uint8_t event_indicator, std::uint8_t market_segment_id_optional)
  : session_id_(session_id), msg_seq_num_(msg_seq_num), sending_time_(sending_time), event_indicator_(event_indicator), market_segment_id_optional_(market_segment_id_optional) {}

std::uint32_t OutboundBusinessHeader::session_id() const { return session_id_; }
void OutboundBusinessHeader::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint32_t OutboundBusinessHeader::msg_seq_num() const { return msg_seq_num_; }
void OutboundBusinessHeader::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::optional<std::chrono::nanoseconds> OutboundBusinessHeader::sending_time() const { return sending_time_; }
void OutboundBusinessHeader::set_sending_time(std::optional<std::chrono::nanoseconds> value) { sending_time_ = value; }

std::uint8_t OutboundBusinessHeader::event_indicator() const { return event_indicator_; }
void OutboundBusinessHeader::set_event_indicator(std::uint8_t value) { event_indicator_ = value; }

std::uint8_t OutboundBusinessHeader::market_segment_id_optional() const { return market_segment_id_optional_; }
void OutboundBusinessHeader::set_market_segment_id_optional(std::uint8_t value) { market_segment_id_optional_ = value; }

std::size_t OutboundBusinessHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OutboundBusinessHeader", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    msg_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    sending_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    event_indicator_ = wire::read_u8(data + offset);
    offset += 1;

    market_segment_id_optional_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t OutboundBusinessHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OutboundBusinessHeader", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(msg_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, sending_time_ ? static_cast<std::uint64_t>(sending_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(event_indicator_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_segment_id_optional_));
    offset += 1;

    return offset;
}

std::size_t OutboundBusinessHeader::encoded_size() const {
    return wire_size;
}

void OutboundBusinessHeader::print(std::ostream& out) const {
    out << "OutboundBusinessHeader{";
    out << "session_id=";
    out << session_id_;
    out << ", msg_seq_num=";
    out << msg_seq_num_;
    out << ", sending_time=";
    print::optional_duration(out, sending_time_);
    out << ", event_indicator=";
    out << static_cast<int>(event_indicator_);
    out << ", market_segment_id_optional=";
    out << static_cast<int>(market_segment_id_optional_);
    out << '}';
}

bool OutboundBusinessHeader::operator==(const OutboundBusinessHeader& other) const {
    return session_id_ == other.session_id_
        && msg_seq_num_ == other.msg_seq_num_
        && sending_time_ == other.sending_time_
        && event_indicator_ == other.event_indicator_
        && market_segment_id_optional_ == other.market_segment_id_optional_;
}

bool OutboundBusinessHeader::operator!=(const OutboundBusinessHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OutboundBusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
