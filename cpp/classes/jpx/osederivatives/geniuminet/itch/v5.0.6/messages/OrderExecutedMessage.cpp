#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint64_t executed_quantity, std::uint64_t match_id, std::uint32_t combo_group_id, const std::string& participant_id_owner, const std::string& participant_id_counterparty)
  : nanoseconds_(nanoseconds), order_id_(order_id), order_book_id_(order_book_id), side_(side), executed_quantity_(executed_quantity), match_id_(match_id), combo_group_id_(combo_group_id), participant_id_owner_(participant_id_owner), participant_id_counterparty_(participant_id_counterparty) {}

std::chrono::nanoseconds OrderExecutedMessage::nanoseconds() const { return nanoseconds_; }
void OrderExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedMessage::order_book_id() const { return order_book_id_; }
void OrderExecutedMessage::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

Side OrderExecutedMessage::side() const { return side_; }
void OrderExecutedMessage::set_side(Side value) { side_ = value; }

std::uint64_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint64_t value) { executed_quantity_ = value; }

std::uint64_t OrderExecutedMessage::match_id() const { return match_id_; }
void OrderExecutedMessage::set_match_id(std::uint64_t value) { match_id_ = value; }

std::uint32_t OrderExecutedMessage::combo_group_id() const { return combo_group_id_; }
void OrderExecutedMessage::set_combo_group_id(std::uint32_t value) { combo_group_id_ = value; }

const std::string& OrderExecutedMessage::participant_id_owner() const { return participant_id_owner_; }
std::string& OrderExecutedMessage::participant_id_owner() { return participant_id_owner_; }
void OrderExecutedMessage::set_participant_id_owner(const std::string& value) { participant_id_owner_ = value; }

const std::string& OrderExecutedMessage::participant_id_counterparty() const { return participant_id_counterparty_; }
std::string& OrderExecutedMessage::participant_id_counterparty() { return participant_id_counterparty_; }
void OrderExecutedMessage::set_participant_id_counterparty(const std::string& value) { participant_id_counterparty_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    executed_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    match_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    combo_group_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_id_owner_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    participant_id_counterparty_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(executed_quantity_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(combo_group_id_));
    offset += 4;

    wire::write_text(data + offset, 7, ' ', participant_id_owner_);
    offset += 7;

    wire::write_text(data + offset, 7, ' ', participant_id_counterparty_);
    offset += 7;

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
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", side=";
    out << side_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", match_id=";
    out << match_id_;
    out << ", combo_group_id=";
    out << combo_group_id_;
    out << ", participant_id_owner=";
    print::text(out, participant_id_owner_);
    out << ", participant_id_counterparty=";
    print::text(out, participant_id_counterparty_);
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_id_ == other.order_id_
        && order_book_id_ == other.order_book_id_
        && side_ == other.side_
        && executed_quantity_ == other.executed_quantity_
        && match_id_ == other.match_id_
        && combo_group_id_ == other.combo_group_id_
        && participant_id_owner_ == other.participant_id_owner_
        && participant_id_counterparty_ == other.participant_id_counterparty_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
