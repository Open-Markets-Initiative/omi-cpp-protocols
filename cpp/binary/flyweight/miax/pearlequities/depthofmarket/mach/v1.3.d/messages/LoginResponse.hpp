// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginResponse.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../groups/LoginMatchingEngine.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The ESesM server sends a Login response packet in response to a Login request packet from
// the client
class LoginResponse {
  public:
    static constexpr const char* name = "LoginResponse";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginResponse(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginResponse has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return login_matching_engine_end(); }

    std::uint8_t number_of_matching_engines() const { return wire::read_u8(at(0)); }

    view::entries<LoginMatchingEngine> login_matching_engine() const { return view::entries<LoginMatchingEngine>{ bytes_.subspan(1), wire::count(number_of_matching_engines()) }; }

    void print(std::ostream& out) const {
        out << "LoginResponse{";
        out << "number_of_matching_engines=";
        out << static_cast<int>(number_of_matching_engines());
        out << ", login_matching_engine=";
        print::sequence(out, login_matching_engine());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t login_matching_engine_end() const { return 1 + login_matching_engine().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginResponse& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
