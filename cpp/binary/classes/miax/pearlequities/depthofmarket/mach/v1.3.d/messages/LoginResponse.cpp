#include "LoginResponse.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

LoginResponse::LoginResponse(std::uint8_t number_of_matching_engines, LoginStatus login_status, std::uint8_t trading_session_id, std::uint64_t highest_sequence_number)
  : number_of_matching_engines_(number_of_matching_engines), login_status_(login_status), trading_session_id_(trading_session_id), highest_sequence_number_(highest_sequence_number) {}

std::uint8_t LoginResponse::number_of_matching_engines() const { return number_of_matching_engines_; }
void LoginResponse::set_number_of_matching_engines(std::uint8_t value) { number_of_matching_engines_ = value; }

LoginStatus LoginResponse::login_status() const { return login_status_; }
void LoginResponse::set_login_status(LoginStatus value) { login_status_ = value; }

std::uint8_t LoginResponse::trading_session_id() const { return trading_session_id_; }
void LoginResponse::set_trading_session_id(std::uint8_t value) { trading_session_id_ = value; }

std::uint64_t LoginResponse::highest_sequence_number() const { return highest_sequence_number_; }
void LoginResponse::set_highest_sequence_number(std::uint64_t value) { highest_sequence_number_ = value; }

TcpMessageCode LoginResponse::type() const { return message_type; }

std::string_view LoginResponse::name() const { return "Login Response"; }

std::size_t LoginResponse::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginResponse", wire_size, length);

    number_of_matching_engines_ = wire::read_u8(data + offset);
    offset += 1;

    login_status_ = static_cast<LoginStatus>(wire::read_char(data + offset));
    offset += 1;

    trading_session_id_ = wire::read_u8(data + offset);
    offset += 1;

    highest_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t LoginResponse::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginResponse", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_matching_engines_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(login_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(highest_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t LoginResponse::encoded_size() const {
    return wire_size;
}

void LoginResponse::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginResponse::clone() const {
    return std::make_unique<LoginResponse>(*this);
}

void LoginResponse::print(std::ostream& out) const {
    out << "LoginResponse{";
    out << "number_of_matching_engines=";
    out << static_cast<int>(number_of_matching_engines_);
    out << ", login_status=";
    out << login_status_;
    out << ", trading_session_id=";
    out << static_cast<int>(trading_session_id_);
    out << ", highest_sequence_number=";
    out << highest_sequence_number_;
    out << '}';
}

bool LoginResponse::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginResponse*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginResponse::operator==(const LoginResponse& other) const {
    return number_of_matching_engines_ == other.number_of_matching_engines_
        && login_status_ == other.login_status_
        && trading_session_id_ == other.trading_session_id_
        && highest_sequence_number_ == other.highest_sequence_number_;
}

bool LoginResponse::operator!=(const LoginResponse& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
