#include "BidirectionalBusinessHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

BidirectionalBusinessHeader::BidirectionalBusinessHeader(std::uint32_t session_id, std::uint32_t msg_seq_num, std::optional<std::chrono::nanoseconds> sending_time, std::uint8_t poss_resend, std::uint8_t market_segment_id_optional, char padding)
  : session_id_(session_id), msg_seq_num_(msg_seq_num), sending_time_(sending_time), poss_resend_(poss_resend), market_segment_id_optional_(market_segment_id_optional), padding_(padding) {}

std::uint32_t BidirectionalBusinessHeader::session_id() const { return session_id_; }
void BidirectionalBusinessHeader::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint32_t BidirectionalBusinessHeader::msg_seq_num() const { return msg_seq_num_; }
void BidirectionalBusinessHeader::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::optional<std::chrono::nanoseconds> BidirectionalBusinessHeader::sending_time() const { return sending_time_; }
void BidirectionalBusinessHeader::set_sending_time(std::optional<std::chrono::nanoseconds> value) { sending_time_ = value; }

std::uint8_t BidirectionalBusinessHeader::poss_resend() const { return poss_resend_; }
void BidirectionalBusinessHeader::set_poss_resend(std::uint8_t value) { poss_resend_ = value; }

std::uint8_t BidirectionalBusinessHeader::market_segment_id_optional() const { return market_segment_id_optional_; }
void BidirectionalBusinessHeader::set_market_segment_id_optional(std::uint8_t value) { market_segment_id_optional_ = value; }

char BidirectionalBusinessHeader::padding() const { return padding_; }
void BidirectionalBusinessHeader::set_padding(char value) { padding_ = value; }

std::size_t BidirectionalBusinessHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BidirectionalBusinessHeader", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    msg_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    sending_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    poss_resend_ = wire::read_u8(data + offset);
    offset += 1;

    market_segment_id_optional_ = wire::read_u8(data + offset);
    offset += 1;

    padding_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t BidirectionalBusinessHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BidirectionalBusinessHeader", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(msg_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, sending_time_ ? static_cast<std::uint64_t>(sending_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(poss_resend_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_segment_id_optional_));
    offset += 1;

    wire::write_char(data + offset, padding_);
    offset += 1;

    return offset;
}

std::size_t BidirectionalBusinessHeader::encoded_size() const {
    return wire_size;
}

void BidirectionalBusinessHeader::print(std::ostream& out) const {
    out << "BidirectionalBusinessHeader{";
    out << "session_id=";
    out << session_id_;
    out << ", msg_seq_num=";
    out << msg_seq_num_;
    out << ", sending_time=";
    print::optional_duration(out, sending_time_);
    out << ", poss_resend=";
    out << static_cast<int>(poss_resend_);
    out << ", market_segment_id_optional=";
    out << static_cast<int>(market_segment_id_optional_);
    out << ", padding=";
    print::character(out, padding_);
    out << '}';
}

bool BidirectionalBusinessHeader::operator==(const BidirectionalBusinessHeader& other) const {
    return session_id_ == other.session_id_
        && msg_seq_num_ == other.msg_seq_num_
        && sending_time_ == other.sending_time_
        && poss_resend_ == other.poss_resend_
        && market_segment_id_optional_ == other.market_segment_id_optional_
        && padding_ == other.padding_;
}

bool BidirectionalBusinessHeader::operator!=(const BidirectionalBusinessHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BidirectionalBusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
