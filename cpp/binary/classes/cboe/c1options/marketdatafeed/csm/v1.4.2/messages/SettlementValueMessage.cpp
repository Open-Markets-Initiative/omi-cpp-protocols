#include "SettlementValueMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SettlementValueMessage::SettlementValueMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, std::uint8_t no_entries, const std::vector<SettlementValueMdEntry>& settlement_value_md_entry)
  : class_key_(class_key), security_id_(security_id), price_type_(price_type), no_entries_(no_entries), settlement_value_md_entry_(settlement_value_md_entry) {}

std::uint32_t SettlementValueMessage::class_key() const { return class_key_; }
void SettlementValueMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t SettlementValueMessage::security_id() const { return security_id_; }
void SettlementValueMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

std::uint8_t SettlementValueMessage::price_type() const { return price_type_; }
void SettlementValueMessage::set_price_type(std::uint8_t value) { price_type_ = value; }

std::uint8_t SettlementValueMessage::no_entries() const { return no_entries_; }
void SettlementValueMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<SettlementValueMdEntry>& SettlementValueMessage::settlement_value_md_entry() const { return settlement_value_md_entry_; }
std::vector<SettlementValueMdEntry>& SettlementValueMessage::settlement_value_md_entry() { return settlement_value_md_entry_; }
void SettlementValueMessage::set_settlement_value_md_entry(const std::vector<SettlementValueMdEntry>& value) { settlement_value_md_entry_ = value; }

MessageCode SettlementValueMessage::type() const { return message_type; }

std::string_view SettlementValueMessage::name() const { return "Settlement Value Message"; }

std::size_t SettlementValueMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SettlementValueMessage", offset + 4, length);
    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SettlementValueMessage", offset + 4, length);
    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("SettlementValueMessage", offset + 1, length);
    price_type_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("SettlementValueMessage", offset + 1, length);
    no_entries_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_entries_);
        settlement_value_md_entry_.clear();
        settlement_value_md_entry_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SettlementValueMdEntry entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            settlement_value_md_entry_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SettlementValueMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SettlementValueMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_entries = no_entries_;
    no_entries = static_cast<std::uint8_t>(settlement_value_md_entry_.size());

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : settlement_value_md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SettlementValueMessage::encoded_size() const {
    return 4 + 4 + 1 + 1 + wire::encoded_size_of(settlement_value_md_entry_);
}

void SettlementValueMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SettlementValueMessage::clone() const {
    return std::make_unique<SettlementValueMessage>(*this);
}

void SettlementValueMessage::print(std::ostream& out) const {
    out << "SettlementValueMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", price_type=";
    out << static_cast<int>(price_type_);
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", settlement_value_md_entry=";
    print::sequence(out, settlement_value_md_entry_);
    out << '}';
}

bool SettlementValueMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SettlementValueMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SettlementValueMessage::operator==(const SettlementValueMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && price_type_ == other.price_type_
        && no_entries_ == other.no_entries_
        && settlement_value_md_entry_ == other.settlement_value_md_entry_;
}

bool SettlementValueMessage::operator!=(const SettlementValueMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
