#include "SecurityDesc.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

SecurityDesc::SecurityDesc(std::uint8_t security_desc_length, const std::string& security_desc_data)
  : security_desc_length_(security_desc_length), security_desc_data_(security_desc_data) {}

std::uint8_t SecurityDesc::security_desc_length() const { return security_desc_length_; }
void SecurityDesc::set_security_desc_length(std::uint8_t value) { security_desc_length_ = value; }

const std::string& SecurityDesc::security_desc_data() const { return security_desc_data_; }
std::string& SecurityDesc::security_desc_data() { return security_desc_data_; }
void SecurityDesc::set_security_desc_data(const std::string& value) { security_desc_data_ = value; }

std::size_t SecurityDesc::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SecurityDesc", offset + 1, length);
    security_desc_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = static_cast<std::size_t>(security_desc_length_);
        wire::require("SecurityDesc", offset + count, length);
        security_desc_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t SecurityDesc::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDesc", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto security_desc_length = security_desc_length_;
    security_desc_length = static_cast<std::uint8_t>(security_desc_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_desc_length));
    offset += 1;

    wire::require_capacity("encode", offset + security_desc_data_.size(), capacity);
    wire::write_text(data + offset, security_desc_data_.size(), ' ', security_desc_data_);
    offset += security_desc_data_.size();

    return offset;
}

std::size_t SecurityDesc::encoded_size() const {
    return 1 + security_desc_data_.size();
}

void SecurityDesc::print(std::ostream& out) const {
    out << "SecurityDesc{";
    out << "security_desc_length=";
    out << static_cast<int>(security_desc_length_);
    out << ", security_desc_data=";
    print::text(out, security_desc_data_);
    out << '}';
}

bool SecurityDesc::operator==(const SecurityDesc& other) const {
    return security_desc_length_ == other.security_desc_length_
        && security_desc_data_ == other.security_desc_data_;
}

bool SecurityDesc::operator!=(const SecurityDesc& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityDesc& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
