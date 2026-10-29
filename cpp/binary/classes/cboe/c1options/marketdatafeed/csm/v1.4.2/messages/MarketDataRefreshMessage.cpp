#include "MarketDataRefreshMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MarketDataRefreshMessage::MarketDataRefreshMessage(std::uint32_t class_key, std::uint32_t security_id, SecurityTradingStatus security_trading_status, std::uint8_t price_type, std::uint32_t appl_seq_num, const PrevClosePx& prev_close_px, std::uint32_t trade_volume, std::uint8_t no_entries, const std::vector<MdEntry>& md_entry)
  : class_key_(class_key), security_id_(security_id), security_trading_status_(security_trading_status), price_type_(price_type), appl_seq_num_(appl_seq_num), prev_close_px_(prev_close_px), trade_volume_(trade_volume), no_entries_(no_entries), md_entry_(md_entry) {}

std::uint32_t MarketDataRefreshMessage::class_key() const { return class_key_; }
void MarketDataRefreshMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t MarketDataRefreshMessage::security_id() const { return security_id_; }
void MarketDataRefreshMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

SecurityTradingStatus MarketDataRefreshMessage::security_trading_status() const { return security_trading_status_; }
void MarketDataRefreshMessage::set_security_trading_status(SecurityTradingStatus value) { security_trading_status_ = value; }

std::uint8_t MarketDataRefreshMessage::price_type() const { return price_type_; }
void MarketDataRefreshMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

std::uint32_t MarketDataRefreshMessage::appl_seq_num() const { return appl_seq_num_; }
void MarketDataRefreshMessage::set_appl_seq_num(std::uint32_t value) { appl_seq_num_ = value; }

const PrevClosePx& MarketDataRefreshMessage::prev_close_px() const { return prev_close_px_; }
PrevClosePx& MarketDataRefreshMessage::prev_close_px() { return prev_close_px_; }
void MarketDataRefreshMessage::set_prev_close_px(const PrevClosePx& value) { prev_close_px_ = value; }

std::uint32_t MarketDataRefreshMessage::trade_volume() const { return trade_volume_; }
void MarketDataRefreshMessage::set_trade_volume(std::uint32_t value) { trade_volume_ = value; }

std::uint8_t MarketDataRefreshMessage::no_entries() const { return no_entries_; }
void MarketDataRefreshMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<MdEntry>& MarketDataRefreshMessage::md_entry() const { return md_entry_; }
std::vector<MdEntry>& MarketDataRefreshMessage::md_entry() { return md_entry_; }
void MarketDataRefreshMessage::set_md_entry(const std::vector<MdEntry>& value) { md_entry_ = value; }

MessageCode MarketDataRefreshMessage::type() const { return message_type; }

std::string_view MarketDataRefreshMessage::name() const { return "Market Data Refresh Message"; }

std::size_t MarketDataRefreshMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("MarketDataRefreshMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("MarketDataRefreshMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("MarketDataRefreshMessage", offset + 1, length);
    security_trading_status_ = static_cast<SecurityTradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("MarketDataRefreshMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("MarketDataRefreshMessage", offset + 4, length);
    appl_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += prev_close_px_.decode(data + offset, length - offset);

    wire::require("MarketDataRefreshMessage", offset + 4, length);
    trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("MarketDataRefreshMessage", offset + 1, length);
    no_entries_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_entries_);
        md_entry_.clear();
        md_entry_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            MdEntry entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            md_entry_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t MarketDataRefreshMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketDataRefreshMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_entries = no_entries_;
    no_entries = static_cast<std::uint8_t>(md_entry_.size());

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(appl_seq_num_));
    offset += 4;

    offset += prev_close_px_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t MarketDataRefreshMessage::encoded_size() const {
    return 4 + 4 + 1 + 1 + 4 + prev_close_px_.encoded_size() + 4 + 1 + wire::encoded_size_of(md_entry_);
}

void MarketDataRefreshMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketDataRefreshMessage::clone() const {
    return std::make_unique<MarketDataRefreshMessage>(*this);
}

void MarketDataRefreshMessage::print(std::ostream& out) const {
    out << "MarketDataRefreshMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", security_trading_status=";
    out << security_trading_status_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", appl_seq_num=";
    out << appl_seq_num_;
    out << ", prev_close_px=";
    prev_close_px_.print(out);
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", md_entry=";
    print::sequence(out, md_entry_);
    out << '}';
}

bool MarketDataRefreshMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketDataRefreshMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketDataRefreshMessage::operator==(const MarketDataRefreshMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && security_trading_status_ == other.security_trading_status_
        && price_type_ == other.price_type_
        && appl_seq_num_ == other.appl_seq_num_
        && prev_close_px_ == other.prev_close_px_
        && trade_volume_ == other.trade_volume_
        && no_entries_ == other.no_entries_
        && md_entry_ == other.md_entry_;
}

bool MarketDataRefreshMessage::operator!=(const MarketDataRefreshMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
