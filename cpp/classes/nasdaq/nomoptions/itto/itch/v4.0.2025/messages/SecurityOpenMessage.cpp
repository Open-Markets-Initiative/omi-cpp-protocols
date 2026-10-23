#include "SecurityOpenMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

SecurityOpenMessage::SecurityOpenMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, OpenState open_state)
  : tracking_number_(tracking_number), timestamp_(timestamp), option_id_(option_id), open_state_(open_state) {}

std::uint16_t SecurityOpenMessage::tracking_number() const { return tracking_number_; }
void SecurityOpenMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds SecurityOpenMessage::timestamp() const { return timestamp_; }
void SecurityOpenMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t SecurityOpenMessage::option_id() const { return option_id_; }
void SecurityOpenMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

OpenState SecurityOpenMessage::open_state() const { return open_state_; }
void SecurityOpenMessage::set_open_state(OpenState value) { open_state_ = value; }

SequencedMessageCode SecurityOpenMessage::type() const { return message_type; }

std::string_view SecurityOpenMessage::name() const { return "Security Open Message"; }

std::size_t SecurityOpenMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityOpenMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    open_state_ = static_cast<OpenState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SecurityOpenMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityOpenMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(open_state_));
    offset += 1;

    return offset;
}

std::size_t SecurityOpenMessage::encoded_size() const {
    return wire_size;
}

void SecurityOpenMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> SecurityOpenMessage::clone() const {
    return std::make_unique<SecurityOpenMessage>(*this);
}

void SecurityOpenMessage::print(std::ostream& out) const {
    out << "SecurityOpenMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", open_state=";
    out << open_state_;
    out << '}';
}

bool SecurityOpenMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SecurityOpenMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityOpenMessage::operator==(const SecurityOpenMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && option_id_ == other.option_id_
        && open_state_ == other.open_state_;
}

bool SecurityOpenMessage::operator!=(const SecurityOpenMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
