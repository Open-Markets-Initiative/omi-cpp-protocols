#include "LoginResultMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

LoginResultMessage::LoginResultMessage(std::uint8_t multicast_group_number, ResultCode result_code)
  : multicast_group_number_(multicast_group_number), result_code_(result_code) {}

std::uint8_t LoginResultMessage::multicast_group_number() const { return multicast_group_number_; }
void LoginResultMessage::set_multicast_group_number(std::uint8_t value) { multicast_group_number_ = value; }

ResultCode LoginResultMessage::result_code() const { return result_code_; }
void LoginResultMessage::set_result_code(ResultCode value) { result_code_ = value; }

TcpMessageCode LoginResultMessage::type() const { return message_type; }

std::string_view LoginResultMessage::name() const { return "Login Result Message"; }

std::size_t LoginResultMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginResultMessage", wire_size, length);

    multicast_group_number_ = wire::read_u8(data + offset);
    offset += 1;

    result_code_ = static_cast<ResultCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t LoginResultMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginResultMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(multicast_group_number_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(result_code_));
    offset += 1;

    return offset;
}

std::size_t LoginResultMessage::encoded_size() const {
    return wire_size;
}

void LoginResultMessage::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginResultMessage::clone() const {
    return std::make_unique<LoginResultMessage>(*this);
}

void LoginResultMessage::print(std::ostream& out) const {
    out << "LoginResultMessage{";
    out << "multicast_group_number=";
    out << static_cast<int>(multicast_group_number_);
    out << ", result_code=";
    out << result_code_;
    out << '}';
}

bool LoginResultMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginResultMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginResultMessage::operator==(const LoginResultMessage& other) const {
    return multicast_group_number_ == other.multicast_group_number_
        && result_code_ == other.result_code_;
}

bool LoginResultMessage::operator!=(const LoginResultMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
