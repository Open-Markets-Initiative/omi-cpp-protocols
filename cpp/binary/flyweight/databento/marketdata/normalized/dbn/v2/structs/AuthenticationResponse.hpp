#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// The gateway sends this response following the client's authentication request (success, and
// error or session_id)
class AuthenticationResponse {
  public:
    static constexpr const char* name = "AuthenticationResponse";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuthenticationResponse(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuthenticationResponse has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    std::size_t encoded_size() const { return control_fields_end(); }

    // the characters before its terminator, which the bytes must hold
    std::size_t control_fields_size() const {
        wire::require("AuthenticationResponse", 0, bytes_.size());
        return wire::terminated_length(at(0), bytes_.size() - (0), 0);
    }
    std::string_view control_fields() const { return view::characters(at(0), control_fields_size()); }

    void print(std::ostream& out) const {
        out << "AuthenticationResponse{";
        out << "control_fields=";
        print::text(out, control_fields());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t control_fields_end() const { return 0 + (control_fields_size() + 1); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuthenticationResponse& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
