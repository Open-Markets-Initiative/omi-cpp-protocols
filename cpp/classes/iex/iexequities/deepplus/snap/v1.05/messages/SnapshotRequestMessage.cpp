#include "SnapshotRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

SnapshotRequestMessage::SnapshotRequestMessage(const std::string& authentication_token, std::uint32_t channel_id, std::uint32_t session_id, std::uint64_t minimum_sequence_number)
  : authentication_token_(authentication_token), channel_id_(channel_id), session_id_(session_id), minimum_sequence_number_(minimum_sequence_number) {}

const std::string& SnapshotRequestMessage::authentication_token() const { return authentication_token_; }
std::string& SnapshotRequestMessage::authentication_token() { return authentication_token_; }
void SnapshotRequestMessage::set_authentication_token(const std::string& value) { authentication_token_ = value; }

std::uint32_t SnapshotRequestMessage::channel_id() const { return channel_id_; }
void SnapshotRequestMessage::set_channel_id(std::uint32_t value) { channel_id_ = value; }

std::uint32_t SnapshotRequestMessage::session_id() const { return session_id_; }
void SnapshotRequestMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t SnapshotRequestMessage::minimum_sequence_number() const { return minimum_sequence_number_; }
void SnapshotRequestMessage::set_minimum_sequence_number(std::uint64_t value) { minimum_sequence_number_ = value; }

MessageCode SnapshotRequestMessage::type() const { return message_type; }

std::string_view SnapshotRequestMessage::name() const { return "Snapshot Request Message"; }

std::size_t SnapshotRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotRequestMessage", wire_size, length);

    authentication_token_ = wire::read_text(data + offset, 40, ' ');
    offset += 40;

    channel_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    minimum_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t SnapshotRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotRequestMessage", wire_size, capacity);

    wire::write_text(data + offset, 40, ' ', authentication_token_);
    offset += 40;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(channel_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(minimum_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t SnapshotRequestMessage::encoded_size() const {
    return wire_size;
}

void SnapshotRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotRequestMessage::clone() const {
    return std::make_unique<SnapshotRequestMessage>(*this);
}

void SnapshotRequestMessage::print(std::ostream& out) const {
    out << "SnapshotRequestMessage{";
    out << "authentication_token=";
    print::text(out, authentication_token_);
    out << ", channel_id=";
    out << channel_id_;
    out << ", session_id=";
    out << session_id_;
    out << ", minimum_sequence_number=";
    out << minimum_sequence_number_;
    out << '}';
}

bool SnapshotRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotRequestMessage::operator==(const SnapshotRequestMessage& other) const {
    return authentication_token_ == other.authentication_token_
        && channel_id_ == other.channel_id_
        && session_id_ == other.session_id_
        && minimum_sequence_number_ == other.minimum_sequence_number_;
}

bool SnapshotRequestMessage::operator!=(const SnapshotRequestMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::snap::v1_05
