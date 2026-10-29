#include "Issuer.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

Issuer::Issuer(std::uint8_t issuer_size, const std::string& issuer_name)
  : issuer_size_(issuer_size), issuer_name_(issuer_name) {}

std::uint8_t Issuer::issuer_size() const { return issuer_size_; }
void Issuer::set_issuer_size(std::uint8_t value) { issuer_size_ = value; }

const std::string& Issuer::issuer_name() const { return issuer_name_; }
std::string& Issuer::issuer_name() { return issuer_name_; }
void Issuer::set_issuer_name(const std::string& value) { issuer_name_ = value; }

std::size_t Issuer::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Issuer", offset + 1, length);
    issuer_size_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(issuer_size_);
        wire::require("Issuer", offset + count, length);
        issuer_name_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t Issuer::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Issuer", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto issuer_size = issuer_size_;
    issuer_size = static_cast<std::uint8_t>(issuer_name_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(issuer_size));
    offset += 1;

    wire::require_capacity("encode", offset + issuer_name_.size(), capacity);
    wire::write_text(data + offset, issuer_name_.size(), ' ', issuer_name_);
    offset += issuer_name_.size();

    return offset;
}

std::size_t Issuer::encoded_size() const {
    return 1 + issuer_name_.size();
}

void Issuer::print(std::ostream& out) const {
    out << "Issuer{";
    out << "issuer_size=";
    out << static_cast<int>(issuer_size_);
    out << ", issuer_name=";
    print::text(out, issuer_name_);
    out << '}';
}

bool Issuer::operator==(const Issuer& other) const {
    return issuer_size_ == other.issuer_size_
        && issuer_name_ == other.issuer_name_;
}

bool Issuer::operator!=(const Issuer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Issuer& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
