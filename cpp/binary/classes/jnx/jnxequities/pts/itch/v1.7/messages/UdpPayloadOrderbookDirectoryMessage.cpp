#include "UdpPayloadOrderbookDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadOrderbookDirectoryMessage::UdpPayloadOrderbookDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& orderbook_code, const std::string& group, std::uint32_t round_lot_size, std::uint32_t price_tick_size_table_id, std::uint32_t price_decimals, Decimal upper_price_limit, Decimal lower_price_limit)
  : nanoseconds_(nanoseconds), orderbook_id_(orderbook_id), orderbook_code_(orderbook_code), group_(group), round_lot_size_(round_lot_size), price_tick_size_table_id_(price_tick_size_table_id), price_decimals_(price_decimals), upper_price_limit_(upper_price_limit), lower_price_limit_(lower_price_limit) {}

std::chrono::nanoseconds UdpPayloadOrderbookDirectoryMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadOrderbookDirectoryMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t UdpPayloadOrderbookDirectoryMessage::orderbook_id() const { return orderbook_id_; }
void UdpPayloadOrderbookDirectoryMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& UdpPayloadOrderbookDirectoryMessage::orderbook_code() const { return orderbook_code_; }
std::string& UdpPayloadOrderbookDirectoryMessage::orderbook_code() { return orderbook_code_; }
void UdpPayloadOrderbookDirectoryMessage::set_orderbook_code(const std::string& value) { orderbook_code_ = value; }

const std::string& UdpPayloadOrderbookDirectoryMessage::group() const { return group_; }
std::string& UdpPayloadOrderbookDirectoryMessage::group() { return group_; }
void UdpPayloadOrderbookDirectoryMessage::set_group(const std::string& value) { group_ = value; }

std::uint32_t UdpPayloadOrderbookDirectoryMessage::round_lot_size() const { return round_lot_size_; }
void UdpPayloadOrderbookDirectoryMessage::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

std::uint32_t UdpPayloadOrderbookDirectoryMessage::price_tick_size_table_id() const { return price_tick_size_table_id_; }
void UdpPayloadOrderbookDirectoryMessage::set_price_tick_size_table_id(std::uint32_t value) { price_tick_size_table_id_ = value; }

std::uint32_t UdpPayloadOrderbookDirectoryMessage::price_decimals() const { return price_decimals_; }
void UdpPayloadOrderbookDirectoryMessage::set_price_decimals(std::uint32_t value) { price_decimals_ = value; }

Decimal UdpPayloadOrderbookDirectoryMessage::upper_price_limit() const { return upper_price_limit_; }
void UdpPayloadOrderbookDirectoryMessage::set_upper_price_limit(Decimal value) { upper_price_limit_ = value; }

Decimal UdpPayloadOrderbookDirectoryMessage::lower_price_limit() const { return lower_price_limit_; }
void UdpPayloadOrderbookDirectoryMessage::set_lower_price_limit(Decimal value) { lower_price_limit_ = value; }

PacketMessageCode UdpPayloadOrderbookDirectoryMessage::type() const { return message_type; }

std::string_view UdpPayloadOrderbookDirectoryMessage::name() const { return "Orderbook Directory Message"; }

std::size_t UdpPayloadOrderbookDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOrderbookDirectoryMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    orderbook_code_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    round_lot_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_tick_size_table_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_decimals_ = wire::read_u32_be(data + offset);
    offset += 4;

    upper_price_limit_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    lower_price_limit_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderbookDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOrderbookDirectoryMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(orderbook_id_));
    offset += 4;

    wire::write_text(data + offset, 12, ' ', orderbook_code_);
    offset += 12;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(round_lot_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_tick_size_table_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_decimals_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(upper_price_limit_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(lower_price_limit_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderbookDirectoryMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOrderbookDirectoryMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOrderbookDirectoryMessage::clone() const {
    return std::make_unique<UdpPayloadOrderbookDirectoryMessage>(*this);
}

void UdpPayloadOrderbookDirectoryMessage::print(std::ostream& out) const {
    out << "UdpPayloadOrderbookDirectoryMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", orderbook_id=";
    out << orderbook_id_;
    out << ", orderbook_code=";
    print::text(out, orderbook_code_);
    out << ", group=";
    print::text(out, group_);
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", price_tick_size_table_id=";
    out << price_tick_size_table_id_;
    out << ", price_decimals=";
    out << price_decimals_;
    out << ", upper_price_limit=";
    out << upper_price_limit_;
    out << ", lower_price_limit=";
    out << lower_price_limit_;
    out << '}';
}

bool UdpPayloadOrderbookDirectoryMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOrderbookDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOrderbookDirectoryMessage::operator==(const UdpPayloadOrderbookDirectoryMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && orderbook_id_ == other.orderbook_id_
        && orderbook_code_ == other.orderbook_code_
        && group_ == other.group_
        && round_lot_size_ == other.round_lot_size_
        && price_tick_size_table_id_ == other.price_tick_size_table_id_
        && price_decimals_ == other.price_decimals_
        && upper_price_limit_ == other.upper_price_limit_
        && lower_price_limit_ == other.lower_price_limit_;
}

bool UdpPayloadOrderbookDirectoryMessage::operator!=(const UdpPayloadOrderbookDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
