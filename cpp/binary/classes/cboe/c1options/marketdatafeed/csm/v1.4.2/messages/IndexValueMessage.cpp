#include "IndexValueMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

IndexValueMessage::IndexValueMessage(const Symbol& symbol, std::uint8_t no_entries, const std::vector<IndexValueMdEntry>& index_value_md_entry)
  : symbol_(symbol), no_entries_(no_entries), index_value_md_entry_(index_value_md_entry) {}

const Symbol& IndexValueMessage::symbol() const { return symbol_; }
Symbol& IndexValueMessage::symbol() { return symbol_; }
void IndexValueMessage::set_symbol(const Symbol& value) { symbol_ = value; }

std::uint8_t IndexValueMessage::no_entries() const { return no_entries_; }
void IndexValueMessage::set_no_entries(std::uint8_t value) { no_entries_ = value; }

const std::vector<IndexValueMdEntry>& IndexValueMessage::index_value_md_entry() const { return index_value_md_entry_; }
std::vector<IndexValueMdEntry>& IndexValueMessage::index_value_md_entry() { return index_value_md_entry_; }
void IndexValueMessage::set_index_value_md_entry(const std::vector<IndexValueMdEntry>& value) { index_value_md_entry_ = value; }

MessageCode IndexValueMessage::type() const { return message_type; }

std::string_view IndexValueMessage::name() const { return "Index Value Message"; }

std::size_t IndexValueMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += symbol_.decode(data + offset, length - offset);

    wire::require("IndexValueMessage", offset + 1, length);
    no_entries_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(no_entries_);
        index_value_md_entry_.clear();
        index_value_md_entry_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IndexValueMdEntry entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            index_value_md_entry_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IndexValueMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IndexValueMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_entries = no_entries_;
    no_entries = static_cast<std::uint8_t>(index_value_md_entry_.size());

    offset += symbol_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_entries));
    offset += 1;

    for (const auto& entry : index_value_md_entry_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IndexValueMessage::encoded_size() const {
    return symbol_.encoded_size() + 1 + wire::encoded_size_of(index_value_md_entry_);
}

void IndexValueMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> IndexValueMessage::clone() const {
    return std::make_unique<IndexValueMessage>(*this);
}

void IndexValueMessage::print(std::ostream& out) const {
    out << "IndexValueMessage{";
    out << "symbol=";
    symbol_.print(out);
    out << ", no_entries=";
    out << static_cast<int>(no_entries_);
    out << ", index_value_md_entry=";
    print::sequence(out, index_value_md_entry_);
    out << '}';
}

bool IndexValueMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const IndexValueMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool IndexValueMessage::operator==(const IndexValueMessage& other) const {
    return symbol_ == other.symbol_
        && no_entries_ == other.no_entries_
        && index_value_md_entry_ == other.index_value_md_entry_;
}

bool IndexValueMessage::operator!=(const IndexValueMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
