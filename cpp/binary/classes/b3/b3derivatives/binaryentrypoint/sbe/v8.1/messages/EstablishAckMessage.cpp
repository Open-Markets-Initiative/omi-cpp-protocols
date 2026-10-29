#include "EstablishAckMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

EstablishAckMessage::EstablishAckMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, std::uint64_t keep_alive_interval, std::uint32_t next_seq_no, std::uint32_t last_incoming_seq_no)
  : session_id_(session_id), session_ver_id_(session_ver_id), request_timestamp_(request_timestamp), keep_alive_interval_(keep_alive_interval), next_seq_no_(next_seq_no), last_incoming_seq_no_(last_incoming_seq_no) {}

std::uint32_t EstablishAckMessage::session_id() const { return session_id_; }
void EstablishAckMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t EstablishAckMessage::session_ver_id() const { return session_ver_id_; }
void EstablishAckMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

std::chrono::nanoseconds EstablishAckMessage::request_timestamp() const { return request_timestamp_; }
void EstablishAckMessage::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

std::uint64_t EstablishAckMessage::keep_alive_interval() const { return keep_alive_interval_; }
void EstablishAckMessage::set_keep_alive_interval(std::uint64_t value) { keep_alive_interval_ = value; }

std::uint32_t EstablishAckMessage::next_seq_no() const { return next_seq_no_; }
void EstablishAckMessage::set_next_seq_no(std::uint32_t value) { next_seq_no_ = value; }

std::uint32_t EstablishAckMessage::last_incoming_seq_no() const { return last_incoming_seq_no_; }
void EstablishAckMessage::set_last_incoming_seq_no(std::uint32_t value) { last_incoming_seq_no_ = value; }

MessageCode EstablishAckMessage::type() const { return message_type; }

std::string_view EstablishAckMessage::name() const { return "Establish Ack Message"; }

std::size_t EstablishAckMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EstablishAckMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    keep_alive_interval_ = wire::read_u64_le(data + offset);
    offset += 8;

    next_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    last_incoming_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t EstablishAckMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EstablishAckMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(keep_alive_interval_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(next_seq_no_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_incoming_seq_no_));
    offset += 4;

    return offset;
}

std::size_t EstablishAckMessage::encoded_size() const {
    return wire_size;
}

void EstablishAckMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EstablishAckMessage::clone() const {
    return std::make_unique<EstablishAckMessage>(*this);
}

void EstablishAckMessage::print(std::ostream& out) const {
    out << "EstablishAckMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", keep_alive_interval=";
    out << keep_alive_interval_;
    out << ", next_seq_no=";
    out << next_seq_no_;
    out << ", last_incoming_seq_no=";
    out << last_incoming_seq_no_;
    out << '}';
}

bool EstablishAckMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EstablishAckMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EstablishAckMessage::operator==(const EstablishAckMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && request_timestamp_ == other.request_timestamp_
        && keep_alive_interval_ == other.keep_alive_interval_
        && next_seq_no_ == other.next_seq_no_
        && last_incoming_seq_no_ == other.last_incoming_seq_no_;
}

bool EstablishAckMessage::operator!=(const EstablishAckMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
