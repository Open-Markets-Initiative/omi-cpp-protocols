#include "TradingSessionStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

TradingSessionStatusMessage::TradingSessionStatusMessage(std::chrono::nanoseconds timestamp, TradingSession trading_session)
  : timestamp_(timestamp), trading_session_(trading_session) {}

std::chrono::nanoseconds TradingSessionStatusMessage::timestamp() const { return timestamp_; }
void TradingSessionStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

TradingSession TradingSessionStatusMessage::trading_session() const { return trading_session_; }
void TradingSessionStatusMessage::set_trading_session(TradingSession value) { trading_session_ = value; }

PayloadCode TradingSessionStatusMessage::type() const { return message_type; }

std::string_view TradingSessionStatusMessage::name() const { return "Trading Session Status Message"; }

std::size_t TradingSessionStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingSessionStatusMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    trading_session_ = static_cast<TradingSession>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradingSessionStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingSessionStatusMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trading_session_));
    offset += 1;

    return offset;
}

std::size_t TradingSessionStatusMessage::encoded_size() const {
    return wire_size;
}

void TradingSessionStatusMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> TradingSessionStatusMessage::clone() const {
    return std::make_unique<TradingSessionStatusMessage>(*this);
}

void TradingSessionStatusMessage::print(std::ostream& out) const {
    out << "TradingSessionStatusMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", trading_session=";
    out << trading_session_;
    out << '}';
}

bool TradingSessionStatusMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const TradingSessionStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingSessionStatusMessage::operator==(const TradingSessionStatusMessage& other) const {
    return timestamp_ == other.timestamp_
        && trading_session_ == other.trading_session_;
}

bool TradingSessionStatusMessage::operator!=(const TradingSessionStatusMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
