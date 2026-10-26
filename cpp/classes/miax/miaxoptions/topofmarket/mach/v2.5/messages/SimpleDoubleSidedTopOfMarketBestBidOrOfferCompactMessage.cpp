#include "SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal bid_price_short, std::uint16_t bid_size_short, std::uint16_t bid_priority_customer_size_short, BidCondition bid_condition, Decimal offer_price_short, std::uint16_t offer_size_short, std::uint16_t offer_priority_customer_size_short, OfferCondition offer_condition)
  : nanoseconds_(nanoseconds), product_id_(product_id), bid_price_short_(bid_price_short), bid_size_short_(bid_size_short), bid_priority_customer_size_short_(bid_priority_customer_size_short), bid_condition_(bid_condition), offer_price_short_(offer_price_short), offer_size_short_(offer_size_short), offer_priority_customer_size_short_(offer_priority_customer_size_short), offer_condition_(offer_condition) {}

std::chrono::nanoseconds SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::nanoseconds() const { return nanoseconds_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::product_id() const { return product_id_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_product_id(std::uint32_t value) { product_id_ = value; }

Decimal SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::bid_price_short() const { return bid_price_short_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_bid_price_short(Decimal value) { bid_price_short_ = value; }

std::uint16_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::bid_size_short() const { return bid_size_short_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_bid_size_short(std::uint16_t value) { bid_size_short_ = value; }

std::uint16_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::bid_priority_customer_size_short() const { return bid_priority_customer_size_short_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_bid_priority_customer_size_short(std::uint16_t value) { bid_priority_customer_size_short_ = value; }

BidCondition SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::bid_condition() const { return bid_condition_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_bid_condition(BidCondition value) { bid_condition_ = value; }

Decimal SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::offer_price_short() const { return offer_price_short_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_offer_price_short(Decimal value) { offer_price_short_ = value; }

std::uint16_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::offer_size_short() const { return offer_size_short_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_offer_size_short(std::uint16_t value) { offer_size_short_ = value; }

std::uint16_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::offer_priority_customer_size_short() const { return offer_priority_customer_size_short_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_offer_priority_customer_size_short(std::uint16_t value) { offer_priority_customer_size_short_ = value; }

OfferCondition SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::offer_condition() const { return offer_condition_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::set_offer_condition(OfferCondition value) { offer_condition_ = value; }

DataCode SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::type() const { return message_type; }

std::string_view SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::name() const { return "Simple Double Sided Top Of Market Best Bid Or Offer Compact Message"; }

std::size_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_le(data + offset)), -2);
    offset += 2;

    bid_size_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    bid_priority_customer_size_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    bid_condition_ = static_cast<BidCondition>(wire::read_char(data + offset));
    offset += 1;

    offer_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_le(data + offset)), -2);
    offset += 2;

    offer_size_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    offer_priority_customer_size_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    offer_condition_ = static_cast<OfferCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(bid_size_short_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(bid_priority_customer_size_short_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(bid_condition_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(offer_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(offer_size_short_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(offer_priority_customer_size_short_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(offer_condition_));
    offset += 1;

    return offset;
}

std::size_t SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::encoded_size() const {
    return wire_size;
}

void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::clone() const {
    return std::make_unique<SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage>(*this);
}

void SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::print(std::ostream& out) const {
    out << "SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", bid_price_short=";
    out << bid_price_short_;
    out << ", bid_size_short=";
    out << bid_size_short_;
    out << ", bid_priority_customer_size_short=";
    out << bid_priority_customer_size_short_;
    out << ", bid_condition=";
    out << bid_condition_;
    out << ", offer_price_short=";
    out << offer_price_short_;
    out << ", offer_size_short=";
    out << offer_size_short_;
    out << ", offer_priority_customer_size_short=";
    out << offer_priority_customer_size_short_;
    out << ", offer_condition=";
    out << offer_condition_;
    out << '}';
}

bool SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::operator==(const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && bid_price_short_ == other.bid_price_short_
        && bid_size_short_ == other.bid_size_short_
        && bid_priority_customer_size_short_ == other.bid_priority_customer_size_short_
        && bid_condition_ == other.bid_condition_
        && offer_price_short_ == other.offer_price_short_
        && offer_size_short_ == other.offer_size_short_
        && offer_priority_customer_size_short_ == other.offer_priority_customer_size_short_
        && offer_condition_ == other.offer_condition_;
}

bool SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::operator!=(const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
