#include "WideComplexTopOfMarketOfferMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

WideComplexTopOfMarketOfferMessage::WideComplexTopOfMarketOfferMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, Decimal wide_price, std::uint32_t wide_size, const std::array<std::byte, 4>& reserved_4, TopOfMarketQuoteCondition top_of_market_quote_condition)
  : nanoseconds_(nanoseconds), strategy_id_(strategy_id), wide_price_(wide_price), wide_size_(wide_size), reserved_4_(reserved_4), top_of_market_quote_condition_(top_of_market_quote_condition) {}

std::chrono::nanoseconds WideComplexTopOfMarketOfferMessage::nanoseconds() const { return nanoseconds_; }
void WideComplexTopOfMarketOfferMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t WideComplexTopOfMarketOfferMessage::strategy_id() const { return strategy_id_; }
void WideComplexTopOfMarketOfferMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

Decimal WideComplexTopOfMarketOfferMessage::wide_price() const { return wide_price_; }
void WideComplexTopOfMarketOfferMessage::set_wide_price(Decimal value) { wide_price_ = value; }

std::uint32_t WideComplexTopOfMarketOfferMessage::wide_size() const { return wide_size_; }
void WideComplexTopOfMarketOfferMessage::set_wide_size(std::uint32_t value) { wide_size_ = value; }

const std::array<std::byte, 4>& WideComplexTopOfMarketOfferMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& WideComplexTopOfMarketOfferMessage::reserved_4() { return reserved_4_; }
void WideComplexTopOfMarketOfferMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

TopOfMarketQuoteCondition WideComplexTopOfMarketOfferMessage::top_of_market_quote_condition() const { return top_of_market_quote_condition_; }
void WideComplexTopOfMarketOfferMessage::set_top_of_market_quote_condition(TopOfMarketQuoteCondition value) { top_of_market_quote_condition_ = value; }

DataCode WideComplexTopOfMarketOfferMessage::type() const { return message_type; }

std::string_view WideComplexTopOfMarketOfferMessage::name() const { return "Wide Complex Top Of Market Offer Message"; }

std::size_t WideComplexTopOfMarketOfferMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("WideComplexTopOfMarketOfferMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wide_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wide_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    top_of_market_quote_condition_ = static_cast<TopOfMarketQuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t WideComplexTopOfMarketOfferMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("WideComplexTopOfMarketOfferMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(wide_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(wide_size_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(top_of_market_quote_condition_));
    offset += 1;

    return offset;
}

std::size_t WideComplexTopOfMarketOfferMessage::encoded_size() const {
    return wire_size;
}

void WideComplexTopOfMarketOfferMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> WideComplexTopOfMarketOfferMessage::clone() const {
    return std::make_unique<WideComplexTopOfMarketOfferMessage>(*this);
}

void WideComplexTopOfMarketOfferMessage::print(std::ostream& out) const {
    out << "WideComplexTopOfMarketOfferMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", wide_price=";
    out << wide_price_;
    out << ", wide_size=";
    out << wide_size_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", top_of_market_quote_condition=";
    out << top_of_market_quote_condition_;
    out << '}';
}

bool WideComplexTopOfMarketOfferMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const WideComplexTopOfMarketOfferMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool WideComplexTopOfMarketOfferMessage::operator==(const WideComplexTopOfMarketOfferMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && strategy_id_ == other.strategy_id_
        && wide_price_ == other.wide_price_
        && wide_size_ == other.wide_size_
        && reserved_4_ == other.reserved_4_
        && top_of_market_quote_condition_ == other.top_of_market_quote_condition_;
}

bool WideComplexTopOfMarketOfferMessage::operator!=(const WideComplexTopOfMarketOfferMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
