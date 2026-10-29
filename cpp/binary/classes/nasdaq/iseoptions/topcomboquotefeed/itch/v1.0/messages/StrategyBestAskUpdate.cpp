#include "StrategyBestAskUpdate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

StrategyBestAskUpdate::StrategyBestAskUpdate(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, QuoteCondition quote_condition, Decimal price, std::uint32_t size, std::uint32_t cust_size, std::uint32_t pro_cust_size, std::uint32_t ntt_size, std::uint32_t market_size, std::uint32_t ntt_market_size)
  : timestamp_(timestamp), strategy_id_(strategy_id), quote_condition_(quote_condition), price_(price), size_(size), cust_size_(cust_size), pro_cust_size_(pro_cust_size), ntt_size_(ntt_size), market_size_(market_size), ntt_market_size_(ntt_market_size) {}

std::chrono::nanoseconds StrategyBestAskUpdate::timestamp() const { return timestamp_; }
void StrategyBestAskUpdate::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t StrategyBestAskUpdate::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t StrategyBestAskUpdate::strategy_id() const { return strategy_id_; }
void StrategyBestAskUpdate::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

QuoteCondition StrategyBestAskUpdate::quote_condition() const { return quote_condition_; }
void StrategyBestAskUpdate::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

Decimal StrategyBestAskUpdate::price() const { return price_; }
void StrategyBestAskUpdate::set_price(Decimal value) { price_ = value; }

std::uint32_t StrategyBestAskUpdate::size() const { return size_; }
void StrategyBestAskUpdate::set_size(std::uint32_t value) { size_ = value; }

std::uint32_t StrategyBestAskUpdate::cust_size() const { return cust_size_; }
void StrategyBestAskUpdate::set_cust_size(std::uint32_t value) { cust_size_ = value; }

std::uint32_t StrategyBestAskUpdate::pro_cust_size() const { return pro_cust_size_; }
void StrategyBestAskUpdate::set_pro_cust_size(std::uint32_t value) { pro_cust_size_ = value; }

std::uint32_t StrategyBestAskUpdate::ntt_size() const { return ntt_size_; }
void StrategyBestAskUpdate::set_ntt_size(std::uint32_t value) { ntt_size_ = value; }

std::uint32_t StrategyBestAskUpdate::market_size() const { return market_size_; }
void StrategyBestAskUpdate::set_market_size(std::uint32_t value) { market_size_ = value; }

std::uint32_t StrategyBestAskUpdate::ntt_market_size() const { return ntt_market_size_; }
void StrategyBestAskUpdate::set_ntt_market_size(std::uint32_t value) { ntt_market_size_ = value; }

MessageCode StrategyBestAskUpdate::type() const { return message_type; }

std::string_view StrategyBestAskUpdate::name() const { return "Strategy Best Ask Update"; }

std::size_t StrategyBestAskUpdate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StrategyBestAskUpdate", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    size_ = wire::read_u32_be(data + offset);
    offset += 4;

    cust_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    pro_cust_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ntt_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    market_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ntt_market_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t StrategyBestAskUpdate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StrategyBestAskUpdate", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cust_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(pro_cust_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ntt_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(market_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ntt_market_size_));
    offset += 4;

    return offset;
}

std::size_t StrategyBestAskUpdate::encoded_size() const {
    return wire_size;
}

void StrategyBestAskUpdate::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StrategyBestAskUpdate::clone() const {
    return std::make_unique<StrategyBestAskUpdate>(*this);
}

void StrategyBestAskUpdate::print(std::ostream& out) const {
    out << "StrategyBestAskUpdate{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", cust_size=";
    out << cust_size_;
    out << ", pro_cust_size=";
    out << pro_cust_size_;
    out << ", ntt_size=";
    out << ntt_size_;
    out << ", market_size=";
    out << market_size_;
    out << ", ntt_market_size=";
    out << ntt_market_size_;
    out << '}';
}

bool StrategyBestAskUpdate::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StrategyBestAskUpdate*>(&other);
    return that != nullptr && *this == *that;
}

bool StrategyBestAskUpdate::operator==(const StrategyBestAskUpdate& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && quote_condition_ == other.quote_condition_
        && price_ == other.price_
        && size_ == other.size_
        && cust_size_ == other.cust_size_
        && pro_cust_size_ == other.pro_cust_size_
        && ntt_size_ == other.ntt_size_
        && market_size_ == other.market_size_
        && ntt_market_size_ == other.ntt_market_size_;
}

bool StrategyBestAskUpdate::operator!=(const StrategyBestAskUpdate& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
