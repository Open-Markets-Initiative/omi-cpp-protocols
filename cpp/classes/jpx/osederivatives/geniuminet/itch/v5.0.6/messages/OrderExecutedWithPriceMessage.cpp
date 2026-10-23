#include "OrderExecutedWithPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

OrderExecutedWithPriceMessage::OrderExecutedWithPriceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint64_t executed_quantity, std::uint64_t match_id, std::uint32_t combo_group_id, const std::string& owner_participant_id, const std::string& counterparty_participant_id, std::int32_t trade_price, OccurredAtCross occurred_at_cross, Printable printable)
  : nanoseconds_(nanoseconds), order_id_(order_id), order_book_id_(order_book_id), side_(side), executed_quantity_(executed_quantity), match_id_(match_id), combo_group_id_(combo_group_id), owner_participant_id_(owner_participant_id), counterparty_participant_id_(counterparty_participant_id), trade_price_(trade_price), occurred_at_cross_(occurred_at_cross), printable_(printable) {}

std::chrono::nanoseconds OrderExecutedWithPriceMessage::nanoseconds() const { return nanoseconds_; }
void OrderExecutedWithPriceMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderExecutedWithPriceMessage::order_id() const { return order_id_; }
void OrderExecutedWithPriceMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedWithPriceMessage::order_book_id() const { return order_book_id_; }
void OrderExecutedWithPriceMessage::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

Side OrderExecutedWithPriceMessage::side() const { return side_; }
void OrderExecutedWithPriceMessage::set_side(Side value) { side_ = value; }

std::uint64_t OrderExecutedWithPriceMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedWithPriceMessage::set_executed_quantity(std::uint64_t value) { executed_quantity_ = value; }

std::uint64_t OrderExecutedWithPriceMessage::match_id() const { return match_id_; }
void OrderExecutedWithPriceMessage::set_match_id(std::uint64_t value) { match_id_ = value; }

std::uint32_t OrderExecutedWithPriceMessage::combo_group_id() const { return combo_group_id_; }
void OrderExecutedWithPriceMessage::set_combo_group_id(std::uint32_t value) { combo_group_id_ = value; }

const std::string& OrderExecutedWithPriceMessage::owner_participant_id() const { return owner_participant_id_; }
std::string& OrderExecutedWithPriceMessage::owner_participant_id() { return owner_participant_id_; }
void OrderExecutedWithPriceMessage::set_owner_participant_id(const std::string& value) { owner_participant_id_ = value; }

const std::string& OrderExecutedWithPriceMessage::counterparty_participant_id() const { return counterparty_participant_id_; }
std::string& OrderExecutedWithPriceMessage::counterparty_participant_id() { return counterparty_participant_id_; }
void OrderExecutedWithPriceMessage::set_counterparty_participant_id(const std::string& value) { counterparty_participant_id_ = value; }

std::int32_t OrderExecutedWithPriceMessage::trade_price() const { return trade_price_; }
void OrderExecutedWithPriceMessage::set_trade_price(std::int32_t value) { trade_price_ = value; }

OccurredAtCross OrderExecutedWithPriceMessage::occurred_at_cross() const { return occurred_at_cross_; }
void OrderExecutedWithPriceMessage::set_occurred_at_cross(OccurredAtCross value) { occurred_at_cross_ = value; }

Printable OrderExecutedWithPriceMessage::printable() const { return printable_; }
void OrderExecutedWithPriceMessage::set_printable(Printable value) { printable_ = value; }

MessageCode OrderExecutedWithPriceMessage::type() const { return message_type; }

std::string_view OrderExecutedWithPriceMessage::name() const { return "Order Executed With Price Message"; }

std::size_t OrderExecutedWithPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedWithPriceMessage", wire_size, length);

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

    owner_participant_id_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    counterparty_participant_id_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    trade_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    occurred_at_cross_ = static_cast<OccurredAtCross>(wire::read_char(data + offset));
    offset += 1;

    printable_ = static_cast<Printable>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderExecutedWithPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedWithPriceMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 7, ' ', owner_participant_id_);
    offset += 7;

    wire::write_text(data + offset, 7, ' ', counterparty_participant_id_);
    offset += 7;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(trade_price_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(occurred_at_cross_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(printable_));
    offset += 1;

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
    out << ", owner_participant_id=";
    print::text(out, owner_participant_id_);
    out << ", counterparty_participant_id=";
    print::text(out, counterparty_participant_id_);
    out << ", trade_price=";
    out << trade_price_;
    out << ", occurred_at_cross=";
    out << occurred_at_cross_;
    out << ", printable=";
    out << printable_;
    out << '}';
}

bool OrderExecutedWithPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedWithPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedWithPriceMessage::operator==(const OrderExecutedWithPriceMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_id_ == other.order_id_
        && order_book_id_ == other.order_book_id_
        && side_ == other.side_
        && executed_quantity_ == other.executed_quantity_
        && match_id_ == other.match_id_
        && combo_group_id_ == other.combo_group_id_
        && owner_participant_id_ == other.owner_participant_id_
        && counterparty_participant_id_ == other.counterparty_participant_id_
        && trade_price_ == other.trade_price_
        && occurred_at_cross_ == other.occurred_at_cross_
        && printable_ == other.printable_;
}

bool OrderExecutedWithPriceMessage::operator!=(const OrderExecutedWithPriceMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
