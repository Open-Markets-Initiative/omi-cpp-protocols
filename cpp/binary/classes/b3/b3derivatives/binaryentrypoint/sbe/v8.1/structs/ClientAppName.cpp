#include "ClientAppName.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

ClientAppName::ClientAppName(std::uint8_t client_app_name_length, const std::string& client_app_name_data)
  : client_app_name_length_(client_app_name_length), client_app_name_data_(client_app_name_data) {}

std::uint8_t ClientAppName::client_app_name_length() const { return client_app_name_length_; }
void ClientAppName::set_client_app_name_length(std::uint8_t value) { client_app_name_length_ = value; }

const std::string& ClientAppName::client_app_name_data() const { return client_app_name_data_; }
std::string& ClientAppName::client_app_name_data() { return client_app_name_data_; }
void ClientAppName::set_client_app_name_data(const std::string& value) { client_app_name_data_ = value; }

std::size_t ClientAppName::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ClientAppName", offset + 1, length);
    client_app_name_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(client_app_name_length_);
        wire::require("ClientAppName", offset + count, length);
        client_app_name_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t ClientAppName::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientAppName", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto client_app_name_length = client_app_name_length_;
    client_app_name_length = static_cast<std::uint8_t>(client_app_name_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(client_app_name_length));
    offset += 1;

    wire::require_capacity("encode", offset + client_app_name_data_.size(), capacity);
    wire::write_text(data + offset, client_app_name_data_.size(), ' ', client_app_name_data_);
    offset += client_app_name_data_.size();

    return offset;
}

std::size_t ClientAppName::encoded_size() const {
    return 1 + client_app_name_data_.size();
}

void ClientAppName::print(std::ostream& out) const {
    out << "ClientAppName{";
    out << "client_app_name_length=";
    out << static_cast<int>(client_app_name_length_);
    out << ", client_app_name_data=";
    print::text(out, client_app_name_data_);
    out << '}';
}

bool ClientAppName::operator==(const ClientAppName& other) const {
    return client_app_name_length_ == other.client_app_name_length_
        && client_app_name_data_ == other.client_app_name_data_;
}

bool ClientAppName::operator!=(const ClientAppName& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ClientAppName& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
