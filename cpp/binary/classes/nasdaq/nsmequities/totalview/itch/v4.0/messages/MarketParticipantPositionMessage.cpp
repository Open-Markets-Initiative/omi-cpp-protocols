#include "MarketParticipantPositionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

MarketParticipantPositionMessage::MarketParticipantPositionMessage(std::chrono::nanoseconds nanoseconds, const std::string& mpid, const std::string& stock, PrimaryMarketMaker primary_market_maker, MarketMakerMode market_maker_mode, MarketParticipantState market_participant_state)
  : nanoseconds_(nanoseconds), mpid_(mpid), stock_(stock), primary_market_maker_(primary_market_maker), market_maker_mode_(market_maker_mode), market_participant_state_(market_participant_state) {}

std::chrono::nanoseconds MarketParticipantPositionMessage::nanoseconds() const { return nanoseconds_; }
void MarketParticipantPositionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& MarketParticipantPositionMessage::mpid() const { return mpid_; }
std::string& MarketParticipantPositionMessage::mpid() { return mpid_; }
void MarketParticipantPositionMessage::set_mpid(const std::string& value) { mpid_ = value; }

const std::string& MarketParticipantPositionMessage::stock() const { return stock_; }
std::string& MarketParticipantPositionMessage::stock() { return stock_; }
void MarketParticipantPositionMessage::set_stock(const std::string& value) { stock_ = value; }

PrimaryMarketMaker MarketParticipantPositionMessage::primary_market_maker() const { return primary_market_maker_; }
void MarketParticipantPositionMessage::set_primary_market_maker(PrimaryMarketMaker value) { primary_market_maker_ = value; }

MarketMakerMode MarketParticipantPositionMessage::market_maker_mode() const { return market_maker_mode_; }
void MarketParticipantPositionMessage::set_market_maker_mode(MarketMakerMode value) { market_maker_mode_ = value; }

MarketParticipantState MarketParticipantPositionMessage::market_participant_state() const { return market_participant_state_; }
void MarketParticipantPositionMessage::set_market_participant_state(MarketParticipantState value) { market_participant_state_ = value; }

SequencedMessageCode MarketParticipantPositionMessage::type() const { return message_type; }

std::string_view MarketParticipantPositionMessage::name() const { return "Market Participant Position Message"; }

std::size_t MarketParticipantPositionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketParticipantPositionMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    mpid_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    stock_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    primary_market_maker_ = static_cast<PrimaryMarketMaker>(wire::read_char(data + offset));
    offset += 1;

    market_maker_mode_ = static_cast<MarketMakerMode>(wire::read_char(data + offset));
    offset += 1;

    market_participant_state_ = static_cast<MarketParticipantState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MarketParticipantPositionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketParticipantPositionMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', mpid_);
    offset += 4;

    wire::write_text(data + offset, 6, ' ', stock_);
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(primary_market_maker_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(market_maker_mode_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(market_participant_state_));
    offset += 1;

    return offset;
}

std::size_t MarketParticipantPositionMessage::encoded_size() const {
    return wire_size;
}

void MarketParticipantPositionMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> MarketParticipantPositionMessage::clone() const {
    return std::make_unique<MarketParticipantPositionMessage>(*this);
}

void MarketParticipantPositionMessage::print(std::ostream& out) const {
    out << "MarketParticipantPositionMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", mpid=";
    print::text(out, mpid_);
    out << ", stock=";
    print::text(out, stock_);
    out << ", primary_market_maker=";
    out << primary_market_maker_;
    out << ", market_maker_mode=";
    out << market_maker_mode_;
    out << ", market_participant_state=";
    out << market_participant_state_;
    out << '}';
}

bool MarketParticipantPositionMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const MarketParticipantPositionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketParticipantPositionMessage::operator==(const MarketParticipantPositionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && mpid_ == other.mpid_
        && stock_ == other.stock_
        && primary_market_maker_ == other.primary_market_maker_
        && market_maker_mode_ == other.market_maker_mode_
        && market_participant_state_ == other.market_participant_state_;
}

bool MarketParticipantPositionMessage::operator!=(const MarketParticipantPositionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
