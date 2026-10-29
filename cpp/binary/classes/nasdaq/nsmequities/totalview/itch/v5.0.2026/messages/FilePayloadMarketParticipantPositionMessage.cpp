#include "FilePayloadMarketParticipantPositionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

FilePayloadMarketParticipantPositionMessage::FilePayloadMarketParticipantPositionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& mpid, const std::string& stock, PrimaryMarketMaker primary_market_maker, MarketMakerMode market_maker_mode, MarketParticipantState market_participant_state)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), mpid_(mpid), stock_(stock), primary_market_maker_(primary_market_maker), market_maker_mode_(market_maker_mode), market_participant_state_(market_participant_state) {}

std::uint16_t FilePayloadMarketParticipantPositionMessage::stock_locate() const { return stock_locate_; }
void FilePayloadMarketParticipantPositionMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadMarketParticipantPositionMessage::tracking_number() const { return tracking_number_; }
void FilePayloadMarketParticipantPositionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadMarketParticipantPositionMessage::timestamp() const { return timestamp_; }
void FilePayloadMarketParticipantPositionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadMarketParticipantPositionMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

const std::string& FilePayloadMarketParticipantPositionMessage::mpid() const { return mpid_; }
std::string& FilePayloadMarketParticipantPositionMessage::mpid() { return mpid_; }
void FilePayloadMarketParticipantPositionMessage::set_mpid(const std::string& value) { mpid_ = value; }

const std::string& FilePayloadMarketParticipantPositionMessage::stock() const { return stock_; }
std::string& FilePayloadMarketParticipantPositionMessage::stock() { return stock_; }
void FilePayloadMarketParticipantPositionMessage::set_stock(const std::string& value) { stock_ = value; }

PrimaryMarketMaker FilePayloadMarketParticipantPositionMessage::primary_market_maker() const { return primary_market_maker_; }
void FilePayloadMarketParticipantPositionMessage::set_primary_market_maker(PrimaryMarketMaker value) { primary_market_maker_ = value; }

MarketMakerMode FilePayloadMarketParticipantPositionMessage::market_maker_mode() const { return market_maker_mode_; }
void FilePayloadMarketParticipantPositionMessage::set_market_maker_mode(MarketMakerMode value) { market_maker_mode_ = value; }

MarketParticipantState FilePayloadMarketParticipantPositionMessage::market_participant_state() const { return market_participant_state_; }
void FilePayloadMarketParticipantPositionMessage::set_market_participant_state(MarketParticipantState value) { market_participant_state_ = value; }

FileMessageCode FilePayloadMarketParticipantPositionMessage::type() const { return message_type; }

std::string_view FilePayloadMarketParticipantPositionMessage::name() const { return "Market Participant Position Message"; }

std::size_t FilePayloadMarketParticipantPositionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadMarketParticipantPositionMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    mpid_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    primary_market_maker_ = static_cast<PrimaryMarketMaker>(wire::read_char(data + offset));
    offset += 1;

    market_maker_mode_ = static_cast<MarketMakerMode>(wire::read_char(data + offset));
    offset += 1;

    market_participant_state_ = static_cast<MarketParticipantState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FilePayloadMarketParticipantPositionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadMarketParticipantPositionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 4, ' ', mpid_);
    offset += 4;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(primary_market_maker_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(market_maker_mode_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(market_participant_state_));
    offset += 1;

    return offset;
}

std::size_t FilePayloadMarketParticipantPositionMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadMarketParticipantPositionMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadMarketParticipantPositionMessage::clone() const {
    return std::make_unique<FilePayloadMarketParticipantPositionMessage>(*this);
}

void FilePayloadMarketParticipantPositionMessage::print(std::ostream& out) const {
    out << "FilePayloadMarketParticipantPositionMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
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

bool FilePayloadMarketParticipantPositionMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadMarketParticipantPositionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadMarketParticipantPositionMessage::operator==(const FilePayloadMarketParticipantPositionMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && mpid_ == other.mpid_
        && stock_ == other.stock_
        && primary_market_maker_ == other.primary_market_maker_
        && market_maker_mode_ == other.market_maker_mode_
        && market_participant_state_ == other.market_participant_state_;
}

bool FilePayloadMarketParticipantPositionMessage::operator!=(const FilePayloadMarketParticipantPositionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
