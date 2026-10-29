#include "TargetLocationId.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

TargetLocationId::TargetLocationId(std::uint8_t target_location_id_length, const std::string& target_location_id_text)
  : target_location_id_length_(target_location_id_length), target_location_id_text_(target_location_id_text) {}

std::uint8_t TargetLocationId::target_location_id_length() const { return target_location_id_length_; }
void TargetLocationId::set_target_location_id_length(std::uint8_t value) { target_location_id_length_ = value; }

const std::string& TargetLocationId::target_location_id_text() const { return target_location_id_text_; }
std::string& TargetLocationId::target_location_id_text() { return target_location_id_text_; }
void TargetLocationId::set_target_location_id_text(const std::string& value) { target_location_id_text_ = value; }

std::size_t TargetLocationId::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("TargetLocationId", offset + 1, length);
    target_location_id_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(target_location_id_length_);
        wire::require("TargetLocationId", offset + count, length);
        target_location_id_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t TargetLocationId::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TargetLocationId", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto target_location_id_length = target_location_id_length_;
    target_location_id_length = static_cast<std::uint8_t>(target_location_id_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(target_location_id_length));
    offset += 1;

    wire::require_capacity("encode", offset + target_location_id_text_.size(), capacity);
    wire::write_text(data + offset, target_location_id_text_.size(), ' ', target_location_id_text_);
    offset += target_location_id_text_.size();

    return offset;
}

std::size_t TargetLocationId::encoded_size() const {
    return 1 + target_location_id_text_.size();
}

void TargetLocationId::print(std::ostream& out) const {
    out << "TargetLocationId{";
    out << "target_location_id_length=";
    out << static_cast<int>(target_location_id_length_);
    out << ", target_location_id_text=";
    print::text(out, target_location_id_text_);
    out << '}';
}

bool TargetLocationId::operator==(const TargetLocationId& other) const {
    return target_location_id_length_ == other.target_location_id_length_
        && target_location_id_text_ == other.target_location_id_text_;
}

bool TargetLocationId::operator!=(const TargetLocationId& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TargetLocationId& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
