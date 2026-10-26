#include "SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal bid_price_long, std::uint32_t bid_size_long, std::uint32_t bid_priority_customer_size_long, BidCondition bid_condition, Decimal offer_price_long, std::uint32_t offer_size_long, std::uint32_t offer_priority_customer_size_long, OfferCondition offer_condition)
  : nanoseconds_(nanoseconds), product_id_(product_id), bid_price_long_(bid_price_long), bid_size_long_(bid_size_long), bid_priority_customer_size_long_(bid_priority_customer_size_long), bid_condition_(bid_condition), offer_price_long_(offer_price_long), offer_size_long_(offer_size_long), offer_priority_customer_size_long_(offer_priority_customer_size_long), offer_condition_(offer_condition) {}

std::chrono::nanoseconds SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::nanoseconds() const { return nanoseconds_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::product_id() const { return product_id_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_product_id(std::uint32_t value) { product_id_ = value; }

Decimal SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::bid_price_long() const { return bid_price_long_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_bid_price_long(Decimal value) { bid_price_long_ = value; }

std::uint32_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::bid_size_long() const { return bid_size_long_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_bid_size_long(std::uint32_t value) { bid_size_long_ = value; }

std::uint32_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::bid_priority_customer_size_long() const { return bid_priority_customer_size_long_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_bid_priority_customer_size_long(std::uint32_t value) { bid_priority_customer_size_long_ = value; }

BidCondition SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::bid_condition() const { return bid_condition_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_bid_condition(BidCondition value) { bid_condition_ = value; }

Decimal SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::offer_price_long() const { return offer_price_long_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_offer_price_long(Decimal value) { offer_price_long_ = value; }

std::uint32_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::offer_size_long() const { return offer_size_long_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_offer_size_long(std::uint32_t value) { offer_size_long_ = value; }

std::uint32_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::offer_priority_customer_size_long() const { return offer_priority_customer_size_long_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_offer_priority_customer_size_long(std::uint32_t value) { offer_priority_customer_size_long_ = value; }

OfferCondition SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::offer_condition() const { return offer_condition_; }
void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::set_offer_condition(OfferCondition value) { offer_condition_ = value; }

DataCode SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::type() const { return message_type; }

std::string_view SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::name() const { return "Simple Double Sided Top Of Market Best Bid Or Offer Wide Message"; }

std::size_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    bid_size_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_priority_customer_size_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_condition_ = static_cast<BidCondition>(wire::read_char(data + offset));
    offset += 1;

    offer_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    offer_size_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    offer_priority_customer_size_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    offer_condition_ = static_cast<OfferCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_price_long_.mantissa()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_size_long_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_priority_customer_size_long_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(bid_condition_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(offer_price_long_.mantissa()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(offer_size_long_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(offer_priority_customer_size_long_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(offer_condition_));
    offset += 1;

    return offset;
}

std::size_t SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::encoded_size() const {
    return wire_size;
}

void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::clone() const {
    return std::make_unique<SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage>(*this);
}

void SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::print(std::ostream& out) const {
    out << "SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", bid_price_long=";
    out << bid_price_long_;
    out << ", bid_size_long=";
    out << bid_size_long_;
    out << ", bid_priority_customer_size_long=";
    out << bid_priority_customer_size_long_;
    out << ", bid_condition=";
    out << bid_condition_;
    out << ", offer_price_long=";
    out << offer_price_long_;
    out << ", offer_size_long=";
    out << offer_size_long_;
    out << ", offer_priority_customer_size_long=";
    out << offer_priority_customer_size_long_;
    out << ", offer_condition=";
    out << offer_condition_;
    out << '}';
}

bool SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::operator==(const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && bid_price_long_ == other.bid_price_long_
        && bid_size_long_ == other.bid_size_long_
        && bid_priority_customer_size_long_ == other.bid_priority_customer_size_long_
        && bid_condition_ == other.bid_condition_
        && offer_price_long_ == other.offer_price_long_
        && offer_size_long_ == other.offer_size_long_
        && offer_priority_customer_size_long_ == other.offer_priority_customer_size_long_
        && offer_condition_ == other.offer_condition_;
}

bool SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::operator!=(const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
