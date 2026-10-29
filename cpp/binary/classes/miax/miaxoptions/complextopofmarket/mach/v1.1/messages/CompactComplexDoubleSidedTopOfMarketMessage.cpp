#include "CompactComplexDoubleSidedTopOfMarketMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

CompactComplexDoubleSidedTopOfMarketMessage::CompactComplexDoubleSidedTopOfMarketMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, const CompactBid& compact_bid, const CompactOffer& compact_offer)
  : nanoseconds_(nanoseconds), strategy_id_(strategy_id), compact_bid_(compact_bid), compact_offer_(compact_offer) {}

std::chrono::nanoseconds CompactComplexDoubleSidedTopOfMarketMessage::nanoseconds() const { return nanoseconds_; }
void CompactComplexDoubleSidedTopOfMarketMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t CompactComplexDoubleSidedTopOfMarketMessage::strategy_id() const { return strategy_id_; }
void CompactComplexDoubleSidedTopOfMarketMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

const CompactBid& CompactComplexDoubleSidedTopOfMarketMessage::compact_bid() const { return compact_bid_; }
CompactBid& CompactComplexDoubleSidedTopOfMarketMessage::compact_bid() { return compact_bid_; }
void CompactComplexDoubleSidedTopOfMarketMessage::set_compact_bid(const CompactBid& value) { compact_bid_ = value; }

const CompactOffer& CompactComplexDoubleSidedTopOfMarketMessage::compact_offer() const { return compact_offer_; }
CompactOffer& CompactComplexDoubleSidedTopOfMarketMessage::compact_offer() { return compact_offer_; }
void CompactComplexDoubleSidedTopOfMarketMessage::set_compact_offer(const CompactOffer& value) { compact_offer_ = value; }

DataCode CompactComplexDoubleSidedTopOfMarketMessage::type() const { return message_type; }

std::string_view CompactComplexDoubleSidedTopOfMarketMessage::name() const { return "Compact Complex Double Sided Top Of Market Message"; }

std::size_t CompactComplexDoubleSidedTopOfMarketMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CompactComplexDoubleSidedTopOfMarketMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += compact_bid_.decode(data + offset, length - offset);

    offset += compact_offer_.decode(data + offset, length - offset);

    return offset;
}

std::size_t CompactComplexDoubleSidedTopOfMarketMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CompactComplexDoubleSidedTopOfMarketMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    offset += compact_bid_.encode(data + offset, capacity - offset);

    offset += compact_offer_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t CompactComplexDoubleSidedTopOfMarketMessage::encoded_size() const {
    return wire_size;
}

void CompactComplexDoubleSidedTopOfMarketMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> CompactComplexDoubleSidedTopOfMarketMessage::clone() const {
    return std::make_unique<CompactComplexDoubleSidedTopOfMarketMessage>(*this);
}

void CompactComplexDoubleSidedTopOfMarketMessage::print(std::ostream& out) const {
    out << "CompactComplexDoubleSidedTopOfMarketMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", compact_bid=";
    compact_bid_.print(out);
    out << ", compact_offer=";
    compact_offer_.print(out);
    out << '}';
}

bool CompactComplexDoubleSidedTopOfMarketMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const CompactComplexDoubleSidedTopOfMarketMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CompactComplexDoubleSidedTopOfMarketMessage::operator==(const CompactComplexDoubleSidedTopOfMarketMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && strategy_id_ == other.strategy_id_
        && compact_bid_ == other.compact_bid_
        && compact_offer_ == other.compact_offer_;
}

bool CompactComplexDoubleSidedTopOfMarketMessage::operator!=(const CompactComplexDoubleSidedTopOfMarketMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
