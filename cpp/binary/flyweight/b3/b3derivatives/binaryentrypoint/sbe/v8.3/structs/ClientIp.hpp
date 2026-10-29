#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// clientIP data struct
class ClientIp {
  public:
    static constexpr const char* name = "ClientIp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ClientIp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ClientIp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return client_ip_data_end(); }

    std::uint8_t client_ip_length() const { return wire::read_u8(at(0)); }

    std::size_t client_ip_data_size() const { return wire::count(client_ip_length()); }
    std::string_view client_ip_data() const {
        wire::require("ClientIp", 1 + client_ip_data_size(), bytes_.size());
        return view::characters(at(1), client_ip_data_size());
    }

    void print(std::ostream& out) const {
        out << "ClientIp{";
        out << "client_ip_length=";
        out << static_cast<int>(client_ip_length());
        out << ", client_ip_data=";
        print::text(out, client_ip_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t client_ip_data_end() const { return 1 + client_ip_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ClientIp& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
