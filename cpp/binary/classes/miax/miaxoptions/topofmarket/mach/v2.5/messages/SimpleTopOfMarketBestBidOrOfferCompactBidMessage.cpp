#include "SimpleTopOfMarketBestBidOrOfferCompactBidMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SimpleTopOfMarketBestBidOrOfferCompactBidMessage::SimpleTopOfMarketBestBidOrOfferCompactBidMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal mbbo_price_short, std::uint16_t mbbo_size_short, std::uint16_t mbbo_priority_customer_size_short, MbboCondition mbbo_condition)
  : nanoseconds_(nanoseconds), product_id_(product_id), mbbo_price_short_(mbbo_price_short), mbbo_size_short_(mbbo_size_short), mbbo_priority_customer_size_short_(mbbo_priority_customer_size_short), mbbo_condition_(mbbo_condition) {}

std::chrono::nanoseconds SimpleTopOfMarketBestBidOrOfferCompactBidMessage::nanoseconds() const { return nanoseconds_; }
void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SimpleTopOfMarketBestBidOrOfferCompactBidMessage::product_id() const { return product_id_; }
void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::set_product_id(std::uint32_t value) { product_id_ = value; }

Decimal SimpleTopOfMarketBestBidOrOfferCompactBidMessage::mbbo_price_short() const { return mbbo_price_short_; }
void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::set_mbbo_price_short(Decimal value) { mbbo_price_short_ = value; }

std::uint16_t SimpleTopOfMarketBestBidOrOfferCompactBidMessage::mbbo_size_short() const { return mbbo_size_short_; }
void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::set_mbbo_size_short(std::uint16_t value) { mbbo_size_short_ = value; }

std::uint16_t SimpleTopOfMarketBestBidOrOfferCompactBidMessage::mbbo_priority_customer_size_short() const { return mbbo_priority_customer_size_short_; }
void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::set_mbbo_priority_customer_size_short(std::uint16_t value) { mbbo_priority_customer_size_short_ = value; }

MbboCondition SimpleTopOfMarketBestBidOrOfferCompactBidMessage::mbbo_condition() const { return mbbo_condition_; }
void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::set_mbbo_condition(MbboCondition value) { mbbo_condition_ = value; }

DataCode SimpleTopOfMarketBestBidOrOfferCompactBidMessage::type() const { return message_type; }

std::string_view SimpleTopOfMarketBestBidOrOfferCompactBidMessage::name() const { return "Simple Top Of Market Best Bid Or Offer Compact Bid Message"; }

std::size_t SimpleTopOfMarketBestBidOrOfferCompactBidMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SimpleTopOfMarketBestBidOrOfferCompactBidMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    mbbo_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_le(data + offset)), -2);
    offset += 2;

    mbbo_size_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    mbbo_priority_customer_size_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    mbbo_condition_ = static_cast<MbboCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SimpleTopOfMarketBestBidOrOfferCompactBidMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleTopOfMarketBestBidOrOfferCompactBidMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(mbbo_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(mbbo_size_short_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(mbbo_priority_customer_size_short_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(mbbo_condition_));
    offset += 1;

    return offset;
}

std::size_t SimpleTopOfMarketBestBidOrOfferCompactBidMessage::encoded_size() const {
    return wire_size;
}

void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SimpleTopOfMarketBestBidOrOfferCompactBidMessage::clone() const {
    return std::make_unique<SimpleTopOfMarketBestBidOrOfferCompactBidMessage>(*this);
}

void SimpleTopOfMarketBestBidOrOfferCompactBidMessage::print(std::ostream& out) const {
    out << "SimpleTopOfMarketBestBidOrOfferCompactBidMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", mbbo_price_short=";
    out << mbbo_price_short_;
    out << ", mbbo_size_short=";
    out << mbbo_size_short_;
    out << ", mbbo_priority_customer_size_short=";
    out << mbbo_priority_customer_size_short_;
    out << ", mbbo_condition=";
    out << mbbo_condition_;
    out << '}';
}

bool SimpleTopOfMarketBestBidOrOfferCompactBidMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SimpleTopOfMarketBestBidOrOfferCompactBidMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SimpleTopOfMarketBestBidOrOfferCompactBidMessage::operator==(const SimpleTopOfMarketBestBidOrOfferCompactBidMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && mbbo_price_short_ == other.mbbo_price_short_
        && mbbo_size_short_ == other.mbbo_size_short_
        && mbbo_priority_customer_size_short_ == other.mbbo_priority_customer_size_short_
        && mbbo_condition_ == other.mbbo_condition_;
}

bool SimpleTopOfMarketBestBidOrOfferCompactBidMessage::operator!=(const SimpleTopOfMarketBestBidOrOfferCompactBidMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
