#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/Credentials.hpp"
#include "../structs/ClientIp.hpp"
#include "../structs/ClientAppName.hpp"
#include "../structs/ClientAppVersion.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// NegotiateMessage
class NegotiateMessage {
  public:
    static constexpr const char* name = "NegotiateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NegotiateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NegotiateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    std::size_t encoded_size() const { return client_app_version_end(); }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint64_t session_ver_id() const { return wire::read_u64_le(at(4)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(12)))); }

    std::uint32_t entering_firm() const { return wire::read_u32_le(at(20)); }

    std::optional<std::uint32_t> onbehalf_firm() const { return wire::nullable(wire::read_u32_le(at(24)), static_cast<std::uint32_t>(0ULL)); }

    Credentials credentials() const { return Credentials{ bytes_.subspan(28) }; }

    ClientIp client_ip() const {
        wire::require("NegotiateMessage", credentials_end() + ClientIp::minimum_size, bytes_.size());
        return ClientIp{ bytes_.subspan(credentials_end()) };
    }

    ClientAppName client_app_name() const {
        wire::require("NegotiateMessage", client_ip_end() + ClientAppName::minimum_size, bytes_.size());
        return ClientAppName{ bytes_.subspan(client_ip_end()) };
    }

    ClientAppVersion client_app_version() const {
        wire::require("NegotiateMessage", client_app_name_end() + ClientAppVersion::minimum_size, bytes_.size());
        return ClientAppVersion{ bytes_.subspan(client_app_name_end()) };
    }

    void print(std::ostream& out) const {
        out << "NegotiateMessage{";
        out << "session_id=";
        out << session_id();
        out << ", session_ver_id=";
        out << session_ver_id();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", entering_firm=";
        out << entering_firm();
        out << ", onbehalf_firm=";
        print::optional(out, onbehalf_firm());
        out << ", credentials=";
        credentials().print(out);
        out << ", client_ip=";
        client_ip().print(out);
        out << ", client_app_name=";
        client_app_name().print(out);
        out << ", client_app_version=";
        client_app_version().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t credentials_end() const { return 28 + credentials().encoded_size(); }
    std::size_t client_ip_end() const { return credentials_end() + client_ip().encoded_size(); }
    std::size_t client_app_name_end() const { return client_ip_end() + client_app_name().encoded_size(); }
    std::size_t client_app_version_end() const { return client_app_name_end() + client_app_version().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NegotiateMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
