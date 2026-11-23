// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/HeartbeatBody.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>

#include "../groups/AdminBody.hpp"
#include "../structs/BodyHeader.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Packet;

// Heartbeat Body
class HeartbeatBody {
  public:

    HeartbeatBody() = default;
    HeartbeatBody(const BodyHeader& body_header, std::uint8_t admin_id, std::uint16_t hb_interval, const std::vector<AdminBody>& admin_body);

    // Body Header: Xmt Body Header
    const BodyHeader& body_header() const;
    BodyHeader& body_header();
    void set_body_header(const BodyHeader& value);

    // Admin Id: Admin ID for short window (1 to 255). Note: 0 is not allowed as a value.
    std::uint8_t admin_id() const;
    void set_admin_id(std::uint8_t value);

    // Hb Interval: Heartbeat interval in milliseconds (1 to 65536).
    std::uint16_t hb_interval() const;
    void set_hb_interval(std::uint16_t value);

    // Admin Body:
    const std::vector<AdminBody>& admin_body() const;
    std::vector<AdminBody>& admin_body();
    void set_admin_body(const std::vector<AdminBody>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const HeartbeatBody& other) const;
    bool operator!=(const HeartbeatBody& other) const;

    // The Packet holding this, which decode reads the fields outside it through
    void set_parent(const Packet* parent) { parent_ = parent; }

  private:
    const Packet* parent_ = nullptr;
    BodyHeader body_header_{};
    std::uint8_t admin_id_{};
    std::uint16_t hb_interval_{};
    std::vector<AdminBody> admin_body_{};
};

std::ostream& operator<<(std::ostream& out, const HeartbeatBody& value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
