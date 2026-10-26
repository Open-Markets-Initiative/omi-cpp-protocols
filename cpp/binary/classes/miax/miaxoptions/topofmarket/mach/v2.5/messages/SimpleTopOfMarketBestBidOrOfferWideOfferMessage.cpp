#include "SimpleTopOfMarketBestBidOrOfferWideOfferMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SimpleTopOfMarketBestBidOrOfferWideOfferMessage::SimpleTopOfMarketBestBidOrOfferWideOfferMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, Decimal mbbo_price_long, std::uint32_t mbbo_size_long, std::uint32_t mbbo_priority_customer_size_long, MbboCondition mbbo_condition)
  : nanoseconds_(nanoseconds), product_id_(product_id), mbbo_price_long_(mbbo_price_long), mbbo_size_long_(mbbo_size_long), mbbo_priority_customer_size_long_(mbbo_priority_customer_size_long), mbbo_condition_(mbbo_condition) {}

std::chrono::nanoseconds SimpleTopOfMarketBestBidOrOfferWideOfferMessage::nanoseconds() const { return nanoseconds_; }
void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SimpleTopOfMarketBestBidOrOfferWideOfferMessage::product_id() const { return product_id_; }
void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::set_product_id(std::uint32_t value) { product_id_ = value; }

Decimal SimpleTopOfMarketBestBidOrOfferWideOfferMessage::mbbo_price_long() const { return mbbo_price_long_; }
void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::set_mbbo_price_long(Decimal value) { mbbo_price_long_ = value; }

std::uint32_t SimpleTopOfMarketBestBidOrOfferWideOfferMessage::mbbo_size_long() const { return mbbo_size_long_; }
void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::set_mbbo_size_long(std::uint32_t value) { mbbo_size_long_ = value; }

std::uint32_t SimpleTopOfMarketBestBidOrOfferWideOfferMessage::mbbo_priority_customer_size_long() const { return mbbo_priority_customer_size_long_; }
void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::set_mbbo_priority_customer_size_long(std::uint32_t value) { mbbo_priority_customer_size_long_ = value; }

MbboCondition SimpleTopOfMarketBestBidOrOfferWideOfferMessage::mbbo_condition() const { return mbbo_condition_; }
void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::set_mbbo_condition(MbboCondition value) { mbbo_condition_ = value; }

DataCode SimpleTopOfMarketBestBidOrOfferWideOfferMessage::type() const { return message_type; }

std::string_view SimpleTopOfMarketBestBidOrOfferWideOfferMessage::name() const { return "Simple Top Of Market Best Bid Or Offer Wide Offer Message"; }

std::size_t SimpleTopOfMarketBestBidOrOfferWideOfferMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SimpleTopOfMarketBestBidOrOfferWideOfferMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    product_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    mbbo_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -4);
    offset += 4;

    mbbo_size_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    mbbo_priority_customer_size_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    mbbo_condition_ = static_cast<MbboCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SimpleTopOfMarketBestBidOrOfferWideOfferMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleTopOfMarketBestBidOrOfferWideOfferMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(product_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(mbbo_price_long_.mantissa()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(mbbo_size_long_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(mbbo_priority_customer_size_long_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(mbbo_condition_));
    offset += 1;

    return offset;
}

std::size_t SimpleTopOfMarketBestBidOrOfferWideOfferMessage::encoded_size() const {
    return wire_size;
}

void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SimpleTopOfMarketBestBidOrOfferWideOfferMessage::clone() const {
    return std::make_unique<SimpleTopOfMarketBestBidOrOfferWideOfferMessage>(*this);
}

void SimpleTopOfMarketBestBidOrOfferWideOfferMessage::print(std::ostream& out) const {
    out << "SimpleTopOfMarketBestBidOrOfferWideOfferMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", product_id=";
    out << product_id_;
    out << ", mbbo_price_long=";
    out << mbbo_price_long_;
    out << ", mbbo_size_long=";
    out << mbbo_size_long_;
    out << ", mbbo_priority_customer_size_long=";
    out << mbbo_priority_customer_size_long_;
    out << ", mbbo_condition=";
    out << mbbo_condition_;
    out << '}';
}

bool SimpleTopOfMarketBestBidOrOfferWideOfferMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SimpleTopOfMarketBestBidOrOfferWideOfferMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SimpleTopOfMarketBestBidOrOfferWideOfferMessage::operator==(const SimpleTopOfMarketBestBidOrOfferWideOfferMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && product_id_ == other.product_id_
        && mbbo_price_long_ == other.mbbo_price_long_
        && mbbo_size_long_ == other.mbbo_size_long_
        && mbbo_priority_customer_size_long_ == other.mbbo_priority_customer_size_long_
        && mbbo_condition_ == other.mbbo_condition_;
}

bool SimpleTopOfMarketBestBidOrOfferWideOfferMessage::operator!=(const SimpleTopOfMarketBestBidOrOfferWideOfferMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
