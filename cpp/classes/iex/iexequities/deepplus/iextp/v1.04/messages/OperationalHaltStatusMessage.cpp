#include "OperationalHaltStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

OperationalHaltStatusMessage::OperationalHaltStatusMessage(OperationalHaltStatus operational_halt_status, std::chrono::nanoseconds timestamp, const std::string& symbol)
  : operational_halt_status_(operational_halt_status), timestamp_(timestamp), symbol_(symbol) {}

OperationalHaltStatus OperationalHaltStatusMessage::operational_halt_status() const { return operational_halt_status_; }
void OperationalHaltStatusMessage::set_operational_halt_status(OperationalHaltStatus value) { operational_halt_status_ = value; }

std::chrono::nanoseconds OperationalHaltStatusMessage::timestamp() const { return timestamp_; }
void OperationalHaltStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& OperationalHaltStatusMessage::symbol() const { return symbol_; }
std::string& OperationalHaltStatusMessage::symbol() { return symbol_; }
void OperationalHaltStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

MessageCode OperationalHaltStatusMessage::type() const { return message_type; }

std::string_view OperationalHaltStatusMessage::name() const { return "Operational Halt Status Message"; }

std::size_t OperationalHaltStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OperationalHaltStatusMessage", wire_size, length);

    operational_halt_status_ = static_cast<OperationalHaltStatus>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    return offset;
}

std::size_t OperationalHaltStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OperationalHaltStatusMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(operational_halt_status_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    return offset;
}

std::size_t OperationalHaltStatusMessage::encoded_size() const {
    return wire_size;
}

void OperationalHaltStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OperationalHaltStatusMessage::clone() const {
    return std::make_unique<OperationalHaltStatusMessage>(*this);
}

void OperationalHaltStatusMessage::print(std::ostream& out) const {
    out << "OperationalHaltStatusMessage{";
    out << "operational_halt_status=";
    out << operational_halt_status_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << '}';
}

bool OperationalHaltStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OperationalHaltStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OperationalHaltStatusMessage::operator==(const OperationalHaltStatusMessage& other) const {
    return operational_halt_status_ == other.operational_halt_status_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_;
}

bool OperationalHaltStatusMessage::operator!=(const OperationalHaltStatusMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::iextp::v1_04
