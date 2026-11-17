// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TradingSessionUpdate.cpp
#include "TradingSessionUpdate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

TradingSessionUpdate::TradingSessionUpdate(std::uint8_t matching_engine_id, std::uint8_t trading_session_id)
  : matching_engine_id_(matching_engine_id), trading_session_id_(trading_session_id) {}

std::uint8_t TradingSessionUpdate::matching_engine_id() const { return matching_engine_id_; }
void TradingSessionUpdate::set_matching_engine_id(std::uint8_t value) { matching_engine_id_ = value; }

std::uint8_t TradingSessionUpdate::trading_session_id() const { return trading_session_id_; }
void TradingSessionUpdate::set_trading_session_id(std::uint8_t value) { trading_session_id_ = value; }

TcpMessageCode TradingSessionUpdate::type() const { return message_type; }

std::string_view TradingSessionUpdate::name() const { return "Trading Session Update"; }

std::size_t TradingSessionUpdate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingSessionUpdate", wire_size, length);

    matching_engine_id_ = wire::read_u8(data + offset);
    offset += 1;

    trading_session_id_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t TradingSessionUpdate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingSessionUpdate", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(matching_engine_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    return offset;
}

std::size_t TradingSessionUpdate::encoded_size() const {
    return wire_size;
}

void TradingSessionUpdate::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> TradingSessionUpdate::clone() const {
    return std::make_unique<TradingSessionUpdate>(*this);
}

void TradingSessionUpdate::print(std::ostream& out) const {
    out << "TradingSessionUpdate{";
    out << "matching_engine_id=";
    out << static_cast<int>(matching_engine_id_);
    out << ", trading_session_id=";
    out << static_cast<int>(trading_session_id_);
    out << '}';
}

bool TradingSessionUpdate::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const TradingSessionUpdate*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingSessionUpdate::operator==(const TradingSessionUpdate& other) const {
    return matching_engine_id_ == other.matching_engine_id_
        && trading_session_id_ == other.trading_session_id_;
}

bool TradingSessionUpdate::operator!=(const TradingSessionUpdate& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
