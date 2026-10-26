#include "LoginRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

LoginRequest::LoginRequest(const std::string& sesm_version, const std::string& username, const std::string& computer_id, const std::string& application_protocol, std::uint8_t requested_trading_session_id, std::uint64_t requested_sequence_number)
  : sesm_version_(sesm_version), username_(username), computer_id_(computer_id), application_protocol_(application_protocol), requested_trading_session_id_(requested_trading_session_id), requested_sequence_number_(requested_sequence_number) {}

const std::string& LoginRequest::sesm_version() const { return sesm_version_; }
std::string& LoginRequest::sesm_version() { return sesm_version_; }
void LoginRequest::set_sesm_version(const std::string& value) { sesm_version_ = value; }

const std::string& LoginRequest::username() const { return username_; }
std::string& LoginRequest::username() { return username_; }
void LoginRequest::set_username(const std::string& value) { username_ = value; }

const std::string& LoginRequest::computer_id() const { return computer_id_; }
std::string& LoginRequest::computer_id() { return computer_id_; }
void LoginRequest::set_computer_id(const std::string& value) { computer_id_ = value; }

const std::string& LoginRequest::application_protocol() const { return application_protocol_; }
std::string& LoginRequest::application_protocol() { return application_protocol_; }
void LoginRequest::set_application_protocol(const std::string& value) { application_protocol_ = value; }

std::uint8_t LoginRequest::requested_trading_session_id() const { return requested_trading_session_id_; }
void LoginRequest::set_requested_trading_session_id(std::uint8_t value) { requested_trading_session_id_ = value; }

std::uint64_t LoginRequest::requested_sequence_number() const { return requested_sequence_number_; }
void LoginRequest::set_requested_sequence_number(std::uint64_t value) { requested_sequence_number_ = value; }

TcpMessageCode LoginRequest::type() const { return message_type; }

std::string_view LoginRequest::name() const { return "Login Request"; }

std::size_t LoginRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginRequest", wire_size, length);

    sesm_version_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    username_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    computer_id_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    application_protocol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    requested_trading_session_id_ = wire::read_u8(data + offset);
    offset += 1;

    requested_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t LoginRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginRequest", wire_size, capacity);

    wire::write_text(data + offset, 5, ' ', sesm_version_);
    offset += 5;

    wire::write_text(data + offset, 5, ' ', username_);
    offset += 5;

    wire::write_text(data + offset, 8, ' ', computer_id_);
    offset += 8;

    wire::write_text(data + offset, 8, ' ', application_protocol_);
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(requested_trading_session_id_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(requested_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t LoginRequest::encoded_size() const {
    return wire_size;
}

void LoginRequest::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginRequest::clone() const {
    return std::make_unique<LoginRequest>(*this);
}

void LoginRequest::print(std::ostream& out) const {
    out << "LoginRequest{";
    out << "sesm_version=";
    print::text(out, sesm_version_);
    out << ", username=";
    print::text(out, username_);
    out << ", computer_id=";
    print::text(out, computer_id_);
    out << ", application_protocol=";
    print::text(out, application_protocol_);
    out << ", requested_trading_session_id=";
    out << static_cast<int>(requested_trading_session_id_);
    out << ", requested_sequence_number=";
    out << requested_sequence_number_;
    out << '}';
}

bool LoginRequest::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginRequest::operator==(const LoginRequest& other) const {
    return sesm_version_ == other.sesm_version_
        && username_ == other.username_
        && computer_id_ == other.computer_id_
        && application_protocol_ == other.application_protocol_
        && requested_trading_session_id_ == other.requested_trading_session_id_
        && requested_sequence_number_ == other.requested_sequence_number_;
}

bool LoginRequest::operator!=(const LoginRequest& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
