#include "PayloadNetOrderImbalanceIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadNetOrderImbalanceIndicatorMessage::PayloadNetOrderImbalanceIndicatorMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t paired_shares, std::uint64_t imbalance_shares, ImbalanceDirection imbalance_direction, const std::string& stock, Decimal far_price, Decimal near_price, Decimal current_reference_price, CrossType cross_type, PriceVariationIndicator price_variation_indicator)
  : nanoseconds_(nanoseconds), paired_shares_(paired_shares), imbalance_shares_(imbalance_shares), imbalance_direction_(imbalance_direction), stock_(stock), far_price_(far_price), near_price_(near_price), current_reference_price_(current_reference_price), cross_type_(cross_type), price_variation_indicator_(price_variation_indicator) {}

std::chrono::nanoseconds PayloadNetOrderImbalanceIndicatorMessage::nanoseconds() const { return nanoseconds_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t PayloadNetOrderImbalanceIndicatorMessage::paired_shares() const { return paired_shares_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_paired_shares(std::uint64_t value) { paired_shares_ = value; }

std::uint64_t PayloadNetOrderImbalanceIndicatorMessage::imbalance_shares() const { return imbalance_shares_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_imbalance_shares(std::uint64_t value) { imbalance_shares_ = value; }

ImbalanceDirection PayloadNetOrderImbalanceIndicatorMessage::imbalance_direction() const { return imbalance_direction_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_imbalance_direction(ImbalanceDirection value) { imbalance_direction_ = value; }

const std::string& PayloadNetOrderImbalanceIndicatorMessage::stock() const { return stock_; }
std::string& PayloadNetOrderImbalanceIndicatorMessage::stock() { return stock_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal PayloadNetOrderImbalanceIndicatorMessage::far_price() const { return far_price_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_far_price(Decimal value) { far_price_ = value; }

Decimal PayloadNetOrderImbalanceIndicatorMessage::near_price() const { return near_price_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_near_price(Decimal value) { near_price_ = value; }

Decimal PayloadNetOrderImbalanceIndicatorMessage::current_reference_price() const { return current_reference_price_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_current_reference_price(Decimal value) { current_reference_price_ = value; }

CrossType PayloadNetOrderImbalanceIndicatorMessage::cross_type() const { return cross_type_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_cross_type(CrossType value) { cross_type_ = value; }

PriceVariationIndicator PayloadNetOrderImbalanceIndicatorMessage::price_variation_indicator() const { return price_variation_indicator_; }
void PayloadNetOrderImbalanceIndicatorMessage::set_price_variation_indicator(PriceVariationIndicator value) { price_variation_indicator_ = value; }

PacketMessageCode PayloadNetOrderImbalanceIndicatorMessage::type() const { return message_type; }

std::string_view PayloadNetOrderImbalanceIndicatorMessage::name() const { return "Net Order Imbalance Indicator Message"; }

std::size_t PayloadNetOrderImbalanceIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadNetOrderImbalanceIndicatorMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    paired_shares_ = wire::read_u64_be(data + offset);
    offset += 8;

    imbalance_shares_ = wire::read_u64_be(data + offset);
    offset += 8;

    imbalance_direction_ = static_cast<ImbalanceDirection>(wire::read_char(data + offset));
    offset += 1;

    stock_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    far_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    near_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    current_reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    price_variation_indicator_ = static_cast<PriceVariationIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PayloadNetOrderImbalanceIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadNetOrderImbalanceIndicatorMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(paired_shares_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(imbalance_shares_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(imbalance_direction_));
    offset += 1;

    wire::write_text(data + offset, 6, ' ', stock_);
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(far_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(near_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(current_reference_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(price_variation_indicator_));
    offset += 1;

    return offset;
}

std::size_t PayloadNetOrderImbalanceIndicatorMessage::encoded_size() const {
    return wire_size;
}

void PayloadNetOrderImbalanceIndicatorMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadNetOrderImbalanceIndicatorMessage::clone() const {
    return std::make_unique<PayloadNetOrderImbalanceIndicatorMessage>(*this);
}

void PayloadNetOrderImbalanceIndicatorMessage::print(std::ostream& out) const {
    out << "PayloadNetOrderImbalanceIndicatorMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", paired_shares=";
    out << paired_shares_;
    out << ", imbalance_shares=";
    out << imbalance_shares_;
    out << ", imbalance_direction=";
    out << imbalance_direction_;
    out << ", stock=";
    print::text(out, stock_);
    out << ", far_price=";
    out << far_price_;
    out << ", near_price=";
    out << near_price_;
    out << ", current_reference_price=";
    out << current_reference_price_;
    out << ", cross_type=";
    out << cross_type_;
    out << ", price_variation_indicator=";
    out << price_variation_indicator_;
    out << '}';
}

bool PayloadNetOrderImbalanceIndicatorMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadNetOrderImbalanceIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadNetOrderImbalanceIndicatorMessage::operator==(const PayloadNetOrderImbalanceIndicatorMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && paired_shares_ == other.paired_shares_
        && imbalance_shares_ == other.imbalance_shares_
        && imbalance_direction_ == other.imbalance_direction_
        && stock_ == other.stock_
        && far_price_ == other.far_price_
        && near_price_ == other.near_price_
        && current_reference_price_ == other.current_reference_price_
        && cross_type_ == other.cross_type_
        && price_variation_indicator_ == other.price_variation_indicator_;
}

bool PayloadNetOrderImbalanceIndicatorMessage::operator!=(const PayloadNetOrderImbalanceIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
