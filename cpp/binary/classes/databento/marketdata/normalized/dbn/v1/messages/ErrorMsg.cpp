// Databento.MarketData.Normalized.Dbn.v1: messages/ErrorMsg.cpp
#include "ErrorMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

ErrorMsg::ErrorMsg(const std::string& err)
  : err_(err) {}

const std::string& ErrorMsg::err() const { return err_; }
std::string& ErrorMsg::err() { return err_; }
void ErrorMsg::set_err(const std::string& value) { err_ = value; }

MessageCode ErrorMsg::type() const { return message_type; }

std::string_view ErrorMsg::name() const { return "Error Msg"; }

std::size_t ErrorMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ErrorMsg", wire_size, length);

    err_ = wire::read_text(data + offset, 64, '\0');
    offset += 64;

    return offset;
}

std::size_t ErrorMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ErrorMsg", wire_size, capacity);

    wire::write_text(data + offset, 64, '\0', err_);
    offset += 64;

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
    out << '}';
}

bool ErrorMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ErrorMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool ErrorMsg::operator==(const ErrorMsg& other) const {
    return err_ == other.err_;
}

bool ErrorMsg::operator!=(const ErrorMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
