#include "InboundBusinessHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

InboundBusinessHeader::InboundBusinessHeader(std::uint32_t session_id, std::uint32_t msg_seq_num, std::optional<std::chrono::nanoseconds> sending_time, std::uint8_t market_segment_id, char padding)
  : session_id_(session_id), msg_seq_num_(msg_seq_num), sending_time_(sending_time), market_segment_id_(market_segment_id), padding_(padding) {}

std::uint32_t InboundBusinessHeader::session_id() const { return session_id_; }
void InboundBusinessHeader::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint32_t InboundBusinessHeader::msg_seq_num() const { return msg_seq_num_; }
void InboundBusinessHeader::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::optional<std::chrono::nanoseconds> InboundBusinessHeader::sending_time() const { return sending_time_; }
void InboundBusinessHeader::set_sending_time(std::optional<std::chrono::nanoseconds> value) { sending_time_ = value; }

std::uint8_t InboundBusinessHeader::market_segment_id() const { return market_segment_id_; }
void InboundBusinessHeader::set_market_segment_id(std::uint8_t value) { market_segment_id_ = value; }

char InboundBusinessHeader::padding() const { return padding_; }
void InboundBusinessHeader::set_padding(char value) { padding_ = value; }

std::size_t InboundBusinessHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InboundBusinessHeader", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    msg_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    sending_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    market_segment_id_ = wire::read_u8(data + offset);
    offset += 1;

    padding_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t InboundBusinessHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InboundBusinessHeader", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(msg_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, sending_time_ ? static_cast<std::uint64_t>(sending_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_segment_id_));
    offset += 1;

    wire::write_char(data + offset, padding_);
    offset += 1;

    return offset;
}

std::size_t InboundBusinessHeader::encoded_size() const {
    return wire_size;
}

void InboundBusinessHeader::print(std::ostream& out) const {
    out << "InboundBusinessHeader{";
    out << "session_id=";
    out << session_id_;
    out << ", msg_seq_num=";
    out << msg_seq_num_;
    out << ", sending_time=";
    print::optional_duration(out, sending_time_);
    out << ", market_segment_id=";
    out << static_cast<int>(market_segment_id_);
    out << ", padding=";
    print::character(out, padding_);
    out << '}';
}

bool InboundBusinessHeader::operator==(const InboundBusinessHeader& other) const {
    return session_id_ == other.session_id_
        && msg_seq_num_ == other.msg_seq_num_
        && sending_time_ == other.sending_time_
        && market_segment_id_ == other.market_segment_id_
        && padding_ == other.padding_;
}

bool InboundBusinessHeader::operator!=(const InboundBusinessHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InboundBusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
