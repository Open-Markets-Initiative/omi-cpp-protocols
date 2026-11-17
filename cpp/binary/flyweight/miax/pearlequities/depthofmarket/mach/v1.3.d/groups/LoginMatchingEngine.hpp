// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: groups/LoginMatchingEngine.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LoginStatus.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The login status, trading session and highest sequence number of one matching engine,
// repeated once for each the login response counts
class LoginMatchingEngine {
  public:
    static constexpr const char* name = "LoginMatchingEngine";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginMatchingEngine(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginMatchingEngine has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    LoginStatus login_status() const { return static_cast<LoginStatus>(wire::read_char(at(0))); }

    std::uint8_t trading_session_id() const { return wire::read_u8(at(1)); }

    std::uint64_t highest_sequence_number() const { return wire::read_u64_le(at(2)); }

    void print(std::ostream& out) const {
        out << "LoginMatchingEngine{";
        out << "login_status=";
        out << login_status();
        out << ", trading_session_id=";
        out << static_cast<int>(trading_session_id());
        out << ", highest_sequence_number=";
        out << highest_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginMatchingEngine& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
