#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

TradeMessage::TradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t match_id, std::uint32_t combo_group_id, Side side, std::uint64_t quantity, std::uint32_t order_book_id, std::int32_t trade_price, const std::string& owner_participant_id, const std::string& counterparty_participant_id, Printable printable, OccurredAtCross occurred_at_cross)
  : nanoseconds_(nanoseconds), match_id_(match_id), combo_group_id_(combo_group_id), side_(side), quantity_(quantity), order_book_id_(order_book_id), trade_price_(trade_price), owner_participant_id_(owner_participant_id), counterparty_participant_id_(counterparty_participant_id), printable_(printable), occurred_at_cross_(occurred_at_cross) {}

std::chrono::nanoseconds TradeMessage::nanoseconds() const { return nanoseconds_; }
void TradeMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t TradeMessage::match_id() const { return match_id_; }
void TradeMessage::set_match_id(std::uint64_t value) { match_id_ = value; }

std::uint32_t TradeMessage::combo_group_id() const { return combo_group_id_; }
void TradeMessage::set_combo_group_id(std::uint32_t value) { combo_group_id_ = value; }

Side TradeMessage::side() const { return side_; }
void TradeMessage::set_side(Side value) { side_ = value; }

std::uint64_t TradeMessage::quantity() const { return quantity_; }
void TradeMessage::set_quantity(std::uint64_t value) { quantity_ = value; }

std::uint32_t TradeMessage::order_book_id() const { return order_book_id_; }
void TradeMessage::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

std::int32_t TradeMessage::trade_price() const { return trade_price_; }
void TradeMessage::set_trade_price(std::int32_t value) { trade_price_ = value; }

const std::string& TradeMessage::owner_participant_id() const { return owner_participant_id_; }
std::string& TradeMessage::owner_participant_id() { return owner_participant_id_; }
void TradeMessage::set_owner_participant_id(const std::string& value) { owner_participant_id_ = value; }

const std::string& TradeMessage::counterparty_participant_id() const { return counterparty_participant_id_; }
std::string& TradeMessage::counterparty_participant_id() { return counterparty_participant_id_; }
void TradeMessage::set_counterparty_participant_id(const std::string& value) { counterparty_participant_id_ = value; }

Printable TradeMessage::printable() const { return printable_; }
void TradeMessage::set_printable(Printable value) { printable_ = value; }

OccurredAtCross TradeMessage::occurred_at_cross() const { return occurred_at_cross_; }
void TradeMessage::set_occurred_at_cross(OccurredAtCross value) { occurred_at_cross_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    match_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    combo_group_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    owner_participant_id_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    counterparty_participant_id_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    printable_ = static_cast<Printable>(wire::read_char(data + offset));
    offset += 1;

    occurred_at_cross_ = static_cast<OccurredAtCross>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(combo_group_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(quantity_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(trade_price_));
    offset += 4;

    wire::write_text(data + offset, 7, ' ', owner_participant_id_);
    offset += 7;

    wire::write_text(data + offset, 7, ' ', counterparty_participant_id_);
    offset += 7;

    wire::write_char(data + offset, static_cast<char>(printable_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(occurred_at_cross_));
    offset += 1;

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", match_id=";
    out << match_id_;
    out << ", combo_group_id=";
    out << combo_group_id_;
    out << ", side=";
    out << side_;
    out << ", quantity=";
    out << quantity_;
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", owner_participant_id=";
    print::text(out, owner_participant_id_);
    out << ", counterparty_participant_id=";
    print::text(out, counterparty_participant_id_);
    out << ", printable=";
    out << printable_;
    out << ", occurred_at_cross=";
    out << occurred_at_cross_;
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && match_id_ == other.match_id_
        && combo_group_id_ == other.combo_group_id_
        && side_ == other.side_
        && quantity_ == other.quantity_
        && order_book_id_ == other.order_book_id_
        && trade_price_ == other.trade_price_
        && owner_participant_id_ == other.owner_participant_id_
        && counterparty_participant_id_ == other.counterparty_participant_id_
        && printable_ == other.printable_
        && occurred_at_cross_ == other.occurred_at_cross_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
