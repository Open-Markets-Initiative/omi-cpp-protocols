#include "LoginResultAcceptedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

LoginResultAcceptedMessage::LoginResultAcceptedMessage(std::uint8_t multicast_group_number, ResultCode result_code)
  : multicast_group_number_(multicast_group_number), result_code_(result_code) {}

std::uint8_t LoginResultAcceptedMessage::multicast_group_number() const { return multicast_group_number_; }
void LoginResultAcceptedMessage::set_multicast_group_number(std::uint8_t value) { multicast_group_number_ = value; }

ResultCode LoginResultAcceptedMessage::result_code() const { return result_code_; }
void LoginResultAcceptedMessage::set_result_code(ResultCode value) { result_code_ = value; }

TcpMessageCode LoginResultAcceptedMessage::type() const { return message_type; }

std::string_view LoginResultAcceptedMessage::name() const { return "Login Result Accepted Message"; }

std::size_t LoginResultAcceptedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginResultAcceptedMessage", wire_size, length);

    multicast_group_number_ = wire::read_u8(data + offset);
    offset += 1;

    result_code_ = static_cast<ResultCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t LoginResultAcceptedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginResultAcceptedMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(multicast_group_number_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(result_code_));
    offset += 1;

    return offset;
}

std::size_t LoginResultAcceptedMessage::encoded_size() const {
    return wire_size;
}

void LoginResultAcceptedMessage::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginResultAcceptedMessage::clone() const {
    return std::make_unique<LoginResultAcceptedMessage>(*this);
}

void LoginResultAcceptedMessage::print(std::ostream& out) const {
    out << "LoginResultAcceptedMessage{";
    out << "multicast_group_number=";
    out << static_cast<int>(multicast_group_number_);
    out << ", result_code=";
    out << result_code_;
    out << '}';
}

bool LoginResultAcceptedMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginResultAcceptedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginResultAcceptedMessage::operator==(const LoginResultAcceptedMessage& other) const {
    return multicast_group_number_ == other.multicast_group_number_
        && result_code_ == other.result_code_;
}

bool LoginResultAcceptedMessage::operator!=(const LoginResultAcceptedMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
