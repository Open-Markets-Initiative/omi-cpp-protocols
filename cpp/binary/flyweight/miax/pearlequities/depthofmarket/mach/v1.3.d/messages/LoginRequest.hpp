// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginRequest.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../groups/RequestedMatchingEngine.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The ESesM client must send a Login request packet immediately upon establishing a new TCP/IP
// socket connection to the server
class LoginRequest {
  public:
    static constexpr const char* name = "LoginRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 27;
    std::size_t encoded_size() const { return requested_matching_engine_end(); }

    std::string_view esesm_version() const { return view::text(at(0), 5, ' '); }

    std::string_view username() const { return view::text(at(5), 5, ' '); }

    std::string_view computer_id() const { return view::text(at(10), 8, ' '); }

    std::string_view application_protocol() const { return view::text(at(18), 8, ' '); }

    std::uint8_t number_of_matching_engines() const { return wire::read_u8(at(26)); }

    view::entries<RequestedMatchingEngine> requested_matching_engine() const { return view::entries<RequestedMatchingEngine>{ bytes_.subspan(27), wire::count(number_of_matching_engines()) }; }

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
        out << ", number_of_matching_engines=";
        out << static_cast<int>(number_of_matching_engines());
        out << ", requested_matching_engine=";
        print::sequence(out, requested_matching_engine());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t requested_matching_engine_end() const { return 27 + requested_matching_engine().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginRequest& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
