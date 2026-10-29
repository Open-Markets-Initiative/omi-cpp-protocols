#include "ClientAppVersion.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

ClientAppVersion::ClientAppVersion(std::uint8_t client_app_version_length, const std::string& client_app_version_data)
  : client_app_version_length_(client_app_version_length), client_app_version_data_(client_app_version_data) {}

std::uint8_t ClientAppVersion::client_app_version_length() const { return client_app_version_length_; }
void ClientAppVersion::set_client_app_version_length(std::uint8_t value) { client_app_version_length_ = value; }

const std::string& ClientAppVersion::client_app_version_data() const { return client_app_version_data_; }
std::string& ClientAppVersion::client_app_version_data() { return client_app_version_data_; }
void ClientAppVersion::set_client_app_version_data(const std::string& value) { client_app_version_data_ = value; }

std::size_t ClientAppVersion::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ClientAppVersion", offset + 1, length);
    client_app_version_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(client_app_version_length_);
        wire::require("ClientAppVersion", offset + count, length);
        client_app_version_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t ClientAppVersion::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientAppVersion", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto client_app_version_length = client_app_version_length_;
    client_app_version_length = static_cast<std::uint8_t>(client_app_version_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(client_app_version_length));
    offset += 1;

    wire::require_capacity("encode", offset + client_app_version_data_.size(), capacity);
    wire::write_text(data + offset, client_app_version_data_.size(), ' ', client_app_version_data_);
    offset += client_app_version_data_.size();

    return offset;
}

std::size_t ClientAppVersion::encoded_size() const {
    return 1 + client_app_version_data_.size();
}

void ClientAppVersion::print(std::ostream& out) const {
    out << "ClientAppVersion{";
    out << "client_app_version_length=";
    out << static_cast<int>(client_app_version_length_);
    out << ", client_app_version_data=";
    print::text(out, client_app_version_data_);
    out << '}';
}

bool ClientAppVersion::operator==(const ClientAppVersion& other) const {
    return client_app_version_length_ == other.client_app_version_length_
        && client_app_version_data_ == other.client_app_version_data_;
}

bool ClientAppVersion::operator!=(const ClientAppVersion& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ClientAppVersion& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
