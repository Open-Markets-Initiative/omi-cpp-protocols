#include "RetransmitRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

RetransmitRequestMessage::RetransmitRequestMessage(std::uint32_t session_id, std::chrono::nanoseconds timestamp, std::uint32_t from_seq_no, std::uint32_t count)
  : session_id_(session_id), timestamp_(timestamp), from_seq_no_(from_seq_no), count_(count) {}

std::uint32_t RetransmitRequestMessage::session_id() const { return session_id_; }
void RetransmitRequestMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::chrono::nanoseconds RetransmitRequestMessage::timestamp() const { return timestamp_; }
void RetransmitRequestMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t RetransmitRequestMessage::from_seq_no() const { return from_seq_no_; }
void RetransmitRequestMessage::set_from_seq_no(std::uint32_t value) { from_seq_no_ = value; }

std::uint32_t RetransmitRequestMessage::count() const { return count_; }
void RetransmitRequestMessage::set_count(std::uint32_t value) { count_ = value; }

MessageCode RetransmitRequestMessage::type() const { return message_type; }

std::string_view RetransmitRequestMessage::name() const { return "Retransmit Request Message"; }

std::size_t RetransmitRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetransmitRequestMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    from_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    count_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t RetransmitRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetransmitRequestMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(from_seq_no_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(count_));
    offset += 4;

    return offset;
}

std::size_t RetransmitRequestMessage::encoded_size() const {
    return wire_size;
}

void RetransmitRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetransmitRequestMessage::clone() const {
    return std::make_unique<RetransmitRequestMessage>(*this);
}

void RetransmitRequestMessage::print(std::ostream& out) const {
    out << "RetransmitRequestMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", from_seq_no=";
    out << from_seq_no_;
    out << ", count=";
    out << count_;
    out << '}';
}

bool RetransmitRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetransmitRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetransmitRequestMessage::operator==(const RetransmitRequestMessage& other) const {
    return session_id_ == other.session_id_
        && timestamp_ == other.timestamp_
        && from_seq_no_ == other.from_seq_no_
        && count_ == other.count_;
}

bool RetransmitRequestMessage::operator!=(const RetransmitRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
