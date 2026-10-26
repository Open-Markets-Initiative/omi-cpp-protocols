#include "EndOfMessageMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

EndOfMessageMessage::EndOfMessageMessage(std::uint8_t multicast_group_number, std::uint8_t number_of_system_reboots, std::uint32_t next_sequence_number)
  : multicast_group_number_(multicast_group_number), number_of_system_reboots_(number_of_system_reboots), next_sequence_number_(next_sequence_number) {}

std::uint8_t EndOfMessageMessage::multicast_group_number() const { return multicast_group_number_; }
void EndOfMessageMessage::set_multicast_group_number(std::uint8_t value) { multicast_group_number_ = value; }

std::uint8_t EndOfMessageMessage::number_of_system_reboots() const { return number_of_system_reboots_; }
void EndOfMessageMessage::set_number_of_system_reboots(std::uint8_t value) { number_of_system_reboots_ = value; }

std::uint32_t EndOfMessageMessage::next_sequence_number() const { return next_sequence_number_; }
void EndOfMessageMessage::set_next_sequence_number(std::uint32_t value) { next_sequence_number_ = value; }

TcpMessageCode EndOfMessageMessage::type() const { return message_type; }

std::string_view EndOfMessageMessage::name() const { return "End Of Message Message"; }

std::size_t EndOfMessageMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfMessageMessage", wire_size, length);

    multicast_group_number_ = wire::read_u8(data + offset);
    offset += 1;

    number_of_system_reboots_ = wire::read_u8(data + offset);
    offset += 1;

    next_sequence_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t EndOfMessageMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfMessageMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(multicast_group_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_system_reboots_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(next_sequence_number_));
    offset += 4;

    return offset;
}

std::size_t EndOfMessageMessage::encoded_size() const {
    return wire_size;
}

void EndOfMessageMessage::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> EndOfMessageMessage::clone() const {
    return std::make_unique<EndOfMessageMessage>(*this);
}

void EndOfMessageMessage::print(std::ostream& out) const {
    out << "EndOfMessageMessage{";
    out << "multicast_group_number=";
    out << static_cast<int>(multicast_group_number_);
    out << ", number_of_system_reboots=";
    out << static_cast<int>(number_of_system_reboots_);
    out << ", next_sequence_number=";
    out << next_sequence_number_;
    out << '}';
}

bool EndOfMessageMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const EndOfMessageMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfMessageMessage::operator==(const EndOfMessageMessage& other) const {
    return multicast_group_number_ == other.multicast_group_number_
        && number_of_system_reboots_ == other.number_of_system_reboots_
        && next_sequence_number_ == other.next_sequence_number_;
}

bool EndOfMessageMessage::operator!=(const EndOfMessageMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
