#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// AdminLogin
class ServerPayloadAdminLogin {
  public:
    static constexpr const char* name = "ServerPayloadAdminLogin";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadAdminLogin(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadAdminLogin has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::int8_t heart_bt_int() const { return wire::read_i8(at(0)); }

    void print(std::ostream& out) const {
        out << "ServerPayloadAdminLogin{";
        out << "heart_bt_int=";
        out << static_cast<int>(heart_bt_int());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadAdminLogin& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
