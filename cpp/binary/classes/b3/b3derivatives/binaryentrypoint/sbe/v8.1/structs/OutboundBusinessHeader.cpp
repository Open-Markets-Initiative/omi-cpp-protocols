#include "OutboundBusinessHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

OutboundBusinessHeader::OutboundBusinessHeader(std::uint32_t session_id, std::uint32_t msg_seq_num, std::optional<std::chrono::nanoseconds> sending_time, std::uint8_t poss_resend, char padding)
  : session_id_(session_id), msg_seq_num_(msg_seq_num), sending_time_(sending_time), poss_resend_(poss_resend), padding_(padding) {}

std::uint32_t OutboundBusinessHeader::session_id() const { return session_id_; }
void OutboundBusinessHeader::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint32_t OutboundBusinessHeader::msg_seq_num() const { return msg_seq_num_; }
void OutboundBusinessHeader::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::optional<std::chrono::nanoseconds> OutboundBusinessHeader::sending_time() const { return sending_time_; }
void OutboundBusinessHeader::set_sending_time(std::optional<std::chrono::nanoseconds> value) { sending_time_ = value; }

std::uint8_t OutboundBusinessHeader::poss_resend() const { return poss_resend_; }
void OutboundBusinessHeader::set_poss_resend(std::uint8_t value) { poss_resend_ = value; }

char OutboundBusinessHeader::padding() const { return padding_; }
void OutboundBusinessHeader::set_padding(char value) { padding_ = value; }

std::size_t OutboundBusinessHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OutboundBusinessHeader", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    msg_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    sending_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    poss_resend_ = wire::read_u8(data + offset);
    offset += 1;

    padding_ = wire::read_char(data + offset);
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

    wire::write_u8(data + offset, static_cast<std::uint8_t>(poss_resend_));
    offset += 1;

    wire::write_char(data + offset, padding_);
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
    out << ", poss_resend=";
    out << static_cast<int>(poss_resend_);
    out << ", padding=";
    print::character(out, padding_);
    out << '}';
}

bool OutboundBusinessHeader::operator==(const OutboundBusinessHeader& other) const {
    return session_id_ == other.session_id_
        && msg_seq_num_ == other.msg_seq_num_
        && sending_time_ == other.sending_time_
        && poss_resend_ == other.poss_resend_
        && padding_ == other.padding_;
}

bool OutboundBusinessHeader::operator!=(const OutboundBusinessHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OutboundBusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
