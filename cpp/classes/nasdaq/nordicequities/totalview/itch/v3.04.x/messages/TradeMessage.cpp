#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

TradeMessage::TradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, TradeType trade_type, std::uint32_t quantity, std::uint32_t order_book, std::uint32_t match_number, Decimal trade_price, const std::string& participant_id_buyer, const std::string& participant_id_seller)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_reference_number_(order_reference_number), trade_type_(trade_type), quantity_(quantity), order_book_(order_book), match_number_(match_number), trade_price_(trade_price), participant_id_buyer_(participant_id_buyer), participant_id_seller_(participant_id_seller) {}

std::chrono::nanoseconds TradeMessage::timestamp() const { return timestamp_; }
void TradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t TradeMessage::tracking_number() const { return tracking_number_; }
void TradeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t TradeMessage::order_reference_number() const { return order_reference_number_; }
void TradeMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

TradeType TradeMessage::trade_type() const { return trade_type_; }
void TradeMessage::set_trade_type(TradeType value) { trade_type_ = value; }

std::uint32_t TradeMessage::quantity() const { return quantity_; }
void TradeMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t TradeMessage::order_book() const { return order_book_; }
void TradeMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

std::uint32_t TradeMessage::match_number() const { return match_number_; }
void TradeMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

Decimal TradeMessage::trade_price() const { return trade_price_; }
void TradeMessage::set_trade_price(Decimal value) { trade_price_ = value; }

const std::string& TradeMessage::participant_id_buyer() const { return participant_id_buyer_; }
std::string& TradeMessage::participant_id_buyer() { return participant_id_buyer_; }
void TradeMessage::set_participant_id_buyer(const std::string& value) { participant_id_buyer_ = value; }

const std::string& TradeMessage::participant_id_seller() const { return participant_id_seller_; }
std::string& TradeMessage::participant_id_seller() { return participant_id_seller_; }
void TradeMessage::set_participant_id_seller(const std::string& value) { participant_id_seller_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    trade_type_ = static_cast<TradeType>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    participant_id_buyer_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    participant_id_seller_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trade_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_price_.mantissa()));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', participant_id_buyer_);
    offset += 4;

    wire::write_text(data + offset, 4, ' ', participant_id_seller_);
    offset += 4;

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
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", trade_type=";
    out << trade_type_;
    out << ", quantity=";
    out << quantity_;
    out << ", order_book=";
    out << order_book_;
    out << ", match_number=";
    out << match_number_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", participant_id_buyer=";
    print::text(out, participant_id_buyer_);
    out << ", participant_id_seller=";
    print::text(out, participant_id_seller_);
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_reference_number_ == other.order_reference_number_
        && trade_type_ == other.trade_type_
        && quantity_ == other.quantity_
        && order_book_ == other.order_book_
        && match_number_ == other.match_number_
        && trade_price_ == other.trade_price_
        && participant_id_buyer_ == other.participant_id_buyer_
        && participant_id_seller_ == other.participant_id_seller_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
