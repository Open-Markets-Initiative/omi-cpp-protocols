#include "PayloadOrderExecutedWithPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadOrderExecutedWithPriceMessage::PayloadOrderExecutedWithPriceMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, std::uint32_t executed_shares, std::uint64_t match_number, Printable printable, Decimal execution_price)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), executed_shares_(executed_shares), match_number_(match_number), printable_(printable), execution_price_(execution_price) {}

std::uint16_t PayloadOrderExecutedWithPriceMessage::stock_locate() const { return stock_locate_; }
void PayloadOrderExecutedWithPriceMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadOrderExecutedWithPriceMessage::tracking_number() const { return tracking_number_; }
void PayloadOrderExecutedWithPriceMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadOrderExecutedWithPriceMessage::timestamp() const { return timestamp_; }
void PayloadOrderExecutedWithPriceMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t PayloadOrderExecutedWithPriceMessage::order_reference_number() const { return order_reference_number_; }
void PayloadOrderExecutedWithPriceMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t PayloadOrderExecutedWithPriceMessage::executed_shares() const { return executed_shares_; }
void PayloadOrderExecutedWithPriceMessage::set_executed_shares(std::uint32_t value) { executed_shares_ = value; }

std::uint64_t PayloadOrderExecutedWithPriceMessage::match_number() const { return match_number_; }
void PayloadOrderExecutedWithPriceMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

Printable PayloadOrderExecutedWithPriceMessage::printable() const { return printable_; }
void PayloadOrderExecutedWithPriceMessage::set_printable(Printable value) { printable_ = value; }

Decimal PayloadOrderExecutedWithPriceMessage::execution_price() const { return execution_price_; }
void PayloadOrderExecutedWithPriceMessage::set_execution_price(Decimal value) { execution_price_ = value; }

PacketMessageCode PayloadOrderExecutedWithPriceMessage::type() const { return message_type; }

std::string_view PayloadOrderExecutedWithPriceMessage::name() const { return "Order Executed With Price Message"; }

std::size_t PayloadOrderExecutedWithPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadOrderExecutedWithPriceMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    printable_ = static_cast<Printable>(wire::read_char(data + offset));
    offset += 1;

    execution_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t PayloadOrderExecutedWithPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadOrderExecutedWithPriceMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_shares_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(printable_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(execution_price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t PayloadOrderExecutedWithPriceMessage::encoded_size() const {
    return wire_size;
}

void PayloadOrderExecutedWithPriceMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadOrderExecutedWithPriceMessage::clone() const {
    return std::make_unique<PayloadOrderExecutedWithPriceMessage>(*this);
}

void PayloadOrderExecutedWithPriceMessage::print(std::ostream& out) const {
    out << "PayloadOrderExecutedWithPriceMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", executed_shares=";
    out << executed_shares_;
    out << ", match_number=";
    out << match_number_;
    out << ", printable=";
    out << printable_;
    out << ", execution_price=";
    out << execution_price_;
    out << '}';
}

bool PayloadOrderExecutedWithPriceMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadOrderExecutedWithPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadOrderExecutedWithPriceMessage::operator==(const PayloadOrderExecutedWithPriceMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && executed_shares_ == other.executed_shares_
        && match_number_ == other.match_number_
        && printable_ == other.printable_
        && execution_price_ == other.execution_price_;
}

bool PayloadOrderExecutedWithPriceMessage::operator!=(const PayloadOrderExecutedWithPriceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
