#include "Credentials.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

Credentials::Credentials(std::uint8_t credentials_length, const std::string& credentials_data)
  : credentials_length_(credentials_length), credentials_data_(credentials_data) {}

std::uint8_t Credentials::credentials_length() const { return credentials_length_; }
void Credentials::set_credentials_length(std::uint8_t value) { credentials_length_ = value; }

const std::string& Credentials::credentials_data() const { return credentials_data_; }
std::string& Credentials::credentials_data() { return credentials_data_; }
void Credentials::set_credentials_data(const std::string& value) { credentials_data_ = value; }

std::size_t Credentials::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Credentials", offset + 1, length);
    credentials_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(credentials_length_);
        wire::require("Credentials", offset + count, length);
        credentials_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t Credentials::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Credentials", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto credentials_length = credentials_length_;
    credentials_length = static_cast<std::uint8_t>(credentials_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(credentials_length));
    offset += 1;

    wire::require_capacity("encode", offset + credentials_data_.size(), capacity);
    wire::write_text(data + offset, credentials_data_.size(), ' ', credentials_data_);
    offset += credentials_data_.size();

    return offset;
}

std::size_t Credentials::encoded_size() const {
    return 1 + credentials_data_.size();
}

void Credentials::print(std::ostream& out) const {
    out << "Credentials{";
    out << "credentials_length=";
    out << static_cast<int>(credentials_length_);
    out << ", credentials_data=";
    print::text(out, credentials_data_);
    out << '}';
}

bool Credentials::operator==(const Credentials& other) const {
    return credentials_length_ == other.credentials_length_
        && credentials_data_ == other.credentials_data_;
}

bool Credentials::operator!=(const Credentials& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Credentials& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
