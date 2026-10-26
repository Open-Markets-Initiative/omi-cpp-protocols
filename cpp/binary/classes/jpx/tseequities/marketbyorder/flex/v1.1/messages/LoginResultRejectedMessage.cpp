#include "LoginResultRejectedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

LoginResultRejectedMessage::LoginResultRejectedMessage(std::uint8_t multicast_group_number, ResultCode result_code)
  : multicast_group_number_(multicast_group_number), result_code_(result_code) {}

std::uint8_t LoginResultRejectedMessage::multicast_group_number() const { return multicast_group_number_; }
void LoginResultRejectedMessage::set_multicast_group_number(std::uint8_t value) { multicast_group_number_ = value; }

ResultCode LoginResultRejectedMessage::result_code() const { return result_code_; }
void LoginResultRejectedMessage::set_result_code(ResultCode value) { result_code_ = value; }

TcpMessageCode LoginResultRejectedMessage::type() const { return message_type; }

std::string_view LoginResultRejectedMessage::name() const { return "Login Result Rejected Message"; }

std::size_t LoginResultRejectedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginResultRejectedMessage", wire_size, length);

    multicast_group_number_ = wire::read_u8(data + offset);
    offset += 1;

    result_code_ = static_cast<ResultCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t LoginResultRejectedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginResultRejectedMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(multicast_group_number_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(result_code_));
    offset += 1;

    return offset;
}

std::size_t LoginResultRejectedMessage::encoded_size() const {
    return wire_size;
}

void LoginResultRejectedMessage::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginResultRejectedMessage::clone() const {
    return std::make_unique<LoginResultRejectedMessage>(*this);
}

void LoginResultRejectedMessage::print(std::ostream& out) const {
    out << "LoginResultRejectedMessage{";
    out << "multicast_group_number=";
    out << static_cast<int>(multicast_group_number_);
    out << ", result_code=";
    out << result_code_;
    out << '}';
}

bool LoginResultRejectedMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginResultRejectedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginResultRejectedMessage::operator==(const LoginResultRejectedMessage& other) const {
    return multicast_group_number_ == other.multicast_group_number_
        && result_code_ == other.result_code_;
}

bool LoginResultRejectedMessage::operator!=(const LoginResultRejectedMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
