#include "CurrentMarketUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

CurrentMarketUpdateMessage::CurrentMarketUpdateMessage(std::uint32_t class_key, std::uint32_t security_id, SecurityTradingStatus security_trading_status, std::uint8_t price_type, std::uint8_t no_entries, const std::vector<MdEntry>& md_entry)
  : class_key_(class_key), security_id_(security_id), security_trading_status_(security_trading_status), price_type_(price_type), no_entries_(no_entries), md_entry_(md_entry) {}

std::uint32_t CurrentMarketUpdateMessage::class_key() const { return class_key_; }
void CurrentMarketUpdateMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t CurrentMarketUpdateMessage::security_id() const { return security_id_; }
void CurrentMarketUpdateMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

SecurityTradingStatus CurrentMarketUpdateMessage::security_trading_status() const { return security_trading_status_; }
void CurrentMarketUpdateMessage::set_security_trading_status(SecurityTradingStatus value) { security_trading_status_ = value; }

std::uint8_t CurrentMarketUpdateMessage::price_type() const { return price_type_; }
void CurrentMarketUpdateMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

std::uint8_t CurrentMarketUpdateMessage::no_entries() const { return no_entries_; }
void CurrentMarketUpdateMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<MdEntry>& CurrentMarketUpdateMessage::md_entry() const { return md_entry_; }
std::vector<MdEntry>& CurrentMarketUpdateMessage::md_entry() { return md_entry_; }
void CurrentMarketUpdateMessage::set_md_entry(const std::vector<MdEntry>& value) { md_entry_ = value; }

MessageCode CurrentMarketUpdateMessage::type() const { return message_type; }

std::string_view CurrentMarketUpdateMessage::name() const { return "Current Market Update Message"; }

std::size_t CurrentMarketUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("CurrentMarketUpdateMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("CurrentMarketUpdateMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("CurrentMarketUpdateMessage", offset + 1, length);
    security_trading_status_ = static_cast<SecurityTradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("CurrentMarketUpdateMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("CurrentMarketUpdateMessage", offset + 1, length);
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

std::size_t CurrentMarketUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CurrentMarketUpdateMessage", encoded_size(), capacity);

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

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t CurrentMarketUpdateMessage::encoded_size() const {
    return 4 + 4 + 1 + 1 + 1 + wire::encoded_size_of(md_entry_);
}

void CurrentMarketUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CurrentMarketUpdateMessage::clone() const {
    return std::make_unique<CurrentMarketUpdateMessage>(*this);
}

void CurrentMarketUpdateMessage::print(std::ostream& out) const {
    out << "CurrentMarketUpdateMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", security_trading_status=";
    out << security_trading_status_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", md_entry=";
    print::sequence(out, md_entry_);
    out << '}';
}

bool CurrentMarketUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CurrentMarketUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CurrentMarketUpdateMessage::operator==(const CurrentMarketUpdateMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && security_trading_status_ == other.security_trading_status_
        && price_type_ == other.price_type_
        && no_entries_ == other.no_entries_
        && md_entry_ == other.md_entry_;
}

bool CurrentMarketUpdateMessage::operator!=(const CurrentMarketUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
