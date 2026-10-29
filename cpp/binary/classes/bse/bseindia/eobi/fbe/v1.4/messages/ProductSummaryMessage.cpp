#include "ProductSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

ProductSummaryMessage::ProductSummaryMessage(std::uint32_t last_msg_seq_num_processed, TradingSessionId trading_session_id, TradingSessionSubId trading_session_sub_id, TradSesStatus trad_ses_status, FastMarketIndicator fast_market_indicator)
  : last_msg_seq_num_processed_(last_msg_seq_num_processed), trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), trad_ses_status_(trad_ses_status), fast_market_indicator_(fast_market_indicator) {}

std::uint32_t ProductSummaryMessage::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void ProductSummaryMessage::set_last_msg_seq_num_processed(std::uint32_t value) { last_msg_seq_num_processed_ = value; }

TradingSessionId ProductSummaryMessage::trading_session_id() const { return trading_session_id_; }
void ProductSummaryMessage::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

TradingSessionSubId ProductSummaryMessage::trading_session_sub_id() const { return trading_session_sub_id_; }
void ProductSummaryMessage::set_trading_session_sub_id(TradingSessionSubId value) { trading_session_sub_id_ = value; }

TradSesStatus ProductSummaryMessage::trad_ses_status() const { return trad_ses_status_; }
void ProductSummaryMessage::set_trad_ses_status(TradSesStatus value) { trad_ses_status_ = value; }

FastMarketIndicator ProductSummaryMessage::fast_market_indicator() const { return fast_market_indicator_; }
void ProductSummaryMessage::set_fast_market_indicator(FastMarketIndicator value) { fast_market_indicator_ = value; }

MessageCode ProductSummaryMessage::type() const { return message_type; }

std::string_view ProductSummaryMessage::name() const { return "Product Summary Message"; }

std::size_t ProductSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ProductSummaryMessage", wire_size, length);

    last_msg_seq_num_processed_ = wire::read_u32_le(data + offset);
    offset += 4;

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    trading_session_sub_id_ = static_cast<TradingSessionSubId>(wire::read_u8(data + offset));
    offset += 1;

    trad_ses_status_ = static_cast<TradSesStatus>(wire::read_u8(data + offset));
    offset += 1;

    fast_market_indicator_ = static_cast<FastMarketIndicator>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t ProductSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ProductSummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_msg_seq_num_processed_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_sub_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trad_ses_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(fast_market_indicator_));
    offset += 1;

    return offset;
}

std::size_t ProductSummaryMessage::encoded_size() const {
    return wire_size;
}

void ProductSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ProductSummaryMessage::clone() const {
    return std::make_unique<ProductSummaryMessage>(*this);
}

void ProductSummaryMessage::print(std::ostream& out) const {
    out << "ProductSummaryMessage{";
    out << "last_msg_seq_num_processed=";
    out << last_msg_seq_num_processed_;
    out << ", trading_session_id=";
    out << trading_session_id_;
    out << ", trading_session_sub_id=";
    out << trading_session_sub_id_;
    out << ", trad_ses_status=";
    out << trad_ses_status_;
    out << ", fast_market_indicator=";
    out << fast_market_indicator_;
    out << '}';
}

bool ProductSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ProductSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ProductSummaryMessage::operator==(const ProductSummaryMessage& other) const {
    return last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && trad_ses_status_ == other.trad_ses_status_
        && fast_market_indicator_ == other.fast_market_indicator_;
}

bool ProductSummaryMessage::operator!=(const ProductSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
