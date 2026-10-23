#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, std::uint32_t executed_quantity, std::uint32_t match_number, const std::string& mpid, const std::string& mpid_counterparty)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_reference_number_(order_reference_number), executed_quantity_(executed_quantity), match_number_(match_number), mpid_(mpid), mpid_counterparty_(mpid_counterparty) {}

std::chrono::nanoseconds OrderExecutedMessage::timestamp() const { return timestamp_; }
void OrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderExecutedMessage::tracking_number() const { return tracking_number_; }
void OrderExecutedMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t OrderExecutedMessage::order_reference_number() const { return order_reference_number_; }
void OrderExecutedMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint32_t OrderExecutedMessage::match_number() const { return match_number_; }
void OrderExecutedMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

const std::string& OrderExecutedMessage::mpid() const { return mpid_; }
std::string& OrderExecutedMessage::mpid() { return mpid_; }
void OrderExecutedMessage::set_mpid(const std::string& value) { mpid_ = value; }

const std::string& OrderExecutedMessage::mpid_counterparty() const { return mpid_counterparty_; }
std::string& OrderExecutedMessage::mpid_counterparty() { return mpid_counterparty_; }
void OrderExecutedMessage::set_mpid_counterparty(const std::string& value) { mpid_counterparty_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

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

    mpid_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    mpid_counterparty_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 4, ' ', mpid_);
    offset += 4;

    wire::write_text(data + offset, 4, ' ', mpid_counterparty_);
    offset += 4;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
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
    out << ", mpid=";
    print::text(out, mpid_);
    out << ", mpid_counterparty=";
    print::text(out, mpid_counterparty_);
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_reference_number_ == other.order_reference_number_
        && executed_quantity_ == other.executed_quantity_
        && match_number_ == other.match_number_
        && mpid_ == other.mpid_
        && mpid_counterparty_ == other.mpid_counterparty_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
