#include "ProductStateChange.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

ProductStateChange::ProductStateChange(std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<TradSesStatus> trad_ses_status, std::optional<MarketCondition> market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<TesTradSesStatus> tes_trad_ses_status, const std::array<std::byte, 2>& pad2, std::optional<std::chrono::nanoseconds> transact_time)
  : trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), trad_ses_status_(trad_ses_status), market_condition_(market_condition), fast_market_indicator_(fast_market_indicator), tes_trad_ses_status_(tes_trad_ses_status), pad2_(pad2), transact_time_(transact_time) {}

std::optional<TradingSessionId> ProductStateChange::trading_session_id() const { return trading_session_id_; }
void ProductStateChange::set_trading_session_id(std::optional<TradingSessionId> value) { trading_session_id_ = value; }

std::optional<TradingSessionSubId> ProductStateChange::trading_session_sub_id() const { return trading_session_sub_id_; }
void ProductStateChange::set_trading_session_sub_id(std::optional<TradingSessionSubId> value) { trading_session_sub_id_ = value; }

std::optional<TradSesStatus> ProductStateChange::trad_ses_status() const { return trad_ses_status_; }
void ProductStateChange::set_trad_ses_status(std::optional<TradSesStatus> value) { trad_ses_status_ = value; }

std::optional<MarketCondition> ProductStateChange::market_condition() const { return market_condition_; }
void ProductStateChange::set_market_condition(std::optional<MarketCondition> value) { market_condition_ = value; }

std::optional<FastMarketIndicator> ProductStateChange::fast_market_indicator() const { return fast_market_indicator_; }
void ProductStateChange::set_fast_market_indicator(std::optional<FastMarketIndicator> value) { fast_market_indicator_ = value; }

std::optional<TesTradSesStatus> ProductStateChange::tes_trad_ses_status() const { return tes_trad_ses_status_; }
void ProductStateChange::set_tes_trad_ses_status(std::optional<TesTradSesStatus> value) { tes_trad_ses_status_ = value; }

const std::array<std::byte, 2>& ProductStateChange::pad2() const { return pad2_; }
std::array<std::byte, 2>& ProductStateChange::pad2() { return pad2_; }
void ProductStateChange::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::optional<std::chrono::nanoseconds> ProductStateChange::transact_time() const { return transact_time_; }
void ProductStateChange::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

MessageCode ProductStateChange::type() const { return message_type; }

std::string_view ProductStateChange::name() const { return "Product State Change"; }

std::size_t ProductStateChange::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ProductStateChange", wire_size, length);

    trading_session_id_ = wire::nullable_enum<TradingSessionId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trading_session_sub_id_ = wire::nullable_enum<TradingSessionSubId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trad_ses_status_ = wire::nullable_enum<TradSesStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    market_condition_ = wire::nullable_enum<MarketCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    fast_market_indicator_ = wire::nullable_enum<FastMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    tes_trad_ses_status_ = wire::nullable_enum<TesTradSesStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t ProductStateChange::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ProductStateChange", wire_size, capacity);

    wire::write_u8(data + offset, trading_session_id_ ? static_cast<std::uint8_t>(*trading_session_id_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, trading_session_sub_id_ ? static_cast<std::uint8_t>(*trading_session_sub_id_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, trad_ses_status_ ? static_cast<std::uint8_t>(*trad_ses_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, market_condition_ ? static_cast<std::uint8_t>(*market_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, fast_market_indicator_ ? static_cast<std::uint8_t>(*fast_market_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, tes_trad_ses_status_ ? static_cast<std::uint8_t>(*tes_trad_ses_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t ProductStateChange::encoded_size() const {
    return wire_size;
}

void ProductStateChange::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ProductStateChange::clone() const {
    return std::make_unique<ProductStateChange>(*this);
}

void ProductStateChange::print(std::ostream& out) const {
    out << "ProductStateChange{";
    out << "trading_session_id=";
    print::optional(out, trading_session_id_);
    out << ", trading_session_sub_id=";
    print::optional(out, trading_session_sub_id_);
    out << ", trad_ses_status=";
    print::optional(out, trad_ses_status_);
    out << ", market_condition=";
    print::optional(out, market_condition_);
    out << ", fast_market_indicator=";
    print::optional(out, fast_market_indicator_);
    out << ", tes_trad_ses_status=";
    print::optional(out, tes_trad_ses_status_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << '}';
}

bool ProductStateChange::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ProductStateChange*>(&other);
    return that != nullptr && *this == *that;
}

bool ProductStateChange::operator==(const ProductStateChange& other) const {
    return trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && trad_ses_status_ == other.trad_ses_status_
        && market_condition_ == other.market_condition_
        && fast_market_indicator_ == other.fast_market_indicator_
        && tes_trad_ses_status_ == other.tes_trad_ses_status_
        && pad2_ == other.pad2_
        && transact_time_ == other.transact_time_;
}

bool ProductStateChange::operator!=(const ProductStateChange& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
