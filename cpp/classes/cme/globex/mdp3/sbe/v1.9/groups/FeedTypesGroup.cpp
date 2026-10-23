#include "FeedTypesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

FeedTypesGroup::FeedTypesGroup(const std::string& md_feed_type, std::int8_t market_depth)
  : md_feed_type_(md_feed_type), market_depth_(market_depth) {}

const std::string& FeedTypesGroup::md_feed_type() const { return md_feed_type_; }
std::string& FeedTypesGroup::md_feed_type() { return md_feed_type_; }
void FeedTypesGroup::set_md_feed_type(const std::string& value) { md_feed_type_ = value; }

std::int8_t FeedTypesGroup::market_depth() const { return market_depth_; }
void FeedTypesGroup::set_market_depth(std::int8_t value) { market_depth_ = value; }

std::size_t FeedTypesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FeedTypesGroup", wire_size, length);

    md_feed_type_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    market_depth_ = wire::read_i8(data + offset);
    offset += 1;

    return offset;
}

std::size_t FeedTypesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FeedTypesGroup", wire_size, capacity);

    wire::write_text(data + offset, 3, '\0', md_feed_type_);
    offset += 3;

    wire::write_i8(data + offset, static_cast<std::int8_t>(market_depth_));
    offset += 1;

    return offset;
}

std::size_t FeedTypesGroup::encoded_size() const {
    return wire_size;
}

void FeedTypesGroup::print(std::ostream& out) const {
    out << "FeedTypesGroup{";
    out << "md_feed_type=";
    print::text(out, md_feed_type_);
    out << ", market_depth=";
    out << static_cast<int>(market_depth_);
    out << '}';
}

bool FeedTypesGroup::operator==(const FeedTypesGroup& other) const {
    return md_feed_type_ == other.md_feed_type_
        && market_depth_ == other.market_depth_;
}

bool FeedTypesGroup::operator!=(const FeedTypesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FeedTypesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
