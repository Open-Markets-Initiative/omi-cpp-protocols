// OtcMarkets.LinkAts.Multicast.Link.v4.3 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/otcmarkets/linkats/multicast/link/v4.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/tmp/otcmarkets/linkats/multicast/link/v4.3/otcmarkets_linkats_multicast_link_v4_3.hpp"

// OtcMarkets LinkAts Multicast Link 4.3: the reading of its packets, through its Template Meta Programming header
namespace otcmarkets::linkats::multicast::link::v4_3 {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes before the first of a field's delimiters, which it leaves for what follows it; at
    // most its maximum, and the bytes must hold a delimiter when they are shorter than that
    template <std::size_t Count>
    std::size_t delimited(const std::byte* data, std::size_t length, std::size_t maximum, const std::array<std::byte, Count>& delimiters) {
        const std::size_t limit = std::min(maximum, length);
        for (std::size_t index = 0; index < limit; ++index) {
            for (const std::byte delimiter : delimiters) {
                if (data[index] == delimiter) { return index; }
            }
        }
        if (limit < length) { return limit; }
        throw short_read("no delimiter in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Issuer: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_issuer([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& issuer_section_1_ = tmp::read<issuer_section_1>(data + offset, bound - offset, handler); offset += issuer_section_1::size;
    if (static_cast<bool>(tmp::rule(issuer_section_1_.template get<issuer_size>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(issuer_section_1_.template get<issuer_size>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, issuer_name{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Security Detail: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_detail([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_detail_section_1_ = tmp::read<security_detail_section_1>(data + offset, bound - offset, handler); offset += security_detail_section_1::size;
    if (static_cast<bool>(tmp::rule(security_detail_section_1_.template get<security_detail_size>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(security_detail_section_1_.template get<security_detail_size>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, security_detail_name{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Extended Security No Cusip Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_extended_security_no_cusip_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& extended_security_no_cusip_message_section_1_ = tmp::read<extended_security_no_cusip_message_section_1>(data + offset, bound - offset, handler); offset += extended_security_no_cusip_message_section_1::size;
    offset += parse_security_detail(data + offset, bound - offset, handler);
    offset += parse_issuer(data + offset, bound - offset, handler);
    return offset;
}

// Extended Security Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_extended_security_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& extended_security_message_section_1_ = tmp::read<extended_security_message_section_1>(data + offset, bound - offset, handler); offset += extended_security_message_section_1::size;
    offset += parse_security_detail(data + offset, bound - offset, handler);
    offset += parse_issuer(data + offset, tmp::leaving(bound - offset, 9), handler);
    [[maybe_unused]] const auto& extended_security_message_section_2_ = tmp::read<extended_security_message_section_2>(data + offset, bound - offset, handler); offset += extended_security_message_section_2::size;
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& start_of_spin_message_ = tmp::read<start_of_spin_message>(data + offset, bound - offset, handler); offset += start_of_spin_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_spin_message_ = tmp::read<end_of_spin_message>(data + offset, bound - offset, handler); offset += end_of_spin_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 13)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_open_message_ = tmp::read<market_open_message>(data + offset, bound - offset, handler); offset += market_open_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 14)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_close_message_ = tmp::read<market_close_message>(data + offset, bound - offset, handler); offset += market_close_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 9)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_message_ = tmp::read<security_message>(data + offset, bound - offset, handler); offset += security_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_message_ = tmp::read<quote_message>(data + offset, bound - offset, handler); offset += quote_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_update_message_ = tmp::read<quote_update_message>(data + offset, bound - offset, handler); offset += quote_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& inside_message_ = tmp::read<inside_message>(data + offset, bound - offset, handler); offset += inside_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 4)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& inside_update_message_ = tmp::read<inside_update_message>(data + offset, bound - offset, handler); offset += inside_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 7)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reference_price_message_ = tmp::read<reference_price_message>(data + offset, bound - offset, handler); offset += reference_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 8)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reference_price_update_message_ = tmp::read<reference_price_update_message>(data + offset, bound - offset, handler); offset += reference_price_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_extended_security_message(data + offset, bound - offset, handler);
        tmp::call(handler, extended_security_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 16)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_extended_security_no_cusip_message(data + offset, bound - offset, handler);
        tmp::call(handler, extended_security_no_cusip_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 17)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_message_ = tmp::read<trade_message>(data + offset, bound - offset, handler); offset += trade_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_size>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_type>());
    return bound;
}

// Message Block: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message_block([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, heartbeat::type heartbeat_) {
    if (static_cast<bool>(tmp::rule(heartbeat_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat_packet{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
            tmp::require(end, bound);
            while (offset < end) {
                [[maybe_unused]] const std::size_t bound = end;
                offset += parse_message(data + offset, bound - offset, handler);
            }
        }
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_message_block(data + offset, bound - offset, handler, packet_header_.template get<packet_flag>().template get<heartbeat>());
    return offset;
}


} // namespace otcmarkets::linkats::multicast::link::v4_3

namespace protocol = ::otcmarkets::linkats::multicast::link::v4_3;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::packet_size>(); }) { checksum += bench::digest(header.template get<protocol::packet_size>().value()); }
        if constexpr (requires { header.template get<protocol::seq_num>(); }) { checksum += bench::digest(header.template get<protocol::seq_num>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::packet_milli>(); }) { checksum += bench::digest(header.template get<protocol::packet_milli>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_size>(); }) { checksum += bench::digest(header.template get<protocol::message_size>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::start_of_spin_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::spin_type>(); }) { checksum += bench::digest(message.template get<protocol::spin_type>().value()); }
        if constexpr (requires { message.template get<protocol::spin_start_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::spin_start_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::spin_last_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::spin_last_seq_num>().value()); }
    }

    void operator()(const protocol::end_of_spin_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::spin_type>(); }) { checksum += bench::digest(message.template get<protocol::spin_type>().value()); }
        if constexpr (requires { message.template get<protocol::spin_msg_ct>(); }) { checksum += bench::digest(message.template get<protocol::spin_msg_ct>().value()); }
        if constexpr (requires { message.template get<protocol::spin_end_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::spin_end_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::spin_last_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::spin_last_seq_num>().value()); }
    }

    void operator()(const protocol::market_open_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::market_open>(); }) { checksum += bench::digest(message.template get<protocol::market_open>().value()); }
        if constexpr (requires { message.template get<protocol::market_close>(); }) { checksum += bench::digest(message.template get<protocol::market_close>().value()); }
    }

    void operator()(const protocol::market_close_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::market_close_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::market_close_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::market_msg_ct>(); }) { checksum += bench::digest(message.template get<protocol::market_msg_ct>().value()); }
    }

    void operator()(const protocol::security_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::last_update_milli>(); }) { checksum += bench::digest(message.template get<protocol::last_update_milli>().value()); }
        if constexpr (requires { message.template get<protocol::security_action>(); }) { checksum += bench::digest(message.template get<protocol::security_action>().value()); }
        if constexpr (requires { message.template get<protocol::asset_class>(); }) { checksum += bench::digest(message.template get<protocol::asset_class>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::tier>(); }) { checksum += bench::digest(message.template get<protocol::tier>().value()); }
        if constexpr (requires { message.template get<protocol::reporting_status>(); }) { checksum += bench::digest(message.template get<protocol::reporting_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { checksum += bench::digest(message.template get<protocol::security_status>().value()); }
    }

    void operator()(const protocol::quote_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::quote_id>(); }) { checksum += bench::digest(message.template get<protocol::quote_id>().value()); }
        if constexpr (requires { message.template get<protocol::quote_action>(); }) { checksum += bench::digest(message.template get<protocol::quote_action>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::mpid>(); }) { checksum += bench::digest(message.template get<protocol::mpid>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { checksum += bench::digest(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size>(); }) { checksum += bench::digest(message.template get<protocol::ask_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_qap>(); }) { checksum += bench::digest(message.template get<protocol::ask_qap>().value()); }
        if constexpr (requires { message.template get<protocol::ask_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::ask_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { checksum += bench::digest(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { checksum += bench::digest(message.template get<protocol::bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_qap>(); }) { checksum += bench::digest(message.template get<protocol::bid_qap>().value()); }
        if constexpr (requires { message.template get<protocol::bid_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::bid_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::quote_reference_id>(); }) { checksum += bench::digest(message.template get<protocol::quote_reference_id>().value()); }
    }

    void operator()(const protocol::quote_update_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::quote_id>(); }) { checksum += bench::digest(message.template get<protocol::quote_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::qap>(); }) { checksum += bench::digest(message.template get<protocol::qap>().value()); }
        if constexpr (requires { message.template get<protocol::quote_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::quote_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::quote_reference_id>(); }) { checksum += bench::digest(message.template get<protocol::quote_reference_id>().value()); }
    }

    void operator()(const protocol::inside_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::inside_id>(); }) { checksum += bench::digest(message.template get<protocol::inside_id>().value()); }
        if constexpr (requires { message.template get<protocol::inside_action>(); }) { checksum += bench::digest(message.template get<protocol::inside_action>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { checksum += bench::digest(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size>(); }) { checksum += bench::digest(message.template get<protocol::ask_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::ask_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { checksum += bench::digest(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { checksum += bench::digest(message.template get<protocol::bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::bid_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::ask_num_priced_mp>(); }) { checksum += bench::digest(message.template get<protocol::ask_num_priced_mp>().value()); }
        if constexpr (requires { message.template get<protocol::bid_num_priced_mp>(); }) { checksum += bench::digest(message.template get<protocol::bid_num_priced_mp>().value()); }
    }

    void operator()(const protocol::inside_update_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::inside_id>(); }) { checksum += bench::digest(message.template get<protocol::inside_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::inside_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::inside_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::num_priced_mp>(); }) { checksum += bench::digest(message.template get<protocol::num_priced_mp>().value()); }
    }

    void operator()(const protocol::reference_price_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::reference_price_id>(); }) { checksum += bench::digest(message.template get<protocol::reference_price_id>().value()); }
        if constexpr (requires { message.template get<protocol::reference_price_action>(); }) { checksum += bench::digest(message.template get<protocol::reference_price_action>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { checksum += bench::digest(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size>(); }) { checksum += bench::digest(message.template get<protocol::ask_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::ask_time_milli>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { checksum += bench::digest(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { checksum += bench::digest(message.template get<protocol::bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::bid_time_milli>().value()); }
    }

    void operator()(const protocol::reference_price_update_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::reference_price_id>(); }) { checksum += bench::digest(message.template get<protocol::reference_price_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::time_milli>(); }) { checksum += bench::digest(message.template get<protocol::time_milli>().value()); }
    }

    void operator()(const protocol::extended_security_message&) {
    }

    void operator()(const protocol::extended_security_no_cusip_message&) {
    }

    void operator()(const protocol::trade_message& message) {
        if constexpr (requires { message.template get<protocol::channel_seq_num>(); }) { checksum += bench::digest(message.template get<protocol::channel_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_action>(); }) { checksum += bench::digest(message.template get<protocol::trade_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_flags>(); }) { checksum += bench::digest(message.template get<protocol::trade_flags>().value()); }
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::deprecated>(); }) { checksum += bench::digest(message.template get<protocol::deprecated>().value()); }
        if constexpr (requires { message.template get<protocol::trade_price>(); }) { checksum += bench::digest(message.template get<protocol::trade_price>().value()); }
        if constexpr (requires { message.template get<protocol::trade_size>(); }) { checksum += bench::digest(message.template get<protocol::trade_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_time_milli>(); }) { checksum += bench::digest(message.template get<protocol::trade_time_milli>().value()); }
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("OtcMarkets.LinkAts.Multicast.Link.v4.3", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
