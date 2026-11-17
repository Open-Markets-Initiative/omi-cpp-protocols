// Databento.MarketData.Normalized.Dbn.v2: messages/ErrorMsg.cpp
#include "ErrorMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

ErrorMsg::ErrorMsg(const std::string& err, ErrorCode error_code, std::uint8_t is_last)
  : err_(err), error_code_(error_code), is_last_(is_last) {}

const std::string& ErrorMsg::err() const { return err_; }
std::string& ErrorMsg::err() { return err_; }
void ErrorMsg::set_err(const std::string& value) { err_ = value; }

ErrorCode ErrorMsg::error_code() const { return error_code_; }
void ErrorMsg::set_error_code(ErrorCode value) { error_code_ = value; }

std::uint8_t ErrorMsg::is_last() const { return is_last_; }
void ErrorMsg::set_is_last(std::uint8_t value) { is_last_ = value; }

MessageCode ErrorMsg::type() const { return message_type; }

std::string_view ErrorMsg::name() const { return "Error Msg"; }

std::size_t ErrorMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ErrorMsg", wire_size, length);

    err_ = wire::read_text(data + offset, 302, '\0');
    offset += 302;

    error_code_ = static_cast<ErrorCode>(wire::read_u8(data + offset));
    offset += 1;

    is_last_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ErrorMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ErrorMsg", wire_size, capacity);

    wire::write_text(data + offset, 302, '\0', err_);
    offset += 302;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(error_code_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(is_last_));
    offset += 1;

    return offset;
}

std::size_t ErrorMsg::encoded_size() const {
    return wire_size;
}

void ErrorMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ErrorMsg::clone() const {
    return std::make_unique<ErrorMsg>(*this);
}

void ErrorMsg::print(std::ostream& out) const {
    out << "ErrorMsg{";
    out << "err=";
    print::text(out, err_);
    out << ", error_code=";
    out << error_code_;
    out << ", is_last=";
    out << static_cast<int>(is_last_);
    out << '}';
}

bool ErrorMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ErrorMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool ErrorMsg::operator==(const ErrorMsg& other) const {
    return err_ == other.err_
        && error_code_ == other.error_code_
        && is_last_ == other.is_last_;
}

bool ErrorMsg::operator!=(const ErrorMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v2
