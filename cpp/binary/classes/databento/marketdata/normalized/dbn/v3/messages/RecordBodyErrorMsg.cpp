// Databento.MarketData.Normalized.Dbn.v3: messages/RecordBodyErrorMsg.cpp
#include "RecordBodyErrorMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

RecordBodyErrorMsg::RecordBodyErrorMsg(const std::string& err, ErrorCode error_code, std::uint8_t is_last)
  : err_(err), error_code_(error_code), is_last_(is_last) {}

const std::string& RecordBodyErrorMsg::err() const { return err_; }
std::string& RecordBodyErrorMsg::err() { return err_; }
void RecordBodyErrorMsg::set_err(const std::string& value) { err_ = value; }

ErrorCode RecordBodyErrorMsg::error_code() const { return error_code_; }
void RecordBodyErrorMsg::set_error_code(ErrorCode value) { error_code_ = value; }

std::uint8_t RecordBodyErrorMsg::is_last() const { return is_last_; }
void RecordBodyErrorMsg::set_is_last(std::uint8_t value) { is_last_ = value; }

GatewayMessageCode RecordBodyErrorMsg::type() const { return message_type; }

std::string_view RecordBodyErrorMsg::name() const { return "Error Msg"; }

std::size_t RecordBodyErrorMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecordBodyErrorMsg", wire_size, length);

    err_ = wire::read_text(data + offset, 302, '\0');
    offset += 302;

    error_code_ = static_cast<ErrorCode>(wire::read_u8(data + offset));
    offset += 1;

    is_last_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t RecordBodyErrorMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecordBodyErrorMsg", wire_size, capacity);

    wire::write_text(data + offset, 302, '\0', err_);
    offset += 302;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(error_code_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(is_last_));
    offset += 1;

    return offset;
}

std::size_t RecordBodyErrorMsg::encoded_size() const {
    return wire_size;
}

void RecordBodyErrorMsg::accept(GatewayMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<GatewayMessage> RecordBodyErrorMsg::clone() const {
    return std::make_unique<RecordBodyErrorMsg>(*this);
}

void RecordBodyErrorMsg::print(std::ostream& out) const {
    out << "RecordBodyErrorMsg{";
    out << "err=";
    print::text(out, err_);
    out << ", error_code=";
    out << error_code_;
    out << ", is_last=";
    out << static_cast<int>(is_last_);
    out << '}';
}

bool RecordBodyErrorMsg::equals(const GatewayMessage& other) const {
    const auto* that = dynamic_cast<const RecordBodyErrorMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool RecordBodyErrorMsg::operator==(const RecordBodyErrorMsg& other) const {
    return err_ == other.err_
        && error_code_ == other.error_code_
        && is_last_ == other.is_last_;
}

bool RecordBodyErrorMsg::operator!=(const RecordBodyErrorMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v3
