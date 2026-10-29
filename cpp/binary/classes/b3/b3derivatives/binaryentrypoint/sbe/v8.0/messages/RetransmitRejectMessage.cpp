#include "RetransmitRejectMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

RetransmitRejectMessage::RetransmitRejectMessage(std::uint32_t session_id, std::chrono::nanoseconds request_timestamp, RetransmitRejectCode retransmit_reject_code)
  : session_id_(session_id), request_timestamp_(request_timestamp), retransmit_reject_code_(retransmit_reject_code) {}

std::uint32_t RetransmitRejectMessage::session_id() const { return session_id_; }
void RetransmitRejectMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::chrono::nanoseconds RetransmitRejectMessage::request_timestamp() const { return request_timestamp_; }
void RetransmitRejectMessage::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

RetransmitRejectCode RetransmitRejectMessage::retransmit_reject_code() const { return retransmit_reject_code_; }
void RetransmitRejectMessage::set_retransmit_reject_code(RetransmitRejectCode value) { retransmit_reject_code_ = value; }

MessageCode RetransmitRejectMessage::type() const { return message_type; }

std::string_view RetransmitRejectMessage::name() const { return "Retransmit Reject Message"; }

std::size_t RetransmitRejectMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetransmitRejectMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    retransmit_reject_code_ = static_cast<RetransmitRejectCode>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t RetransmitRejectMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetransmitRejectMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(retransmit_reject_code_));
    offset += 1;

    return offset;
}

std::size_t RetransmitRejectMessage::encoded_size() const {
    return wire_size;
}

void RetransmitRejectMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetransmitRejectMessage::clone() const {
    return std::make_unique<RetransmitRejectMessage>(*this);
}

void RetransmitRejectMessage::print(std::ostream& out) const {
    out << "RetransmitRejectMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", retransmit_reject_code=";
    out << retransmit_reject_code_;
    out << '}';
}

bool RetransmitRejectMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetransmitRejectMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetransmitRejectMessage::operator==(const RetransmitRejectMessage& other) const {
    return session_id_ == other.session_id_
        && request_timestamp_ == other.request_timestamp_
        && retransmit_reject_code_ == other.retransmit_reject_code_;
}

bool RetransmitRejectMessage::operator!=(const RetransmitRejectMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
