#include "OrderExecutedWithPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderExecutedWithPriceMessage::OrderExecutedWithPriceMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, std::uint32_t executed_quantity, std::uint32_t match_number, Printable printable, Decimal trade_price, const std::string& mpid_owner, const std::string& mpid_counterparty)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_reference_number_(order_reference_number), executed_quantity_(executed_quantity), match_number_(match_number), printable_(printable), trade_price_(trade_price), mpid_owner_(mpid_owner), mpid_counterparty_(mpid_counterparty) {}

std::chrono::nanoseconds OrderExecutedWithPriceMessage::timestamp() const { return timestamp_; }
void OrderExecutedWithPriceMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderExecutedWithPriceMessage::tracking_number() const { return tracking_number_; }
void OrderExecutedWithPriceMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t OrderExecutedWithPriceMessage::order_reference_number() const { return order_reference_number_; }
void OrderExecutedWithPriceMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t OrderExecutedWithPriceMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedWithPriceMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint32_t OrderExecutedWithPriceMessage::match_number() const { return match_number_; }
void OrderExecutedWithPriceMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

Printable OrderExecutedWithPriceMessage::printable() const { return printable_; }
void OrderExecutedWithPriceMessage::set_printable(Printable value) { printable_ = value; }

Decimal OrderExecutedWithPriceMessage::trade_price() const { return trade_price_; }
void OrderExecutedWithPriceMessage::set_trade_price(Decimal value) { trade_price_ = value; }

const std::string& OrderExecutedWithPriceMessage::mpid_owner() const { return mpid_owner_; }
std::string& OrderExecutedWithPriceMessage::mpid_owner() { return mpid_owner_; }
void OrderExecutedWithPriceMessage::set_mpid_owner(const std::string& value) { mpid_owner_ = value; }

const std::string& OrderExecutedWithPriceMessage::mpid_counterparty() const { return mpid_counterparty_; }
std::string& OrderExecutedWithPriceMessage::mpid_counterparty() { return mpid_counterparty_; }
void OrderExecutedWithPriceMessage::set_mpid_counterparty(const std::string& value) { mpid_counterparty_ = value; }

MessageCode OrderExecutedWithPriceMessage::type() const { return message_type; }

std::string_view OrderExecutedWithPriceMessage::name() const { return "Order Executed With Price Message"; }

std::size_t OrderExecutedWithPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedWithPriceMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    printable_ = static_cast<Printable>(wire::read_char(data + offset));
    offset += 1;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    mpid_owner_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    mpid_counterparty_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t OrderExecutedWithPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedWithPriceMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(printable_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_price_.mantissa()));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', mpid_owner_);
    offset += 4;

    wire::write_text(data + offset, 4, ' ', mpid_counterparty_);
    offset += 4;

    return offset;
}

std::size_t OrderExecutedWithPriceMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedWithPriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedWithPriceMessage::clone() const {
    return std::make_unique<OrderExecutedWithPriceMessage>(*this);
}

void OrderExecutedWithPriceMessage::print(std::ostream& out) const {
    out << "OrderExecutedWithPriceMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", match_number=";
    out << match_number_;
    out << ", printable=";
    out << printable_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", mpid_owner=";
    print::text(out, mpid_owner_);
    out << ", mpid_counterparty=";
    print::text(out, mpid_counterparty_);
    out << '}';
}

bool OrderExecutedWithPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedWithPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedWithPriceMessage::operator==(const OrderExecutedWithPriceMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_reference_number_ == other.order_reference_number_
        && executed_quantity_ == other.executed_quantity_
        && match_number_ == other.match_number_
        && printable_ == other.printable_
        && trade_price_ == other.trade_price_
        && mpid_owner_ == other.mpid_owner_
        && mpid_counterparty_ == other.mpid_counterparty_;
}

bool OrderExecutedWithPriceMessage::operator!=(const OrderExecutedWithPriceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
