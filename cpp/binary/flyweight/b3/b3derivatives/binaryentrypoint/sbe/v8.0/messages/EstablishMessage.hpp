#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/CancelOnDisconnectType.hpp"
#include "../structs/Credentials.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// EstablishMessage
class EstablishMessage {
  public:
    static constexpr const char* name = "EstablishMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EstablishMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EstablishMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    std::size_t encoded_size() const { return credentials_end(); }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint64_t session_ver_id() const { return wire::read_u64_le(at(4)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(12)))); }

    std::uint64_t keep_alive_interval() const { return wire::read_u64_le(at(20)); }

    std::uint32_t next_seq_no() const { return wire::read_u32_le(at(28)); }

    CancelOnDisconnectType cancel_on_disconnect_type() const { return static_cast<CancelOnDisconnectType>(wire::read_u8(at(32))); }

    std::span<const std::byte, 1> offset_33_padding_1() const { return bytes_.subspan(33).template first<1>(); }

    std::uint64_t cod_timeout_window() const { return wire::read_u64_le(at(34)); }

    Credentials credentials() const { return Credentials{ bytes_.subspan(42) }; }

    void print(std::ostream& out) const {
        out << "EstablishMessage{";
        out << "session_id=";
        out << session_id();
        out << ", session_ver_id=";
        out << session_ver_id();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", keep_alive_interval=";
        out << keep_alive_interval();
        out << ", next_seq_no=";
        out << next_seq_no();
        out << ", cancel_on_disconnect_type=";
        out << cancel_on_disconnect_type();
        out << ", offset_33_padding_1=";
        print::hex(out, offset_33_padding_1().data(), offset_33_padding_1().size());
        out << ", cod_timeout_window=";
        out << cod_timeout_window();
        out << ", credentials=";
        credentials().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t credentials_end() const { return 42 + credentials().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EstablishMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
