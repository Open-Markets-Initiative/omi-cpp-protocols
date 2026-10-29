#include "StreamIdMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

StreamIdMessage::StreamIdMessage(std::uint16_t stream_id, const std::array<std::byte, 2>& reserved_2)
  : stream_id_(stream_id), reserved_2_(reserved_2) {}

std::uint16_t StreamIdMessage::stream_id() const { return stream_id_; }
void StreamIdMessage::set_stream_id(std::uint16_t value) { stream_id_ = value; }

const std::array<std::byte, 2>& StreamIdMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& StreamIdMessage::reserved_2() { return reserved_2_; }
void StreamIdMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode StreamIdMessage::type() const { return message_type; }

std::string_view StreamIdMessage::name() const { return "Stream Id Message"; }

std::size_t StreamIdMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StreamIdMessage", wire_size, length);

    stream_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t StreamIdMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StreamIdMessage", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(stream_id_));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t StreamIdMessage::encoded_size() const {
    return wire_size;
}

void StreamIdMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StreamIdMessage::clone() const {
    return std::make_unique<StreamIdMessage>(*this);
}

void StreamIdMessage::print(std::ostream& out) const {
    out << "StreamIdMessage{";
    out << "stream_id=";
    out << stream_id_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool StreamIdMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StreamIdMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StreamIdMessage::operator==(const StreamIdMessage& other) const {
    return stream_id_ == other.stream_id_
        && reserved_2_ == other.reserved_2_;
}

bool StreamIdMessage::operator!=(const StreamIdMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
