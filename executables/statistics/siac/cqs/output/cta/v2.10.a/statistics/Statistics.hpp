#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/siac/cqs/output/cta/v2.10.a/definitions.hpp"

namespace statistics {

// Siac Cta C++ statistics
struct Statistics {

    siac::cqs::output::cta::v2_10_a::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t administrative_message = 0;
    uint64_t symbol_reference_data_message = 0;
    uint64_t control_message = 0;
    uint64_t start_of_day_message = 0;
    uint64_t finra_close_message = 0;
    uint64_t reset_block_sequence_number_message = 0;
    uint64_t finra_open_message = 0;
    uint64_t disaster_recovery_data_center_activation_message = 0;
    uint64_t line_integrity_message = 0;
    uint64_t end_of_day_message = 0;
    uint64_t market_status_message = 0;
    uint64_t market_wide_circuit_breaker_decline_level_status_message = 0;
    uint64_t market_wide_circuit_breaker_status_message = 0;
    uint64_t quote_message = 0;
    uint64_t auction_status_message = 0;
    uint64_t long_quote_message = 0;
    uint64_t short_quote_message = 0;
    uint64_t special_long_quote_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_message(const packet::Frame& frame) {
        message.initialize(frame.payload, frame.payload_len);

        while (message.next()) {
            process_message(message.message, message.message_category);
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte* pointer, const char message_category) {
        switch (message_category) {
            case 'A':
                ++total_messages;
                ++administrative_message;
                {
                    const auto* sub_header = siac::cqs::output::cta::v2_10_a::AdministrativeMessage::parse(pointer);
                    const char administrative_message_type = sub_header->administrative_message_type.get();
                    switch (administrative_message_type) {
                        case 'S':
                            ++symbol_reference_data_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'C':
                ++total_messages;
                ++control_message;
                {
                    const auto* sub_header = siac::cqs::output::cta::v2_10_a::ControlMessage::parse(pointer);
                    const char control_message_type = sub_header->control_message_type.get();
                    switch (control_message_type) {
                        case 'A':
                            ++start_of_day_message;
                            break;
                        case 'C':
                            ++finra_close_message;
                            break;
                        case 'L':
                            ++reset_block_sequence_number_message;
                            break;
                        case 'O':
                            ++finra_open_message;
                            break;
                        case 'P':
                            ++disaster_recovery_data_center_activation_message;
                            break;
                        case 'T':
                            ++line_integrity_message;
                            break;
                        case 'Z':
                            ++end_of_day_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'M':
                ++total_messages;
                ++market_status_message;
                {
                    const auto* sub_header = siac::cqs::output::cta::v2_10_a::MarketStatusMessage::parse(pointer);
                    const char market_status_message_type = sub_header->market_status_message_type.get();
                    switch (market_status_message_type) {
                        case 'K':
                            ++market_wide_circuit_breaker_decline_level_status_message;
                            break;
                        case 'L':
                            ++market_wide_circuit_breaker_status_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'Q':
                ++total_messages;
                ++quote_message;
                {
                    const auto* sub_header = siac::cqs::output::cta::v2_10_a::QuoteMessage::parse(pointer);
                    const char quote_message_type = sub_header->quote_message_type.get();
                    switch (quote_message_type) {
                        case 'A':
                            ++auction_status_message;
                            break;
                        case 'L':
                            ++long_quote_message;
                            break;
                        case 'Q':
                            ++short_quote_message;
                            break;
                        case 'S':
                            ++special_long_quote_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown message_category: " << static_cast<int>(message_category) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  AdministrativeMessage (A)                              " << administrative_message << std::endl;
        std::cout << "  SymbolReferenceDataMessage (S)                         " << symbol_reference_data_message << std::endl;
        std::cout << "  ControlMessage (C)                                     " << control_message << std::endl;
        std::cout << "  StartOfDayMessage (A)                                  " << start_of_day_message << std::endl;
        std::cout << "  FinraCloseMessage (C)                                  " << finra_close_message << std::endl;
        std::cout << "  ResetBlockSequenceNumberMessage (L)                    " << reset_block_sequence_number_message << std::endl;
        std::cout << "  FinraOpenMessage (O)                                   " << finra_open_message << std::endl;
        std::cout << "  DisasterRecoveryDataCenterActivationMessage (P)        " << disaster_recovery_data_center_activation_message << std::endl;
        std::cout << "  LineIntegrityMessage (T)                               " << line_integrity_message << std::endl;
        std::cout << "  EndOfDayMessage (Z)                                    " << end_of_day_message << std::endl;
        std::cout << "  MarketStatusMessage (M)                                " << market_status_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerDeclineLevelStatusMessage (K)  " << market_wide_circuit_breaker_decline_level_status_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerStatusMessage (L)              " << market_wide_circuit_breaker_status_message << std::endl;
        std::cout << "  QuoteMessage (Q)                                       " << quote_message << std::endl;
        std::cout << "  AuctionStatusMessage (A)                               " << auction_status_message << std::endl;
        std::cout << "  LongQuoteMessage (L)                                   " << long_quote_message << std::endl;
        std::cout << "  ShortQuoteMessage (Q)                                  " << short_quote_message << std::endl;
        std::cout << "  SpecialLongQuoteMessage (S)                            " << special_long_quote_message << std::endl;
    }
};
}
