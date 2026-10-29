#include "StrategyBestBidAndAskUpdate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

StrategyBestBidAndAskUpdate::StrategyBestBidAndAskUpdate(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, QuoteCondition quote_condition, Decimal bid_price, std::uint32_t bid_size, std::uint32_t bid_cust_size, std::uint32_t bid_pro_cust_size, std::uint32_t bid_ntt_size, std::uint32_t bid_market_size, std::uint32_t bid_ntt_market_size, Decimal ask_price, std::uint32_t ask_size, std::uint32_t ask_cust_size, std::uint32_t ask_pro_cust_size, std::uint32_t ask_ntt_size, std::uint32_t ask_market_size, std::uint32_t ask_ntt_market_size)
  : timestamp_(timestamp), strategy_id_(strategy_id), quote_condition_(quote_condition), bid_price_(bid_price), bid_size_(bid_size), bid_cust_size_(bid_cust_size), bid_pro_cust_size_(bid_pro_cust_size), bid_ntt_size_(bid_ntt_size), bid_market_size_(bid_market_size), bid_ntt_market_size_(bid_ntt_market_size), ask_price_(ask_price), ask_size_(ask_size), ask_cust_size_(ask_cust_size), ask_pro_cust_size_(ask_pro_cust_size), ask_ntt_size_(ask_ntt_size), ask_market_size_(ask_market_size), ask_ntt_market_size_(ask_ntt_market_size) {}

std::chrono::nanoseconds StrategyBestBidAndAskUpdate::timestamp() const { return timestamp_; }
void StrategyBestBidAndAskUpdate::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t StrategyBestBidAndAskUpdate::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t StrategyBestBidAndAskUpdate::strategy_id() const { return strategy_id_; }
void StrategyBestBidAndAskUpdate::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

QuoteCondition StrategyBestBidAndAskUpdate::quote_condition() const { return quote_condition_; }
void StrategyBestBidAndAskUpdate::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

Decimal StrategyBestBidAndAskUpdate::bid_price() const { return bid_price_; }
void StrategyBestBidAndAskUpdate::set_bid_price(Decimal value) { bid_price_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::bid_size() const { return bid_size_; }
void StrategyBestBidAndAskUpdate::set_bid_size(std::uint32_t value) { bid_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::bid_cust_size() const { return bid_cust_size_; }
void StrategyBestBidAndAskUpdate::set_bid_cust_size(std::uint32_t value) { bid_cust_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::bid_pro_cust_size() const { return bid_pro_cust_size_; }
void StrategyBestBidAndAskUpdate::set_bid_pro_cust_size(std::uint32_t value) { bid_pro_cust_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::bid_ntt_size() const { return bid_ntt_size_; }
void StrategyBestBidAndAskUpdate::set_bid_ntt_size(std::uint32_t value) { bid_ntt_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::bid_market_size() const { return bid_market_size_; }
void StrategyBestBidAndAskUpdate::set_bid_market_size(std::uint32_t value) { bid_market_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::bid_ntt_market_size() const { return bid_ntt_market_size_; }
void StrategyBestBidAndAskUpdate::set_bid_ntt_market_size(std::uint32_t value) { bid_ntt_market_size_ = value; }

Decimal StrategyBestBidAndAskUpdate::ask_price() const { return ask_price_; }
void StrategyBestBidAndAskUpdate::set_ask_price(Decimal value) { ask_price_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::ask_size() const { return ask_size_; }
void StrategyBestBidAndAskUpdate::set_ask_size(std::uint32_t value) { ask_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::ask_cust_size() const { return ask_cust_size_; }
void StrategyBestBidAndAskUpdate::set_ask_cust_size(std::uint32_t value) { ask_cust_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::ask_pro_cust_size() const { return ask_pro_cust_size_; }
void StrategyBestBidAndAskUpdate::set_ask_pro_cust_size(std::uint32_t value) { ask_pro_cust_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::ask_ntt_size() const { return ask_ntt_size_; }
void StrategyBestBidAndAskUpdate::set_ask_ntt_size(std::uint32_t value) { ask_ntt_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::ask_market_size() const { return ask_market_size_; }
void StrategyBestBidAndAskUpdate::set_ask_market_size(std::uint32_t value) { ask_market_size_ = value; }

std::uint32_t StrategyBestBidAndAskUpdate::ask_ntt_market_size() const { return ask_ntt_market_size_; }
void StrategyBestBidAndAskUpdate::set_ask_ntt_market_size(std::uint32_t value) { ask_ntt_market_size_ = value; }

MessageCode StrategyBestBidAndAskUpdate::type() const { return message_type; }

std::string_view StrategyBestBidAndAskUpdate::name() const { return "Strategy Best Bid And Ask Update"; }

std::size_t StrategyBestBidAndAskUpdate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StrategyBestBidAndAskUpdate", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_cust_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_pro_cust_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_ntt_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_market_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_ntt_market_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    ask_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_cust_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_pro_cust_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_ntt_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_market_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_ntt_market_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t StrategyBestBidAndAskUpdate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StrategyBestBidAndAskUpdate", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(bid_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_cust_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_pro_cust_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_ntt_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_market_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_ntt_market_size_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(ask_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_cust_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_pro_cust_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_ntt_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_market_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_ntt_market_size_));
    offset += 4;

    return offset;
}

std::size_t StrategyBestBidAndAskUpdate::encoded_size() const {
    return wire_size;
}

void StrategyBestBidAndAskUpdate::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StrategyBestBidAndAskUpdate::clone() const {
    return std::make_unique<StrategyBestBidAndAskUpdate>(*this);
}

void StrategyBestBidAndAskUpdate::print(std::ostream& out) const {
    out << "StrategyBestBidAndAskUpdate{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", bid_size=";
    out << bid_size_;
    out << ", bid_cust_size=";
    out << bid_cust_size_;
    out << ", bid_pro_cust_size=";
    out << bid_pro_cust_size_;
    out << ", bid_ntt_size=";
    out << bid_ntt_size_;
    out << ", bid_market_size=";
    out << bid_market_size_;
    out << ", bid_ntt_market_size=";
    out << bid_ntt_market_size_;
    out << ", ask_price=";
    out << ask_price_;
    out << ", ask_size=";
    out << ask_size_;
    out << ", ask_cust_size=";
    out << ask_cust_size_;
    out << ", ask_pro_cust_size=";
    out << ask_pro_cust_size_;
    out << ", ask_ntt_size=";
    out << ask_ntt_size_;
    out << ", ask_market_size=";
    out << ask_market_size_;
    out << ", ask_ntt_market_size=";
    out << ask_ntt_market_size_;
    out << '}';
}

bool StrategyBestBidAndAskUpdate::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StrategyBestBidAndAskUpdate*>(&other);
    return that != nullptr && *this == *that;
}

bool StrategyBestBidAndAskUpdate::operator==(const StrategyBestBidAndAskUpdate& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && quote_condition_ == other.quote_condition_
        && bid_price_ == other.bid_price_
        && bid_size_ == other.bid_size_
        && bid_cust_size_ == other.bid_cust_size_
        && bid_pro_cust_size_ == other.bid_pro_cust_size_
        && bid_ntt_size_ == other.bid_ntt_size_
        && bid_market_size_ == other.bid_market_size_
        && bid_ntt_market_size_ == other.bid_ntt_market_size_
        && ask_price_ == other.ask_price_
        && ask_size_ == other.ask_size_
        && ask_cust_size_ == other.ask_cust_size_
        && ask_pro_cust_size_ == other.ask_pro_cust_size_
        && ask_ntt_size_ == other.ask_ntt_size_
        && ask_market_size_ == other.ask_market_size_
        && ask_ntt_market_size_ == other.ask_ntt_market_size_;
}

bool StrategyBestBidAndAskUpdate::operator!=(const StrategyBestBidAndAskUpdate& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
