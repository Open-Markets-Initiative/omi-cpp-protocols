// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a canonical values, through the Tmp header: every value the Tmp reading hands
// over from each sample, at its address, held to what the model reads.

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
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/tmp/nyse/amexoptions/deepfeed/xdp/v1.3.a/nyse_amexoptions_deepfeed_xdp_v1_3_a.hpp"

// Nyse AmexOptions DeepFeed Xdp 1.3.a: the reading of its packets, through its Template Meta Programming header
namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

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

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 403)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_market_depth_buy_message_ = tmp::read<outright_market_depth_buy_message>(data + offset, bound - offset, handler); offset += outright_market_depth_buy_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 405)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_market_depth_sell_message_ = tmp::read<outright_market_depth_sell_message>(data + offset, bound - offset, handler); offset += outright_market_depth_sell_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 419)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_status_message_ = tmp::read<underlying_status_message>(data + offset, bound - offset, handler); offset += underlying_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 421)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_series_status_message_ = tmp::read<outright_series_status_message>(data + offset, bound - offset, handler); offset += outright_series_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 503)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_outright_market_depth_buy_message_ = tmp::read<refresh_outright_market_depth_buy_message>(data + offset, bound - offset, handler); offset += refresh_outright_market_depth_buy_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 505)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_outright_market_depth_sell_message_ = tmp::read<refresh_outright_market_depth_sell_message>(data + offset, bound - offset, handler); offset += refresh_outright_market_depth_sell_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 435)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& underlying_index_mapping_message_ = tmp::read<underlying_index_mapping_message>(data + offset, bound - offset, handler); offset += underlying_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 437)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& series_index_mapping_message_ = tmp::read<series_index_mapping_message>(data + offset, bound - offset, handler); offset += series_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 455)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stream_id_message_ = tmp::read<stream_id_message>(data + offset, bound - offset, handler); offset += stream_id_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& sequence_number_reset_message_ = tmp::read<sequence_number_reset_message>(data + offset, bound - offset, handler); offset += sequence_number_reset_message::size;
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

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
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


} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a

namespace protocol = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::packet_size>(); }) { values["packet.packetheader.packetsize"] = canonical::number(header.template get<protocol::packet_size>().value()); }
        if constexpr (requires { header.template get<protocol::delivery_flag>(); }) { values["packet.packetheader.deliveryflag"] = canonical::number(header.template get<protocol::delivery_flag>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_size>(); }) { values[entry + ".messageheader.messagesize"] = canonical::number(header.template get<protocol::message_size>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::number(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::outright_market_depth_buy_message& message) {
        values[entry + ".payload"] = "packet.message.payload.outrightmarketdepthbuymessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.sourcens"] = canonical::number(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelprice"] = canonical::number(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelprice"] = canonical::number(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelprice"] = canonical::number(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_volume>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelvolume"] = canonical::number(message.template get<protocol::first_level_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_volume>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelvolume"] = canonical::number(message.template get<protocol::second_level_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_volume>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelvolume"] = canonical::number(message.template get<protocol::third_level_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelcustomervolume"] = canonical::number(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelcustomervolume"] = canonical::number(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelcustomervolume"] = canonical::number(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::outright_market_depth_sell_message& message) {
        values[entry + ".payload"] = "packet.message.payload.outrightmarketdepthsellmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.sourcens"] = canonical::number(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.firstlevelprice"] = canonical::number(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.secondlevelprice"] = canonical::number(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.thirdlevelprice"] = canonical::number(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_volume>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.firstvolume"] = canonical::number(message.template get<protocol::first_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_volume>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.secondvolume"] = canonical::number(message.template get<protocol::second_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_volume>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.thirdvolume"] = canonical::number(message.template get<protocol::third_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.firstlevelcustomervolume"] = canonical::number(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.secondlevelcustomervolume"] = canonical::number(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { values[entry + ".payload.outrightmarketdepthsellmessage.thirdlevelcustomervolume"] = canonical::number(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::underlying_status_message& message) {
        values[entry + ".payload"] = "packet.message.payload.underlyingstatusmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.underlyingstatusmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.underlyingstatusmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { values[entry + ".payload.underlyingstatusmessage.underlyingindex"] = canonical::number(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_seq_num>(); }) { values[entry + ".payload.underlyingstatusmessage.underlyingseqnum"] = canonical::number(message.template get<protocol::underlying_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.underlyingstatusmessage.securitystatus"] = canonical::text(canonical::character(message.template get<protocol::security_status>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { values[entry + ".payload.underlyingstatusmessage.haltcondition"] = canonical::text(canonical::character(message.template get<protocol::halt_condition>().value()), '\0', false); }
    }

    void operator()(const protocol::outright_series_status_message& message) {
        values[entry + ".payload"] = "packet.message.payload.outrightseriesstatusmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.outrightseriesstatusmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.outrightseriesstatusmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.outrightseriesstatusmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.outrightseriesstatusmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.outrightseriesstatusmessage.securitystatus"] = canonical::text(canonical::character(message.template get<protocol::security_status>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { values[entry + ".payload.outrightseriesstatusmessage.haltcondition"] = canonical::text(canonical::character(message.template get<protocol::halt_condition>().value()), '\0', false); }
    }

    void operator()(const protocol::refresh_outright_market_depth_buy_message& message) {
        values[entry + ".payload"] = "packet.message.payload.refreshoutrightmarketdepthbuymessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.sourcens"] = canonical::number(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstlevelprice"] = canonical::number(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondlevelprice"] = canonical::number(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdlevelprice"] = canonical::number(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstvolume"] = canonical::number(message.template get<protocol::first_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondvolume"] = canonical::number(message.template get<protocol::second_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdvolume"] = canonical::number(message.template get<protocol::third_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstlevelcustomervolume"] = canonical::number(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondlevelcustomervolume"] = canonical::number(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdlevelcustomervolume"] = canonical::number(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::refresh_outright_market_depth_sell_message& message) {
        values[entry + ".payload"] = "packet.message.payload.refreshoutrightmarketdepthsellmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::first_level_price>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstlevelprice"] = canonical::number(message.template get<protocol::first_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_price>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondlevelprice"] = canonical::number(message.template get<protocol::second_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_price>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdlevelprice"] = canonical::number(message.template get<protocol::third_level_price>().value()); }
        if constexpr (requires { message.template get<protocol::first_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstvolume"] = canonical::number(message.template get<protocol::first_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondvolume"] = canonical::number(message.template get<protocol::second_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdvolume"] = canonical::number(message.template get<protocol::third_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::first_level_customer_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstlevelcustomervolume"] = canonical::number(message.template get<protocol::first_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::second_level_customer_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondlevelcustomervolume"] = canonical::number(message.template get<protocol::second_level_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::third_level_customer_volume>(); }) { values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdlevelcustomervolume"] = canonical::number(message.template get<protocol::third_level_customer_volume>().value()); }
    }

    void operator()(const protocol::underlying_index_mapping_message& message) {
        values[entry + ".payload"] = "packet.message.payload.underlyingindexmappingmessage";
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { values[entry + ".payload.underlyingindexmappingmessage.underlyingindex"] = canonical::number(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_symbol>(); }) { values[entry + ".payload.underlyingindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.template get<protocol::underlying_symbol>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.underlyingindexmappingmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { values[entry + ".payload.underlyingindexmappingmessage.marketid"] = canonical::number(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { values[entry + ".payload.underlyingindexmappingmessage.systemid"] = canonical::number(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::exchange_code>(); }) { values[entry + ".payload.underlyingindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.template get<protocol::exchange_code>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { values[entry + ".payload.underlyingindexmappingmessage.pricescalecode"] = canonical::number(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::security_type>(); }) { values[entry + ".payload.underlyingindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.template get<protocol::security_type>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::price_resolution>(); }) { values[entry + ".payload.underlyingindexmappingmessage.priceresolution"] = canonical::number(message.template get<protocol::price_resolution>().value()); }
    }

    void operator()(const protocol::series_index_mapping_message& message) {
        values[entry + ".payload"] = "packet.message.payload.seriesindexmappingmessage";
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.seriesindexmappingmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.seriesindexmappingmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { values[entry + ".payload.seriesindexmappingmessage.marketid"] = canonical::number(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { values[entry + ".payload.seriesindexmappingmessage.systemid"] = canonical::number(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::stream_id>(); }) { values[entry + ".payload.seriesindexmappingmessage.streamid"] = canonical::number(message.template get<protocol::stream_id>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { values[entry + ".payload.seriesindexmappingmessage.underlyingindex"] = canonical::number(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::contract_multiplier>(); }) { values[entry + ".payload.seriesindexmappingmessage.contractmultiplier"] = canonical::number(message.template get<protocol::contract_multiplier>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_date>(); }) { values[entry + ".payload.seriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message.template get<protocol::maturity_date>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::put_or_call>(); }) { values[entry + ".payload.seriesindexmappingmessage.putorcall"] = canonical::number(message.template get<protocol::put_or_call>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price>(); }) { values[entry + ".payload.seriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message.template get<protocol::strike_price>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { values[entry + ".payload.seriesindexmappingmessage.pricescalecode"] = canonical::number(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::underlying_symbol>(); }) { values[entry + ".payload.seriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.template get<protocol::underlying_symbol>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::option_symbol_root>(); }) { values[entry + ".payload.seriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message.template get<protocol::option_symbol_root>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::group_id>(); }) { values[entry + ".payload.seriesindexmappingmessage.groupid"] = canonical::number(message.template get<protocol::group_id>().value()); }
    }

    void operator()(const protocol::stream_id_message& message) {
        values[entry + ".payload"] = "packet.message.payload.streamidmessage";
        if constexpr (requires { message.template get<protocol::stream_id>(); }) { values[entry + ".payload.streamidmessage.streamid"] = canonical::number(message.template get<protocol::stream_id>().value()); }
    }

    void operator()(const protocol::sequence_number_reset_message& message) {
        values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
    }
};

// The values the Tmp reading reads from one datagram, by indexed address. A datagram it cannot read
// is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Tmp and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a (tmp values)\n");
    int failures = 0;
    failures += check("OutrightMarketDepthBuyMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/OutrightMarketDepthBuyMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/OutrightMarketDepthBuyMessage.values");
    failures += check("OutrightMarketDepthSellMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/OutrightMarketDepthSellMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/OutrightMarketDepthSellMessage.values");
    failures += check("RefreshOutrightMarketDepthBuyMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/RefreshOutrightMarketDepthBuyMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/RefreshOutrightMarketDepthBuyMessage.values");
    failures += check("RefreshOutrightMarketDepthSellMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/RefreshOutrightMarketDepthSellMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/RefreshOutrightMarketDepthSellMessage.values");
    failures += check("StreamIdMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/StreamIdMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/StreamIdMessage.values");
    return failures == 0 ? 0 : 1;
}
