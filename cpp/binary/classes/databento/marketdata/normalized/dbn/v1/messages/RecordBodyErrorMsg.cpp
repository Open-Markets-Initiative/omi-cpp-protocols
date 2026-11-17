// Databento.MarketData.Normalized.Dbn.v1: messages/RecordBodyErrorMsg.cpp
#include "RecordBodyErrorMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

RecordBodyErrorMsg::RecordBodyErrorMsg(const std::string& err)
  : err_(err) {}

const std::string& RecordBodyErrorMsg::err() const { return err_; }
std::string& RecordBodyErrorMsg::err() { return err_; }
void RecordBodyErrorMsg::set_err(const std::string& value) { err_ = value; }

GatewayMessageCode RecordBodyErrorMsg::type() const { return message_type; }

std::string_view RecordBodyErrorMsg::name() const { return "Error Msg"; }

std::size_t RecordBodyErrorMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecordBodyErrorMsg", wire_size, length);

    err_ = wire::read_text(data + offset, 64, '\0');
    offset += 64;

    return offset;
}

std::size_t RecordBodyErrorMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecordBodyErrorMsg", wire_size, capacity);

    wire::write_text(data + offset, 64, '\0', err_);
    offset += 64;

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
    out << '}';
}

bool RecordBodyErrorMsg::equals(const GatewayMessage& other) const {
    const auto* that = dynamic_cast<const RecordBodyErrorMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool RecordBodyErrorMsg::operator==(const RecordBodyErrorMsg& other) const {
    return err_ == other.err_;
}

bool RecordBodyErrorMsg::operator!=(const RecordBodyErrorMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
