#include "TickerMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

TickerMessage::TickerMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, std::uint8_t no_entries, const std::vector<TickerMdEntry>& ticker_md_entry)
  : class_key_(class_key), security_id_(security_id), price_type_(price_type), no_entries_(no_entries), ticker_md_entry_(ticker_md_entry) {}

std::uint32_t TickerMessage::class_key() const { return class_key_; }
void TickerMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t TickerMessage::security_id() const { return security_id_; }
void TickerMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

std::uint8_t TickerMessage::price_type() const { return price_type_; }
void TickerMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

std::uint8_t TickerMessage::no_entries() const { return no_entries_; }
void TickerMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<TickerMdEntry>& TickerMessage::ticker_md_entry() const { return ticker_md_entry_; }
std::vector<TickerMdEntry>& TickerMessage::ticker_md_entry() { return ticker_md_entry_; }
void TickerMessage::set_ticker_md_entry(const std::vector<TickerMdEntry>& value) { ticker_md_entry_ = value; }

MessageCode TickerMessage::type() const { return message_type; }

std::string_view TickerMessage::name() const { return "Ticker Message"; }

std::size_t TickerMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("TickerMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("TickerMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("TickerMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("TickerMessage", offset + 1, length);
    no_entries_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_entries_);
        ticker_md_entry_.clear();
        ticker_md_entry_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            TickerMdEntry entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            ticker_md_entry_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t TickerMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TickerMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_entries = no_entries_;
    no_entries = static_cast<std::uint8_t>(ticker_md_entry_.size());

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : ticker_md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t TickerMessage::encoded_size() const {
    return 4 + 4 + 1 + 1 + wire::encoded_size_of(ticker_md_entry_);
}

void TickerMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TickerMessage::clone() const {
    return std::make_unique<TickerMessage>(*this);
}

void TickerMessage::print(std::ostream& out) const {
    out << "TickerMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", ticker_md_entry=";
    print::sequence(out, ticker_md_entry_);
    out << '}';
}

bool TickerMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TickerMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TickerMessage::operator==(const TickerMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && price_type_ == other.price_type_
        && no_entries_ == other.no_entries_
        && ticker_md_entry_ == other.ticker_md_entry_;
}

bool TickerMessage::operator!=(const TickerMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
