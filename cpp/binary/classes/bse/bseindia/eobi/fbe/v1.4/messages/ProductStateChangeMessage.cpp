#include "ProductStateChangeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

ProductStateChangeMessage::ProductStateChangeMessage(TradingSessionId trading_session_id, TradingSessionSubId trading_session_sub_id, TradSesStatus trad_ses_status, FastMarketIndicator fast_market_indicator, const std::array<std::byte, 4>& pad_4, std::chrono::nanoseconds transact_time)
  : trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), trad_ses_status_(trad_ses_status), fast_market_indicator_(fast_market_indicator), pad_4_(pad_4), transact_time_(transact_time) {}

TradingSessionId ProductStateChangeMessage::trading_session_id() const { return trading_session_id_; }
void ProductStateChangeMessage::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

TradingSessionSubId ProductStateChangeMessage::trading_session_sub_id() const { return trading_session_sub_id_; }
void ProductStateChangeMessage::set_trading_session_sub_id(TradingSessionSubId value) { trading_session_sub_id_ = value; }

TradSesStatus ProductStateChangeMessage::trad_ses_status() const { return trad_ses_status_; }
void ProductStateChangeMessage::set_trad_ses_status(TradSesStatus value) { trad_ses_status_ = value; }

FastMarketIndicator ProductStateChangeMessage::fast_market_indicator() const { return fast_market_indicator_; }
void ProductStateChangeMessage::set_fast_market_indicator(FastMarketIndicator value) { fast_market_indicator_ = value; }

const std::array<std::byte, 4>& ProductStateChangeMessage::pad_4() const { return pad_4_; }
std::array<std::byte, 4>& ProductStateChangeMessage::pad_4() { return pad_4_; }
void ProductStateChangeMessage::set_pad_4(const std::array<std::byte, 4>& value) { pad_4_ = value; }

std::chrono::nanoseconds ProductStateChangeMessage::transact_time() const { return transact_time_; }
void ProductStateChangeMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

MessageCode ProductStateChangeMessage::type() const { return message_type; }

std::string_view ProductStateChangeMessage::name() const { return "Product State Change Message"; }

std::size_t ProductStateChangeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ProductStateChangeMessage", wire_size, length);

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    trading_session_sub_id_ = static_cast<TradingSessionSubId>(wire::read_u8(data + offset));
    offset += 1;

    trad_ses_status_ = static_cast<TradSesStatus>(wire::read_u8(data + offset));
    offset += 1;

    fast_market_indicator_ = static_cast<FastMarketIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t ProductStateChangeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ProductStateChangeMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_sub_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trad_ses_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(fast_market_indicator_));
    offset += 1;

    wire::write_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    return offset;
}

std::size_t ProductStateChangeMessage::encoded_size() const {
    return wire_size;
}

void ProductStateChangeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ProductStateChangeMessage::clone() const {
    return std::make_unique<ProductStateChangeMessage>(*this);
}

void ProductStateChangeMessage::print(std::ostream& out) const {
    out << "ProductStateChangeMessage{";
    out << "trading_session_id=";
    out << trading_session_id_;
    out << ", trading_session_sub_id=";
    out << trading_session_sub_id_;
    out << ", trad_ses_status=";
    out << trad_ses_status_;
    out << ", fast_market_indicator=";
    out << fast_market_indicator_;
    out << ", pad_4=";
    print::hex(out, pad_4_.data(), pad_4_.size());
    out << ", transact_time=";
    out << transact_time_.count();
    out << '}';
}

bool ProductStateChangeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ProductStateChangeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ProductStateChangeMessage::operator==(const ProductStateChangeMessage& other) const {
    return trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && trad_ses_status_ == other.trad_ses_status_
        && fast_market_indicator_ == other.fast_market_indicator_
        && pad_4_ == other.pad_4_
        && transact_time_ == other.transact_time_;
}

bool ProductStateChangeMessage::operator!=(const ProductStateChangeMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
