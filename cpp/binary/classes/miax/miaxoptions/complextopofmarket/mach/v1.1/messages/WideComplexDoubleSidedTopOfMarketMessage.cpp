#include "WideComplexDoubleSidedTopOfMarketMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

WideComplexDoubleSidedTopOfMarketMessage::WideComplexDoubleSidedTopOfMarketMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, const WideBid& wide_bid, const WideOffer& wide_offer)
  : nanoseconds_(nanoseconds), strategy_id_(strategy_id), wide_bid_(wide_bid), wide_offer_(wide_offer) {}

std::chrono::nanoseconds WideComplexDoubleSidedTopOfMarketMessage::nanoseconds() const { return nanoseconds_; }
void WideComplexDoubleSidedTopOfMarketMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t WideComplexDoubleSidedTopOfMarketMessage::strategy_id() const { return strategy_id_; }
void WideComplexDoubleSidedTopOfMarketMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

const WideBid& WideComplexDoubleSidedTopOfMarketMessage::wide_bid() const { return wide_bid_; }
WideBid& WideComplexDoubleSidedTopOfMarketMessage::wide_bid() { return wide_bid_; }
void WideComplexDoubleSidedTopOfMarketMessage::set_wide_bid(const WideBid& value) { wide_bid_ = value; }

const WideOffer& WideComplexDoubleSidedTopOfMarketMessage::wide_offer() const { return wide_offer_; }
WideOffer& WideComplexDoubleSidedTopOfMarketMessage::wide_offer() { return wide_offer_; }
void WideComplexDoubleSidedTopOfMarketMessage::set_wide_offer(const WideOffer& value) { wide_offer_ = value; }

DataCode WideComplexDoubleSidedTopOfMarketMessage::type() const { return message_type; }

std::string_view WideComplexDoubleSidedTopOfMarketMessage::name() const { return "Wide Complex Double Sided Top Of Market Message"; }

std::size_t WideComplexDoubleSidedTopOfMarketMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("WideComplexDoubleSidedTopOfMarketMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += wide_bid_.decode(data + offset, length - offset);

    offset += wide_offer_.decode(data + offset, length - offset);

    return offset;
}

std::size_t WideComplexDoubleSidedTopOfMarketMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("WideComplexDoubleSidedTopOfMarketMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    offset += wide_bid_.encode(data + offset, capacity - offset);

    offset += wide_offer_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t WideComplexDoubleSidedTopOfMarketMessage::encoded_size() const {
    return wire_size;
}

void WideComplexDoubleSidedTopOfMarketMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> WideComplexDoubleSidedTopOfMarketMessage::clone() const {
    return std::make_unique<WideComplexDoubleSidedTopOfMarketMessage>(*this);
}

void WideComplexDoubleSidedTopOfMarketMessage::print(std::ostream& out) const {
    out << "WideComplexDoubleSidedTopOfMarketMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", wide_bid=";
    wide_bid_.print(out);
    out << ", wide_offer=";
    wide_offer_.print(out);
    out << '}';
}

bool WideComplexDoubleSidedTopOfMarketMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const WideComplexDoubleSidedTopOfMarketMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool WideComplexDoubleSidedTopOfMarketMessage::operator==(const WideComplexDoubleSidedTopOfMarketMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && strategy_id_ == other.strategy_id_
        && wide_bid_ == other.wide_bid_
        && wide_offer_ == other.wide_offer_;
}

bool WideComplexDoubleSidedTopOfMarketMessage::operator!=(const WideComplexDoubleSidedTopOfMarketMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
