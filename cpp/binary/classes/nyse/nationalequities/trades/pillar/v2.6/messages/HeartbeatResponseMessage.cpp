#include "HeartbeatResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

HeartbeatResponseMessage::HeartbeatResponseMessage(const std::string& source_id)
  : source_id_(source_id) {}

const std::string& HeartbeatResponseMessage::source_id() const { return source_id_; }
std::string& HeartbeatResponseMessage::source_id() { return source_id_; }
void HeartbeatResponseMessage::set_source_id(const std::string& value) { source_id_ = value; }

MessageCode HeartbeatResponseMessage::type() const { return message_type; }

std::string_view HeartbeatResponseMessage::name() const { return "Heartbeat Response Message"; }

std::size_t HeartbeatResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("HeartbeatResponseMessage", wire_size, length);

    source_id_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    return offset;
}

std::size_t HeartbeatResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("HeartbeatResponseMessage", wire_size, capacity);

    wire::write_text(data + offset, 10, '\0', source_id_);
    offset += 10;

    return offset;
}

std::size_t HeartbeatResponseMessage::encoded_size() const {
    return wire_size;
}

void HeartbeatResponseMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> HeartbeatResponseMessage::clone() const {
    return std::make_unique<HeartbeatResponseMessage>(*this);
}

void HeartbeatResponseMessage::print(std::ostream& out) const {
    out << "HeartbeatResponseMessage{";
    out << "source_id=";
    print::text(out, source_id_);
    out << '}';
}

bool HeartbeatResponseMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const HeartbeatResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool HeartbeatResponseMessage::operator==(const HeartbeatResponseMessage& other) const {
    return source_id_ == other.source_id_;
}

bool HeartbeatResponseMessage::operator!=(const HeartbeatResponseMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
