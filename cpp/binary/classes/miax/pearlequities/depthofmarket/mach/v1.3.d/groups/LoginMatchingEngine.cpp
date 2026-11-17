// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: groups/LoginMatchingEngine.cpp
#include "LoginMatchingEngine.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

LoginMatchingEngine::LoginMatchingEngine(LoginStatus login_status, std::uint8_t trading_session_id, std::uint64_t highest_sequence_number)
  : login_status_(login_status), trading_session_id_(trading_session_id), highest_sequence_number_(highest_sequence_number) {}

LoginStatus LoginMatchingEngine::login_status() const { return login_status_; }
void LoginMatchingEngine::set_login_status(LoginStatus value) { login_status_ = value; }

std::uint8_t LoginMatchingEngine::trading_session_id() const { return trading_session_id_; }
void LoginMatchingEngine::set_trading_session_id(std::uint8_t value) { trading_session_id_ = value; }

std::uint64_t LoginMatchingEngine::highest_sequence_number() const { return highest_sequence_number_; }
void LoginMatchingEngine::set_highest_sequence_number(std::uint64_t value) { highest_sequence_number_ = value; }

std::size_t LoginMatchingEngine::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginMatchingEngine", wire_size, length);

    login_status_ = static_cast<LoginStatus>(wire::read_char(data + offset));
    offset += 1;

    trading_session_id_ = wire::read_u8(data + offset);
    offset += 1;

    highest_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t LoginMatchingEngine::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginMatchingEngine", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(login_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(highest_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t LoginMatchingEngine::encoded_size() const {
    return wire_size;
}

void LoginMatchingEngine::print(std::ostream& out) const {
    out << "LoginMatchingEngine{";
    out << "login_status=";
    out << login_status_;
    out << ", trading_session_id=";
    out << static_cast<int>(trading_session_id_);
    out << ", highest_sequence_number=";
    out << highest_sequence_number_;
    out << '}';
}

bool LoginMatchingEngine::operator==(const LoginMatchingEngine& other) const {
    return login_status_ == other.login_status_
        && trading_session_id_ == other.trading_session_id_
        && highest_sequence_number_ == other.highest_sequence_number_;
}

bool LoginMatchingEngine::operator!=(const LoginMatchingEngine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LoginMatchingEngine& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
