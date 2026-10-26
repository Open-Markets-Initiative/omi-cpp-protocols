#include "OptionRelatedInstrumentsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

OptionRelatedInstrumentsGroups::OptionRelatedInstrumentsGroups(const GroupSize& group_size, const std::vector<OptionRelatedInstrumentsGroup>& option_related_instruments_group)
  : group_size_(group_size), option_related_instruments_group_(option_related_instruments_group) {}

const GroupSize& OptionRelatedInstrumentsGroups::group_size() const { return group_size_; }
GroupSize& OptionRelatedInstrumentsGroups::group_size() { return group_size_; }
void OptionRelatedInstrumentsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<OptionRelatedInstrumentsGroup>& OptionRelatedInstrumentsGroups::option_related_instruments_group() const { return option_related_instruments_group_; }
std::vector<OptionRelatedInstrumentsGroup>& OptionRelatedInstrumentsGroups::option_related_instruments_group() { return option_related_instruments_group_; }
void OptionRelatedInstrumentsGroups::set_option_related_instruments_group(const std::vector<OptionRelatedInstrumentsGroup>& value) { option_related_instruments_group_ = value; }

std::size_t OptionRelatedInstrumentsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        option_related_instruments_group_.clear();
        option_related_instruments_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            OptionRelatedInstrumentsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("OptionRelatedInstrumentsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            option_related_instruments_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t OptionRelatedInstrumentsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionRelatedInstrumentsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(option_related_instruments_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(OptionRelatedInstrumentsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : option_related_instruments_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t OptionRelatedInstrumentsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(option_related_instruments_group_);
}

void OptionRelatedInstrumentsGroups::print(std::ostream& out) const {
    out << "OptionRelatedInstrumentsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", option_related_instruments_group=";
    print::sequence(out, option_related_instruments_group_);
    out << '}';
}

bool OptionRelatedInstrumentsGroups::operator==(const OptionRelatedInstrumentsGroups& other) const {
    return group_size_ == other.group_size_
        && option_related_instruments_group_ == other.option_related_instruments_group_;
}

bool OptionRelatedInstrumentsGroups::operator!=(const OptionRelatedInstrumentsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OptionRelatedInstrumentsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
