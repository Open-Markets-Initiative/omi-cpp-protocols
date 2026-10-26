#include "ExecutionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

ExecutionSummaryMessage::ExecutionSummaryMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book, AggressingSide aggressing_side, std::uint32_t quantity, std::uint32_t hidden_quantity, std::uint32_t stp_cancel_quantity, Decimal far_price, std::uint32_t add_quantity, std::uint16_t number_of_lit_executions)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_book_(order_book), aggressing_side_(aggressing_side), quantity_(quantity), hidden_quantity_(hidden_quantity), stp_cancel_quantity_(stp_cancel_quantity), far_price_(far_price), add_quantity_(add_quantity), number_of_lit_executions_(number_of_lit_executions) {}

std::chrono::nanoseconds ExecutionSummaryMessage::timestamp() const { return timestamp_; }
void ExecutionSummaryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t ExecutionSummaryMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint16_t ExecutionSummaryMessage::tracking_number() const { return tracking_number_; }
void ExecutionSummaryMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint32_t ExecutionSummaryMessage::order_book() const { return order_book_; }
void ExecutionSummaryMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

AggressingSide ExecutionSummaryMessage::aggressing_side() const { return aggressing_side_; }
void ExecutionSummaryMessage::set_aggressing_side(AggressingSide value) { aggressing_side_ = value; }

std::uint32_t ExecutionSummaryMessage::quantity() const { return quantity_; }
void ExecutionSummaryMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t ExecutionSummaryMessage::hidden_quantity() const { return hidden_quantity_; }
void ExecutionSummaryMessage::set_hidden_quantity(std::uint32_t value) { hidden_quantity_ = value; }

std::uint32_t ExecutionSummaryMessage::stp_cancel_quantity() const { return stp_cancel_quantity_; }
void ExecutionSummaryMessage::set_stp_cancel_quantity(std::uint32_t value) { stp_cancel_quantity_ = value; }

Decimal ExecutionSummaryMessage::far_price() const { return far_price_; }
void ExecutionSummaryMessage::set_far_price(Decimal value) { far_price_ = value; }

std::uint32_t ExecutionSummaryMessage::add_quantity() const { return add_quantity_; }
void ExecutionSummaryMessage::set_add_quantity(std::uint32_t value) { add_quantity_ = value; }

std::uint16_t ExecutionSummaryMessage::number_of_lit_executions() const { return number_of_lit_executions_; }
void ExecutionSummaryMessage::set_number_of_lit_executions(std::uint16_t value) { number_of_lit_executions_ = value; }

MessageCode ExecutionSummaryMessage::type() const { return message_type; }

std::string_view ExecutionSummaryMessage::name() const { return "Execution Summary Message"; }

std::size_t ExecutionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExecutionSummaryMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    aggressing_side_ = static_cast<AggressingSide>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    hidden_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    stp_cancel_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    far_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    add_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    number_of_lit_executions_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t ExecutionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionSummaryMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(aggressing_side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(hidden_quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(stp_cancel_quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(far_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(add_quantity_));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(number_of_lit_executions_));
    offset += 2;

    return offset;
}

std::size_t ExecutionSummaryMessage::encoded_size() const {
    return wire_size;
}

void ExecutionSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionSummaryMessage::clone() const {
    return std::make_unique<ExecutionSummaryMessage>(*this);
}

void ExecutionSummaryMessage::print(std::ostream& out) const {
    out << "ExecutionSummaryMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "UTC");
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_book=";
    out << order_book_;
    out << ", aggressing_side=";
    out << aggressing_side_;
    out << ", quantity=";
    out << quantity_;
    out << ", hidden_quantity=";
    out << hidden_quantity_;
    out << ", stp_cancel_quantity=";
    out << stp_cancel_quantity_;
    out << ", far_price=";
    out << far_price_;
    out << ", add_quantity=";
    out << add_quantity_;
    out << ", number_of_lit_executions=";
    out << number_of_lit_executions_;
    out << '}';
}

bool ExecutionSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionSummaryMessage::operator==(const ExecutionSummaryMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_book_ == other.order_book_
        && aggressing_side_ == other.aggressing_side_
        && quantity_ == other.quantity_
        && hidden_quantity_ == other.hidden_quantity_
        && stp_cancel_quantity_ == other.stp_cancel_quantity_
        && far_price_ == other.far_price_
        && add_quantity_ == other.add_quantity_
        && number_of_lit_executions_ == other.number_of_lit_executions_;
}

bool ExecutionSummaryMessage::operator!=(const ExecutionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
