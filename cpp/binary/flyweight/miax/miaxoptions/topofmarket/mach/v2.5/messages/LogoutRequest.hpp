#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LogoutReason.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// The client may send a Logout request packet to request the connection be terminated
class LogoutRequest {
  public:
    static constexpr const char* name = "LogoutRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LogoutRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LogoutRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return logout_text_end(); }

    LogoutReason logout_reason() const { return static_cast<LogoutReason>(wire::read_char(at(0))); }

    std::size_t logout_text_size() const { return bytes_.size() - (1); }
    std::string_view logout_text() const {
        wire::require("LogoutRequest", 1 + logout_text_size(), bytes_.size());
        return view::characters(at(1), logout_text_size());
    }

    void print(std::ostream& out) const {
        out << "LogoutRequest{";
        out << "logout_reason=";
        out << logout_reason();
        out << ", logout_text=";
        print::text(out, logout_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t logout_text_end() const { return 1 + logout_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LogoutRequest& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
