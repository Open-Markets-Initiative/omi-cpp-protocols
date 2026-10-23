#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// AdminLogout
class ServerPayloadAdminLogout {
  public:
    static constexpr const char* name = "ServerPayloadAdminLogout";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadAdminLogout(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadAdminLogout has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 180;
    static constexpr std::size_t fixed_size = 180;
    std::size_t encoded_size() const { return 180; }

    std::string_view logout_text() const { return view::text(at(0), 180, '\0'); }

    void print(std::ostream& out) const {
        out << "ServerPayloadAdminLogout{";
        out << "logout_text=";
        print::text(out, logout_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadAdminLogout& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
