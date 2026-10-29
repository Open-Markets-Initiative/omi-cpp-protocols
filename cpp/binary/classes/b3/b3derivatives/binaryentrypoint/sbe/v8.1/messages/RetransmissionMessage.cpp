#include "RetransmissionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

RetransmissionMessage::RetransmissionMessage(std::uint32_t session_id, std::chrono::nanoseconds request_timestamp, std::uint32_t next_seq_no, std::uint32_t count)
  : session_id_(session_id), request_timestamp_(request_timestamp), next_seq_no_(next_seq_no), count_(count) {}

std::uint32_t RetransmissionMessage::session_id() const { return session_id_; }
void RetransmissionMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::chrono::nanoseconds RetransmissionMessage::request_timestamp() const { return request_timestamp_; }
void RetransmissionMessage::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

std::uint32_t RetransmissionMessage::next_seq_no() const { return next_seq_no_; }
void RetransmissionMessage::set_next_seq_no(std::uint32_t value) { next_seq_no_ = value; }

std::uint32_t RetransmissionMessage::count() const { return count_; }
void RetransmissionMessage::set_count(std::uint32_t value) { count_ = value; }

MessageCode RetransmissionMessage::type() const { return message_type; }

std::string_view RetransmissionMessage::name() const { return "Retransmission Message"; }

std::size_t RetransmissionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetransmissionMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    next_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    count_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t RetransmissionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetransmissionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(next_seq_no_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(count_));
    offset += 4;

    return offset;
}

std::size_t RetransmissionMessage::encoded_size() const {
    return wire_size;
}

void RetransmissionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetransmissionMessage::clone() const {
    return std::make_unique<RetransmissionMessage>(*this);
}

void RetransmissionMessage::print(std::ostream& out) const {
    out << "RetransmissionMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", next_seq_no=";
    out << next_seq_no_;
    out << ", count=";
    out << count_;
    out << '}';
}

bool RetransmissionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetransmissionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetransmissionMessage::operator==(const RetransmissionMessage& other) const {
    return session_id_ == other.session_id_
        && request_timestamp_ == other.request_timestamp_
        && next_seq_no_ == other.next_seq_no_
        && count_ == other.count_;
}

bool RetransmissionMessage::operator!=(const RetransmissionMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
