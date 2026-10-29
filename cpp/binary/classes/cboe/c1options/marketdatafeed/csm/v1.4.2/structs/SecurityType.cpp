#include "SecurityType.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

SecurityType::SecurityType(std::uint8_t security_type_length, const std::string& security_type_text)
  : security_type_length_(security_type_length), security_type_text_(security_type_text) {}

std::uint8_t SecurityType::security_type_length() const { return security_type_length_; }
void SecurityType::set_security_type_length(std::uint8_t value) { security_type_length_ = value; }

const std::string& SecurityType::security_type_text() const { return security_type_text_; }
std::string& SecurityType::security_type_text() { return security_type_text_; }
void SecurityType::set_security_type_text(const std::string& value) { security_type_text_ = value; }

std::size_t SecurityType::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SecurityType", offset + 1, length);
    security_type_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(security_type_length_);
        wire::require("SecurityType", offset + count, length);
        security_type_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t SecurityType::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityType", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto security_type_length = security_type_length_;
    security_type_length = static_cast<std::uint8_t>(security_type_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_type_length));
    offset += 1;

    wire::require_capacity("encode", offset + security_type_text_.size(), capacity);
    wire::write_text(data + offset, security_type_text_.size(), ' ', security_type_text_);
    offset += security_type_text_.size();

    return offset;
}

std::size_t SecurityType::encoded_size() const {
    return 1 + security_type_text_.size();
}

void SecurityType::print(std::ostream& out) const {
    out << "SecurityType{";
    out << "security_type_length=";
    out << static_cast<int>(security_type_length_);
    out << ", security_type_text=";
    print::text(out, security_type_text_);
    out << '}';
}

bool SecurityType::operator==(const SecurityType& other) const {
    return security_type_length_ == other.security_type_length_
        && security_type_text_ == other.security_type_text_;
}

bool SecurityType::operator!=(const SecurityType& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityType& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
