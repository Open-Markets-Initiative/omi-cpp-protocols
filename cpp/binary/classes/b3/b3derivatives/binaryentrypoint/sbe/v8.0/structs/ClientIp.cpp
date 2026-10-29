#include "ClientIp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

ClientIp::ClientIp(std::uint8_t client_ip_length, const std::string& client_ip_data)
  : client_ip_length_(client_ip_length), client_ip_data_(client_ip_data) {}

std::uint8_t ClientIp::client_ip_length() const { return client_ip_length_; }
void ClientIp::set_client_ip_length(std::uint8_t value) { client_ip_length_ = value; }

const std::string& ClientIp::client_ip_data() const { return client_ip_data_; }
std::string& ClientIp::client_ip_data() { return client_ip_data_; }
void ClientIp::set_client_ip_data(const std::string& value) { client_ip_data_ = value; }

std::size_t ClientIp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ClientIp", offset + 1, length);
    client_ip_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(client_ip_length_);
        wire::require("ClientIp", offset + count, length);
        client_ip_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t ClientIp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientIp", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto client_ip_length = client_ip_length_;
    client_ip_length = static_cast<std::uint8_t>(client_ip_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(client_ip_length));
    offset += 1;

    wire::require_capacity("encode", offset + client_ip_data_.size(), capacity);
    wire::write_text(data + offset, client_ip_data_.size(), ' ', client_ip_data_);
    offset += client_ip_data_.size();

    return offset;
}

std::size_t ClientIp::encoded_size() const {
    return 1 + client_ip_data_.size();
}

void ClientIp::print(std::ostream& out) const {
    out << "ClientIp{";
    out << "client_ip_length=";
    out << static_cast<int>(client_ip_length_);
    out << ", client_ip_data=";
    print::text(out, client_ip_data_);
    out << '}';
}

bool ClientIp::operator==(const ClientIp& other) const {
    return client_ip_length_ == other.client_ip_length_
        && client_ip_data_ == other.client_ip_data_;
}

bool ClientIp::operator!=(const ClientIp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ClientIp& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
