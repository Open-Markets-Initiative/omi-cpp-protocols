#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The SesM client must send a Login request packet immediately upon establishing a new TCP/IP
// socket connection to the server
class LoginRequest {
  public:
    static constexpr const char* name = "LoginRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 35;
    static constexpr std::size_t fixed_size = 35;
    std::size_t encoded_size() const { return 35; }

    std::string_view esesm_version() const { return view::text(at(0), 5, ' '); }

    std::string_view username() const { return view::text(at(5), 5, ' '); }

    std::string_view computer_id() const { return view::text(at(10), 8, ' '); }

    std::string_view application_protocol() const { return view::text(at(18), 8, ' '); }

    std::uint8_t requested_trading_session_id() const { return wire::read_u8(at(26)); }

    std::uint64_t requested_sequence_number() const { return wire::read_u64_le(at(27)); }

    void print(std::ostream& out) const {
        out << "LoginRequest{";
        out << "esesm_version=";
        print::text(out, esesm_version());
        out << ", username=";
        print::text(out, username());
        out << ", computer_id=";
        print::text(out, computer_id());
        out << ", application_protocol=";
        print::text(out, application_protocol());
        out << ", requested_trading_session_id=";
        out << static_cast<int>(requested_trading_session_id());
        out << ", requested_sequence_number=";
        out << requested_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginRequest& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
