#include "OperationalHaltMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

OperationalHaltMessage::OperationalHaltMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, MarketCode market_code, OperationalHaltAction operational_halt_action)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), market_code_(market_code), operational_halt_action_(operational_halt_action) {}

std::uint16_t OperationalHaltMessage::stock_locate() const { return stock_locate_; }
void OperationalHaltMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t OperationalHaltMessage::tracking_number() const { return tracking_number_; }
void OperationalHaltMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds OperationalHaltMessage::timestamp() const { return timestamp_; }
void OperationalHaltMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& OperationalHaltMessage::stock() const { return stock_; }
std::string& OperationalHaltMessage::stock() { return stock_; }
void OperationalHaltMessage::set_stock(const std::string& value) { stock_ = value; }

MarketCode OperationalHaltMessage::market_code() const { return market_code_; }
void OperationalHaltMessage::set_market_code(MarketCode value) { market_code_ = value; }

OperationalHaltAction OperationalHaltMessage::operational_halt_action() const { return operational_halt_action_; }
void OperationalHaltMessage::set_operational_halt_action(OperationalHaltAction value) { operational_halt_action_ = value; }

MessageCode OperationalHaltMessage::type() const { return message_type; }

std::string_view OperationalHaltMessage::name() const { return "Operational Halt Message"; }

std::size_t OperationalHaltMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OperationalHaltMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    market_code_ = static_cast<MarketCode>(wire::read_char(data + offset));
    offset += 1;

    operational_halt_action_ = static_cast<OperationalHaltAction>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OperationalHaltMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OperationalHaltMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_code_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(operational_halt_action_));
    offset += 1;

    return offset;
}

std::size_t OperationalHaltMessage::encoded_size() const {
    return wire_size;
}

void OperationalHaltMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OperationalHaltMessage::clone() const {
    return std::make_unique<OperationalHaltMessage>(*this);
}

void OperationalHaltMessage::print(std::ostream& out) const {
    out << "OperationalHaltMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", market_code=";
    out << market_code_;
    out << ", operational_halt_action=";
    out << operational_halt_action_;
    out << '}';
}

bool OperationalHaltMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OperationalHaltMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OperationalHaltMessage::operator==(const OperationalHaltMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && market_code_ == other.market_code_
        && operational_halt_action_ == other.operational_halt_action_;
}

bool OperationalHaltMessage::operator!=(const OperationalHaltMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
