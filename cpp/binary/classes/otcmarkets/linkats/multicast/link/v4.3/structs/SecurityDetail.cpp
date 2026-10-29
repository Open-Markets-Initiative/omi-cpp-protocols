#include "SecurityDetail.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

SecurityDetail::SecurityDetail(std::uint8_t security_detail_size, const std::string& security_detail_name)
  : security_detail_size_(security_detail_size), security_detail_name_(security_detail_name) {}

std::uint8_t SecurityDetail::security_detail_size() const { return security_detail_size_; }
void SecurityDetail::set_security_detail_size(std::uint8_t value) { security_detail_size_ = value; }

const std::string& SecurityDetail::security_detail_name() const { return security_detail_name_; }
std::string& SecurityDetail::security_detail_name() { return security_detail_name_; }
void SecurityDetail::set_security_detail_name(const std::string& value) { security_detail_name_ = value; }

std::size_t SecurityDetail::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SecurityDetail", offset + 1, length);
    security_detail_size_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(security_detail_size_);
        wire::require("SecurityDetail", offset + count, length);
        security_detail_name_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t SecurityDetail::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDetail", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto security_detail_size = security_detail_size_;
    security_detail_size = static_cast<std::uint8_t>(security_detail_name_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_detail_size));
    offset += 1;

    wire::require_capacity("encode", offset + security_detail_name_.size(), capacity);
    wire::write_text(data + offset, security_detail_name_.size(), ' ', security_detail_name_);
    offset += security_detail_name_.size();

    return offset;
}

std::size_t SecurityDetail::encoded_size() const {
    return 1 + security_detail_name_.size();
}

void SecurityDetail::print(std::ostream& out) const {
    out << "SecurityDetail{";
    out << "security_detail_size=";
    out << static_cast<int>(security_detail_size_);
    out << ", security_detail_name=";
    print::text(out, security_detail_name_);
    out << '}';
}

bool SecurityDetail::operator==(const SecurityDetail& other) const {
    return security_detail_size_ == other.security_detail_size_
        && security_detail_name_ == other.security_detail_name_;
}

bool SecurityDetail::operator!=(const SecurityDetail& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityDetail& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
