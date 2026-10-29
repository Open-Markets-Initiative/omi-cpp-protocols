#include "ProductSummary.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

ProductSummary::ProductSummary(std::optional<std::uint32_t> last_msg_seq_num_processed, std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<TradSesStatus> trad_ses_status, std::optional<FastMarketIndicator> fast_market_indicator)
  : last_msg_seq_num_processed_(last_msg_seq_num_processed), trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), trad_ses_status_(trad_ses_status), fast_market_indicator_(fast_market_indicator) {}

std::optional<std::uint32_t> ProductSummary::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void ProductSummary::set_last_msg_seq_num_processed(std::optional<std::uint32_t> value) { last_msg_seq_num_processed_ = value; }

std::optional<TradingSessionId> ProductSummary::trading_session_id() const { return trading_session_id_; }
void ProductSummary::set_trading_session_id(std::optional<TradingSessionId> value) { trading_session_id_ = value; }

std::optional<TradingSessionSubId> ProductSummary::trading_session_sub_id() const { return trading_session_sub_id_; }
void ProductSummary::set_trading_session_sub_id(std::optional<TradingSessionSubId> value) { trading_session_sub_id_ = value; }

std::optional<TradSesStatus> ProductSummary::trad_ses_status() const { return trad_ses_status_; }
void ProductSummary::set_trad_ses_status(std::optional<TradSesStatus> value) { trad_ses_status_ = value; }

std::optional<FastMarketIndicator> ProductSummary::fast_market_indicator() const { return fast_market_indicator_; }
void ProductSummary::set_fast_market_indicator(std::optional<FastMarketIndicator> value) { fast_market_indicator_ = value; }

MessageCode ProductSummary::type() const { return message_type; }

std::string_view ProductSummary::name() const { return "Product Summary"; }

std::size_t ProductSummary::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ProductSummary", wire_size, length);

    last_msg_seq_num_processed_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    trading_session_id_ = wire::nullable_enum<TradingSessionId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trading_session_sub_id_ = wire::nullable_enum<TradingSessionSubId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trad_ses_status_ = wire::nullable_enum<TradSesStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    fast_market_indicator_ = wire::nullable_enum<FastMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    return offset;
}

std::size_t ProductSummary::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ProductSummary", wire_size, capacity);

    wire::write_u32_le(data + offset, last_msg_seq_num_processed_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_u8(data + offset, trading_session_id_ ? static_cast<std::uint8_t>(*trading_session_id_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, trading_session_sub_id_ ? static_cast<std::uint8_t>(*trading_session_sub_id_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, trad_ses_status_ ? static_cast<std::uint8_t>(*trad_ses_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, fast_market_indicator_ ? static_cast<std::uint8_t>(*fast_market_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    return offset;
}

std::size_t ProductSummary::encoded_size() const {
    return wire_size;
}

void ProductSummary::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ProductSummary::clone() const {
    return std::make_unique<ProductSummary>(*this);
}

void ProductSummary::print(std::ostream& out) const {
    out << "ProductSummary{";
    out << "last_msg_seq_num_processed=";
    print::optional(out, last_msg_seq_num_processed_);
    out << ", trading_session_id=";
    print::optional(out, trading_session_id_);
    out << ", trading_session_sub_id=";
    print::optional(out, trading_session_sub_id_);
    out << ", trad_ses_status=";
    print::optional(out, trad_ses_status_);
    out << ", fast_market_indicator=";
    print::optional(out, fast_market_indicator_);
    out << '}';
}

bool ProductSummary::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ProductSummary*>(&other);
    return that != nullptr && *this == *that;
}

bool ProductSummary::operator==(const ProductSummary& other) const {
    return last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && trad_ses_status_ == other.trad_ses_status_
        && fast_market_indicator_ == other.fast_market_indicator_;
}

bool ProductSummary::operator!=(const ProductSummary& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v3_0
