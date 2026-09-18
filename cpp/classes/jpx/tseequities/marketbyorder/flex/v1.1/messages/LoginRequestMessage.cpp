#include "LoginRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

LoginRequestMessage::LoginRequestMessage(const std::string& user_id, std::uint8_t multicast_group_number, std::uint8_t number_of_system_reboots, std::uint32_t sequence_number, std::uint32_t requested_message_count)
  : user_id_(user_id), multicast_group_number_(multicast_group_number), number_of_system_reboots_(number_of_system_reboots), sequence_number_(sequence_number), requested_message_count_(requested_message_count) {}

const std::string& LoginRequestMessage::user_id() const { return user_id_; }
std::string& LoginRequestMessage::user_id() { return user_id_; }
void LoginRequestMessage::set_user_id(const std::string& value) { user_id_ = value; }

std::uint8_t LoginRequestMessage::multicast_group_number() const { return multicast_group_number_; }
void LoginRequestMessage::set_multicast_group_number(std::uint8_t value) { multicast_group_number_ = value; }

std::uint8_t LoginRequestMessage::number_of_system_reboots() const { return number_of_system_reboots_; }
void LoginRequestMessage::set_number_of_system_reboots(std::uint8_t value) { number_of_system_reboots_ = value; }

std::uint32_t LoginRequestMessage::sequence_number() const { return sequence_number_; }
void LoginRequestMessage::set_sequence_number(std::uint32_t value) { sequence_number_ = value; }

std::uint32_t LoginRequestMessage::requested_message_count() const { return requested_message_count_; }
void LoginRequestMessage::set_requested_message_count(std::uint32_t value) { requested_message_count_ = value; }

TcpMessageCode LoginRequestMessage::type() const { return message_type; }

std::string_view LoginRequestMessage::name() const { return "Login Request Message"; }

std::size_t LoginRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginRequestMessage", wire_size, length);

    user_id_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    multicast_group_number_ = wire::read_u8(data + offset);
    offset += 1;

    number_of_system_reboots_ = wire::read_u8(data + offset);
    offset += 1;

    sequence_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    requested_message_count_ = wire::read_u24_be(data + offset);
    offset += 3;

    return offset;
}

std::size_t LoginRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginRequestMessage", wire_size, capacity);

    wire::write_text(data + offset, 6, ' ', user_id_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(multicast_group_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_system_reboots_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(sequence_number_));
    offset += 4;

    wire::write_u24_be(data + offset, static_cast<std::uint32_t>(requested_message_count_));
    offset += 3;

    return offset;
}

std::size_t LoginRequestMessage::encoded_size() const {
    return wire_size;
}

void LoginRequestMessage::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginRequestMessage::clone() const {
    return std::make_unique<LoginRequestMessage>(*this);
}

void LoginRequestMessage::print(std::ostream& out) const {
    out << "LoginRequestMessage{";
    out << "user_id=";
    print::text(out, user_id_);
    out << ", multicast_group_number=";
    out << static_cast<int>(multicast_group_number_);
    out << ", number_of_system_reboots=";
    out << static_cast<int>(number_of_system_reboots_);
    out << ", sequence_number=";
    out << sequence_number_;
    out << ", requested_message_count=";
    out << requested_message_count_;
    out << '}';
}

bool LoginRequestMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginRequestMessage::operator==(const LoginRequestMessage& other) const {
    return user_id_ == other.user_id_
        && multicast_group_number_ == other.multicast_group_number_
        && number_of_system_reboots_ == other.number_of_system_reboots_
        && sequence_number_ == other.sequence_number_
        && requested_message_count_ == other.requested_message_count_;
}

bool LoginRequestMessage::operator!=(const LoginRequestMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
