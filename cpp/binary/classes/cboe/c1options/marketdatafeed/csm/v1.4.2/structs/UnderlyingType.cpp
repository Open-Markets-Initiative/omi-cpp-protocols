#include "UnderlyingType.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

UnderlyingType::UnderlyingType(std::uint8_t underlying_type_length, const std::string& underlying_type_text)
  : underlying_type_length_(underlying_type_length), underlying_type_text_(underlying_type_text) {}

std::uint8_t UnderlyingType::underlying_type_length() const { return underlying_type_length_; }
void UnderlyingType::set_underlying_type_length(std::uint8_t value) { underlying_type_length_ = value; }

const std::string& UnderlyingType::underlying_type_text() const { return underlying_type_text_; }
std::string& UnderlyingType::underlying_type_text() { return underlying_type_text_; }
void UnderlyingType::set_underlying_type_text(const std::string& value) { underlying_type_text_ = value; }

std::size_t UnderlyingType::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("UnderlyingType", offset + 1, length);
    underlying_type_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(underlying_type_length_);
        wire::require("UnderlyingType", offset + count, length);
        underlying_type_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t UnderlyingType::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingType", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto underlying_type_length = underlying_type_length_;
    underlying_type_length = static_cast<std::uint8_t>(underlying_type_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(underlying_type_length));
    offset += 1;

    wire::require_capacity("encode", offset + underlying_type_text_.size(), capacity);
    wire::write_text(data + offset, underlying_type_text_.size(), ' ', underlying_type_text_);
    offset += underlying_type_text_.size();

    return offset;
}

std::size_t UnderlyingType::encoded_size() const {
    return 1 + underlying_type_text_.size();
}

void UnderlyingType::print(std::ostream& out) const {
    out << "UnderlyingType{";
    out << "underlying_type_length=";
    out << static_cast<int>(underlying_type_length_);
    out << ", underlying_type_text=";
    print::text(out, underlying_type_text_);
    out << '}';
}

bool UnderlyingType::operator==(const UnderlyingType& other) const {
    return underlying_type_length_ == other.underlying_type_length_
        && underlying_type_text_ == other.underlying_type_text_;
}

bool UnderlyingType::operator!=(const UnderlyingType& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UnderlyingType& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
