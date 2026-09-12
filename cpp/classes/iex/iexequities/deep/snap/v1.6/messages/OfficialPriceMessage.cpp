#include "OfficialPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

OfficialPriceMessage::OfficialPriceMessage(PriceType price_type, std::chrono::nanoseconds timestamp, const std::string& symbol, Decimal official_price)
  : price_type_(price_type), timestamp_(timestamp), symbol_(symbol), official_price_(official_price) {}

PriceType OfficialPriceMessage::price_type() const { return price_type_; }
void OfficialPriceMessage::set_price_type(PriceType value) { price_type_ = value; }

std::chrono::nanoseconds OfficialPriceMessage::timestamp() const { return timestamp_; }
void OfficialPriceMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& OfficialPriceMessage::symbol() const { return symbol_; }
std::string& OfficialPriceMessage::symbol() { return symbol_; }
void OfficialPriceMessage::set_symbol(const std::string& value) { symbol_ = value; }

Decimal OfficialPriceMessage::official_price() const { return official_price_; }
void OfficialPriceMessage::set_official_price(Decimal value) { official_price_ = value; }

IexTpMessageDataCode OfficialPriceMessage::type() const { return message_type; }

std::string_view OfficialPriceMessage::name() const { return "Official Price Message"; }

std::size_t OfficialPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OfficialPriceMessage", wire_size, length);

    price_type_ = static_cast<PriceType>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    official_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t OfficialPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OfficialPriceMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(price_type_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(official_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OfficialPriceMessage::encoded_size() const {
    return wire_size;
}

void OfficialPriceMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> OfficialPriceMessage::clone() const {
    return std::make_unique<OfficialPriceMessage>(*this);
}

void OfficialPriceMessage::print(std::ostream& out) const {
    out << "OfficialPriceMessage{";
    out << "price_type=";
    out << price_type_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", official_price=";
    out << official_price_;
    out << '}';
}

bool OfficialPriceMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const OfficialPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OfficialPriceMessage::operator==(const OfficialPriceMessage& other) const {
    return price_type_ == other.price_type_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && official_price_ == other.official_price_;
}

bool OfficialPriceMessage::operator!=(const OfficialPriceMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::snap::v1_6
