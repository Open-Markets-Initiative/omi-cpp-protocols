cmake_minimum_required(VERSION 3.20)
project(omi_cpp_protocols CXX)

# The modern parser uses C++23 (std::byteswap, etc.); a C++23 compiler (GCC 15+) is required.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Each translation unit under checks/ includes a protocol's aggregating headers, so
# compiling it fires the generated layout static_asserts. A clean build is the gate:
# it proves every parser (structs, types, messages) is well-formed and self-consistent.
add_library(protocols_check OBJECT
  checks/asx_asxderivatives_ntp_itch_v1.05_advanced.cpp
  checks/asx_asxderivatives_ntp_itch_v1.05_modern.cpp
  checks/asx_asxderivatives_ntp_itch_v1.05_classes.cpp
  checks/asx_asxderivatives_ntp_itch_v1.05_flyweight.cpp
  checks/asx_asxderivatives_ntp_itch_v1.05_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_tmp.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_flyweight.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_tmp.cpp
  checks/cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29_advanced.cpp
  checks/cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29_modern.cpp
  checks/cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29_classes.cpp
  checks/cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29_flyweight.cpp
  checks/cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29_tmp.cpp
  checks/cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80_advanced.cpp
  checks/cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80_modern.cpp
  checks/cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80_classes.cpp
  checks/cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80_flyweight.cpp
  checks/cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80_tmp.cpp
  checks/cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22_advanced.cpp
  checks/cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22_modern.cpp
  checks/cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22_classes.cpp
  checks/cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22_flyweight.cpp
  checks/cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22_tmp.cpp
  checks/cme_globex_mdp3_sbe_v1.8_advanced.cpp
  checks/cme_globex_mdp3_sbe_v1.8_modern.cpp
  checks/cme_globex_mdp3_sbe_v1.8_classes.cpp
  checks/cme_globex_mdp3_sbe_v1.8_flyweight.cpp
  checks/cme_globex_mdp3_sbe_v1.8_tmp.cpp
  checks/cme_globex_mdp3_sbe_v1.9_advanced.cpp
  checks/cme_globex_mdp3_sbe_v1.9_modern.cpp
  checks/cme_globex_mdp3_sbe_v1.9_classes.cpp
  checks/cme_globex_mdp3_sbe_v1.9_flyweight.cpp
  checks/cme_globex_mdp3_sbe_v1.9_tmp.cpp
  checks/cme_globex_mdp3_sbe_v1.13_advanced.cpp
  checks/cme_globex_mdp3_sbe_v1.13_modern.cpp
  checks/cme_globex_mdp3_sbe_v1.13_classes.cpp
  checks/cme_globex_mdp3_sbe_v1.13_flyweight.cpp
  checks/cme_globex_mdp3_sbe_v1.13_tmp.cpp
  checks/eurex_t7_eobi_fbe_v13.0_advanced.cpp
  checks/eurex_t7_eobi_fbe_v13.0_modern.cpp
  checks/eurex_t7_eobi_fbe_v13.0_classes.cpp
  checks/eurex_t7_eobi_fbe_v13.0_flyweight.cpp
  checks/eurex_t7_eobi_fbe_v13.0_tmp.cpp
  checks/eurex_t7_eobi_fbe_v15.0_advanced.cpp
  checks/eurex_t7_eobi_fbe_v15.0_modern.cpp
  checks/eurex_t7_eobi_fbe_v15.0_classes.cpp
  checks/eurex_t7_eobi_fbe_v15.0_flyweight.cpp
  checks/eurex_t7_eobi_fbe_v15.0_tmp.cpp
  checks/iex_iexequities_deep_iextp_v1.06_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.06_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.06_classes.cpp
  checks/iex_iexequities_deep_iextp_v1.06_flyweight.cpp
  checks/iex_iexequities_deep_iextp_v1.06_tmp.cpp
  checks/iex_iexequities_deep_iextp_v1.08_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.08_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.08_classes.cpp
  checks/iex_iexequities_deep_iextp_v1.08_flyweight.cpp
  checks/iex_iexequities_deep_iextp_v1.08_tmp.cpp
  checks/iex_iexequities_deep_snap_v1.6_advanced.cpp
  checks/iex_iexequities_deep_snap_v1.6_modern.cpp
  checks/iex_iexequities_deep_snap_v1.6_classes.cpp
  checks/iex_iexequities_deep_snap_v1.6_flyweight.cpp
  checks/iex_iexequities_deep_snap_v1.6_tmp.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_classes.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_flyweight.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_tmp.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_classes.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_flyweight.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_tmp.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_advanced.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_modern.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_classes.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_flyweight.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_tmp.cpp
  checks/iex_iexequities_tops_iextp_v1.56_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.56_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.56_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.56_flyweight.cpp
  checks/iex_iexequities_tops_iextp_v1.56_tmp.cpp
  checks/iex_iexequities_tops_iextp_v1.64_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.64_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.64_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.64_flyweight.cpp
  checks/iex_iexequities_tops_iextp_v1.64_tmp.cpp
  checks/iex_iexequities_tops_iextp_v1.66_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.66_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.66_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.66_flyweight.cpp
  checks/iex_iexequities_tops_iextp_v1.66_tmp.cpp
  checks/iex_iexequities_tops_snap_v1.6_advanced.cpp
  checks/iex_iexequities_tops_snap_v1.6_modern.cpp
  checks/iex_iexequities_tops_snap_v1.6_classes.cpp
  checks/iex_iexequities_tops_snap_v1.6_flyweight.cpp
  checks/iex_iexequities_tops_snap_v1.6_tmp.cpp
  checks/jpx_osederivatives_geniuminet_itch_v5.0.6_advanced.cpp
  checks/jpx_osederivatives_geniuminet_itch_v5.0.6_modern.cpp
  checks/jpx_osederivatives_geniuminet_itch_v5.0.6_classes.cpp
  checks/jpx_osederivatives_geniuminet_itch_v5.0.6_flyweight.cpp
  checks/jpx_osederivatives_geniuminet_itch_v5.0.6_tmp.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_advanced.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_modern.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_classes.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_flyweight.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_tmp.cpp
  checks/lseg_lse_level2mbo_gtp_v26.2_advanced.cpp
  checks/lseg_lse_level2mbo_gtp_v26.2_modern.cpp
  checks/lseg_lse_level2mbo_gtp_v26.2_classes.cpp
  checks/lseg_lse_level2mbo_gtp_v26.2_flyweight.cpp
  checks/lseg_lse_level2mbo_gtp_v26.2_tmp.cpp
  checks/lseg_millennium_level2_mitch_v11.9_advanced.cpp
  checks/lseg_millennium_level2_mitch_v11.9_modern.cpp
  checks/lseg_millennium_level2_mitch_v11.9_classes.cpp
  checks/lseg_millennium_level2_mitch_v11.9_flyweight.cpp
  checks/lseg_millennium_level2_mitch_v11.9_tmp.cpp
  checks/memx_memxequities_memoirdepthfeed_sbe_v1.3_advanced.cpp
  checks/memx_memxequities_memoirdepthfeed_sbe_v1.3_modern.cpp
  checks/memx_memxequities_memoirdepthfeed_sbe_v1.3_classes.cpp
  checks/memx_memxequities_memoirdepthfeed_sbe_v1.3_flyweight.cpp
  checks/memx_memxequities_memoirdepthfeed_sbe_v1.3_tmp.cpp
  checks/miax_pearlequities_depthofmarket_mach_v1.3.d_advanced.cpp
  checks/miax_pearlequities_depthofmarket_mach_v1.3.d_modern.cpp
  checks/miax_pearlequities_depthofmarket_mach_v1.3.d_tmp.cpp
  checks/miax_miaxoptions_topofmarket_mach_v2.5_advanced.cpp
  checks/miax_miaxoptions_topofmarket_mach_v2.5_modern.cpp
  checks/miax_miaxoptions_topofmarket_mach_v2.5_tmp.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2017_advanced.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2017_modern.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2017_classes.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2017_flyweight.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2017_tmp.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_advanced.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_modern.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_classes.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_flyweight.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_tmp.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2026_advanced.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2026_modern.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2026_classes.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2026_flyweight.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2026_tmp.cpp
  checks/nasdaq_nsmequities_qbbo_itch_v2.1_advanced.cpp
  checks/nasdaq_nsmequities_qbbo_itch_v2.1_modern.cpp
  checks/nasdaq_nsmequities_qbbo_itch_v2.1_classes.cpp
  checks/nasdaq_nsmequities_qbbo_itch_v2.1_flyweight.cpp
  checks/nasdaq_nsmequities_qbbo_itch_v2.1_tmp.cpp
  checks/nasdaq_nomoptions_itto_itch_v4.0.2025_advanced.cpp
  checks/nasdaq_nomoptions_itto_itch_v4.0.2025_modern.cpp
  checks/nasdaq_nomoptions_itto_itch_v4.0.2025_classes.cpp
  checks/nasdaq_nomoptions_itto_itch_v4.0.2025_flyweight.cpp
  checks/nasdaq_nomoptions_itto_itch_v4.0.2025_tmp.cpp
  checks/nasdaq_phlxoptions_topofmarket_itch_v3.4_advanced.cpp
  checks/nasdaq_phlxoptions_topofmarket_itch_v3.4_modern.cpp
  checks/nasdaq_phlxoptions_topofmarket_itch_v3.4_classes.cpp
  checks/nasdaq_phlxoptions_topofmarket_itch_v3.4_flyweight.cpp
  checks/nasdaq_phlxoptions_topofmarket_itch_v3.4_tmp.cpp
  checks/nasdaq_nordicequities_totalview_itch_v3.04.x_advanced.cpp
  checks/nasdaq_nordicequities_totalview_itch_v3.04.x_modern.cpp
  checks/nasdaq_nordicequities_totalview_itch_v3.04.x_classes.cpp
  checks/nasdaq_nordicequities_totalview_itch_v3.04.x_flyweight.cpp
  checks/nasdaq_nordicequities_totalview_itch_v3.04.x_tmp.cpp
  checks/nyse_arcaequities_integratedfeed_pillar_v2.5.g_advanced.cpp
  checks/nyse_arcaequities_integratedfeed_pillar_v2.5.g_modern.cpp
  checks/nyse_arcaequities_integratedfeed_pillar_v2.5.g_classes.cpp
  checks/nyse_arcaequities_integratedfeed_pillar_v2.5.g_flyweight.cpp
  checks/nyse_arcaequities_integratedfeed_pillar_v2.5.g_tmp.cpp
  checks/nyse_arcaoptions_deepfeed_pillar_v1.2.m_advanced.cpp
  checks/nyse_arcaoptions_deepfeed_pillar_v1.2.m_modern.cpp
  checks/nyse_arcaoptions_deepfeed_pillar_v1.2.m_classes.cpp
  checks/nyse_arcaoptions_deepfeed_pillar_v1.2.m_flyweight.cpp
  checks/nyse_arcaoptions_deepfeed_pillar_v1.2.m_tmp.cpp
  checks/nyse_nyseequities_integratedfeed_xdp_v2.3.a_advanced.cpp
  checks/nyse_nyseequities_integratedfeed_xdp_v2.3.a_modern.cpp
  checks/nyse_nyseequities_integratedfeed_xdp_v2.3.a_classes.cpp
  checks/nyse_nyseequities_integratedfeed_xdp_v2.3.a_flyweight.cpp
  checks/nyse_nyseequities_integratedfeed_xdp_v2.3.a_tmp.cpp
  checks/siac_opra_output_obi_v6.2_advanced.cpp
  checks/siac_opra_output_obi_v6.2_modern.cpp
  checks/siac_opra_output_obi_v6.2_classes.cpp
  checks/siac_opra_output_obi_v6.2_flyweight.cpp
  checks/siac_opra_output_obi_v6.2_tmp.cpp
  checks/siac_cts_output_cta_v2.11.b_advanced.cpp
  checks/siac_cts_output_cta_v2.11.b_modern.cpp
  checks/siac_cts_output_cta_v2.11.b_classes.cpp
  checks/siac_cts_output_cta_v2.11.b_flyweight.cpp
  checks/siac_cts_output_cta_v2.11.b_tmp.cpp
  checks/siac_cqs_output_cta_v2.10.a_advanced.cpp
  checks/siac_cqs_output_cta_v2.10.a_modern.cpp
  checks/siac_cqs_output_cta_v2.10.a_classes.cpp
  checks/siac_cqs_output_cta_v2.10.a_flyweight.cpp
  checks/siac_cqs_output_cta_v2.10.a_tmp.cpp
)
# The libraries of the formats with sources of their own (cpp/classes/, cpp/flyweight/) — one
# static library per protocol and format, linked by the programs and tests that read through it.
# Each library precompiles the standard headers every one of its many small sources parses.
add_library(classes_asx_asxderivatives_ntp_itch_v1.05 STATIC
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/MessageType.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/EventCode.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/ExpiryMonth.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/OptionType.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/PriceMethod.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/SideLeg.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/SessionState.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/Side.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/TradeType.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/OppositeSide.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/BuyerSide.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/SellerSide.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/enums/RfqSide.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/structs/PacketHeader.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/structs/MessageHeader.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/SecondsMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/EndOfBusinessTradeDateMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/FutureSymbolDirectoryMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/OptionsSymbolDirectoryMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/groups/CombinationLeg.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/CombinationSymbolDirectoryMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/groups/BundleLeg.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/BundlesSymbolDirectory.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/OrderBookStateMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/AddOrderMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/OrderVolumeCancelledMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/OrderDeletedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/OrderExecutedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/AuctionOrderExecutedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/CombinationOrderExecutedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/ImpliedOrderAddedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/ImpliedOrderReplacedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/ImpliedOrderDeletedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/TradeExecutedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/CombinationTradeExecutedMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/TradeCancellationMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/EquilibriumPriceMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/OpenHighLowLastTradeAdjustmentMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/MarketSettlementMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/TextMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/RequestForQuoteMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/AnomalousOrderThresholdPublishMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/VolumeAndOpenInterestMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/messages/UnknownMessage.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/Factory.cpp
  cpp/classes/asx/asxderivatives/ntp/itch/v1.05/Packet.cpp
)
target_include_directories(classes_asx_asxderivatives_ntp_itch_v1.05 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_asx_asxderivatives_ntp_itch_v1.05 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_asx_asxderivatives_ntp_itch_v1.05 STATIC
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/MessageType.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/EventCode.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/ExpiryMonth.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/OptionType.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/PriceMethod.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/SideLeg.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/SessionState.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/Side.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/TradeType.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/OppositeSide.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/BuyerSide.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/SellerSide.cpp
  cpp/flyweight/asx/asxderivatives/ntp/itch/v1.05/enums/RfqSide.cpp
)
target_include_directories(flyweight_asx_asxderivatives_ntp_itch_v1.05 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_asx_asxderivatives_ntp_itch_v1.05 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.6 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/DeprecatedUnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/DeprecatedUnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/DeprecatedLegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/DeprecatedLegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/DeprecatedInstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/DeprecatedInstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/DeprecatedSecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/PriceBand20Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.6 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.7 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/DeprecatedUnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/DeprecatedUnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/DeprecatedLegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/DeprecatedLegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/DeprecatedInstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/DeprecatedInstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/DeprecatedSecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/PriceBand20Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.7 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.7 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.7 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.8 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/DeprecatedUnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/DeprecatedUnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/DeprecatedLegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/DeprecatedLegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/DeprecatedInstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/DeprecatedInstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/DeprecatedSecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/PriceBand20Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.8 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.8 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceTypeOptional.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SettlPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.8 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.9 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/MatchEventIndicatorOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.9 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceTypeOptional.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/ImpliedMarketIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SettlPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v2.1 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v2.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.1 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceTypeOptional.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/ImpliedMarketIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SettlPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v2.2 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/OptPayoutType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v2.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.2 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceTypeOptional.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/ImpliedMarketIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/OptPayoutType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SettlPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v2.3 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OptPayoutType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OpenCloseSettlFlagOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v2.3 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.3 STATIC
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TemplateId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TradingSessionId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityTradingStatus.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityTradingEvent.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TradingSessionSubId.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityIdSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LotType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/Product.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/ExerciseStyle.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PutOrCall.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceTypeOptional.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/GovernanceIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityMatchType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LastFragment.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MultiLegModel.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MultiLegPriceMethod.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/ImpliedMarketIndicator.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OptPayoutType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LegSecurityType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LegSide.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/InstrAttribType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/InstrAttribValue.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/NewsSource.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MdUpdateAction.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceBandType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceLimitType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceBandMidpointPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TrdSubType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OpenCloseSettlFlagOptional.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SettlPriceType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MdEntryType.cpp
  cpp/flyweight/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/AggressorSide.cpp
)
target_include_directories(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.3 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 STATIC
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/MessageType.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/SideIndicator.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/TradingStatus.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/RegShoAction.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/AuctionType.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/structs/PacketHeader.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/structs/MessageHeader.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/TimeMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/UnitClearMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/bitfields/AddOrderFlags.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/AddOrderLongMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/AddOrderShortMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/AddOrderExpandedMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/OrderExecutedMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/OrderExecutedAtPriceSizeMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/ReduceSizeLongMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/ReduceSizeShortMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/bitfields/ModifyOrderFlags.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/ModifyOrderLongMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/ModifyOrderShortMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/DeleteOrderMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/TradeLongMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/TradeShortMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/TradeExpandedMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/TradeBreakMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/EndOfSession.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/TradingStatusMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/AuctionUpdateMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/AuctionSummaryMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/messages/UnknownMessage.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/Factory.cpp
  cpp/classes/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/Packet.cpp
)
target_include_directories(classes_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 STATIC
  cpp/flyweight/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/MessageType.cpp
  cpp/flyweight/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/SideIndicator.cpp
  cpp/flyweight/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/TradingStatus.cpp
  cpp/flyweight/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/RegShoAction.cpp
  cpp/flyweight/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/enums/AuctionType.cpp
)
target_include_directories(flyweight_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 STATIC
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/MessageType.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/SideIndicator.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/CustomerIndicator.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/TradeCondition.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/SymbolCondition.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/TradingStatus.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/GthTradingStatus.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/WidthType.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/AuctionType.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/OpeningCondition.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/Side.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/structs/PacketHeader.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/structs/MessageHeader.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TimeMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/UnitClearMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TransactionBeginMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TransactionEndMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/bitfields/AddFlags.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AddOrderLongMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AddOrderShortMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AddOrderExpandedMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/OrderExecutedMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/OrderExecutedAtPriceSizeMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/ReduceSizeLongMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/ReduceSizeShortMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/bitfields/ModifyFlags.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/ModifyOrderLongMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/ModifyOrderShortMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/DeleteOrderMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TradeLongMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TradeShortMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TradeExpandedMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TradeBreakMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/EndOfSessionMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/SymbolMappingMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/TradingStatusMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/WidthUpdateMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/OptionsAuctionUpdateMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AuctionSummaryMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AuctionNotificationMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AuctionCancelMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/AuctionTradeMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/SoqStrikeRangeUpdateMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/ConstituentSymbolMappingMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/UnknownMessage.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/Factory.cpp
  cpp/classes/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/Packet.cpp
)
target_include_directories(classes_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 STATIC
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/MessageType.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/SideIndicator.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/CustomerIndicator.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/TradeCondition.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/SymbolCondition.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/TradingStatus.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/GthTradingStatus.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/WidthType.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/AuctionType.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/OpeningCondition.cpp
  cpp/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/enums/Side.cpp
)
target_include_directories(flyweight_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 STATIC
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/MessageType.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/ListingState.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/SideIndicator.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/TradeCondition.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/Issue.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/TradingStatus.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/structs/PacketHeader.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/structs/MessageHeader.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TimeReferenceMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TimeMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/UnitClearMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/bitfields/FuturesFlags.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/groups/FutureLeg.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/FuturesInstrumentDefinitionMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/FuturesVarianceSymbolMappingMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/PriceLimitsMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/AddOrderLongMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/AddOrderShortMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/OrderExecutedMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/ReduceSizeLongMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/ReduceSizeShortMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/ModifyOrderLongMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/ModifyOrderShortMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/DeleteOrderMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TradeLongMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TradeShortMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TransactionBeginMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TransactionEndMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TradeBreakMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/SettlementMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/OpenInterestMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/bitfields/SummaryFlags.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/EndOfDaySummaryMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/TradingStatusMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/EndOfSessionMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/UnknownMessage.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/Factory.cpp
  cpp/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/Packet.cpp
)
target_include_directories(classes_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 STATIC
  cpp/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/MessageType.cpp
  cpp/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/ListingState.cpp
  cpp/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/SideIndicator.cpp
  cpp/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/TradeCondition.cpp
  cpp/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/Issue.cpp
  cpp/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/enums/TradingStatus.cpp
)
target_include_directories(flyweight_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_cme_globex_mdp3_sbe_v1.8 STATIC
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/TemplateId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/SchemaId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/SecurityUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdSecurityTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/EventType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/LegSide.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/SecurityTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/HaltReason.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/SecurityTradingEvent.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdEntryTypeBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/OrderUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdEntryTypeDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/OpenCloseSettlFlag.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdEntryTypeStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/AggressorSide.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdEntryType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/PutOrCall.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/ErrorCodes.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/SubscriptionReqType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdReqIdStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/enums/MdReqRejReason.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/BinaryPacketHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/MessageHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/bitfields/MatchEventIndicator.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/GroupSize.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/ChannelResetGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/ChannelResetGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ChannelReset.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/AdminHeartbeat.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/AdminLogin.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/AdminLogout.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/MaturityMonthYear.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/bitfields/SettlPriceType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/EventsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/EventsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/FeedTypesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/FeedTypesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/bitfields/InstAttribValue.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/InstAttribGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/InstAttribGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/LotTypeRulesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/LotTypeRulesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdInstrumentDefinitionFuture.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/LegacyLegsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/LegacyLegsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdInstrumentDefinitionSpread.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/SecurityStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/GroupSize8Byte.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshBookOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshBookOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshDailyStatisticsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshDailyStatisticsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshLimitsBandingGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshLimitsBandingGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshLimitsBanding.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshSessionStatisticsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshSessionStatisticsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshSessionStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshTradeGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshTradeGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshTrade.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshVolumeGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshVolumeGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshVolume.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/SnapshotFullRefreshGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/SnapshotFullRefreshGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/SnapshotFullRefresh.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/RelatedSymGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/RelatedSymGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/QuoteRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/OptionUnderlyingsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/OptionUnderlyingsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/OptionRelatedInstrumentsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/OptionRelatedInstrumentsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdInstrumentDefinitionOption.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshTradeSummaryGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshTradeSummaryGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshTradeSummaryOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshTradeSummaryOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshTradeSummary.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/IncrementalRefreshOrderBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/IncrementalRefreshOrderBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdIncrementalRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/SnapshotFullRefreshOrderBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/SnapshotFullRefreshOrderBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/SnapshotFullRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MktdataMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/Negotiate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/NegotiationReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/NegotiationResponse.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/Terminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/MarketDataRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/MarketDataRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/MarketDataRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/MarketDataRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MarketDataRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/RequestAckSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/RequestAckSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/RequestAckRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/RequestAckRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/RequestAck.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/RequestReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/SecurityListRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/SecurityListRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/SecurityListRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/SecurityListRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/SecurityListRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/SecurityStatusRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/SecurityStatusRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/groups/SecurityStatusRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/SecurityStatusRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/SecurityStatusRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/SubscriberHeartbeat.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/MdpsessionmgmtMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/ClientTechnicalHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ClientPayloadNegotiate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ClientPayloadTerminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ClientPayloadMarketDataRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ClientPayloadSecurityListRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ClientPayloadSecurityStatusRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/structs/ServerTechnicalHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadChannelReset.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadAdminLogin.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadAdminLogout.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdInstrumentDefinitionFuture.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdInstrumentDefinitionSpread.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadSecurityStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshLimitsBanding.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshSessionStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshTrade.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshVolume.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadSnapshotFullRefresh.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadQuoteRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdInstrumentDefinitionOption.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshTradeSummary.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadMdIncrementalRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadSnapshotFullRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadNegotiationReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadNegotiationResponse.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadTerminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadRequestAck.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/ServerPayloadRequestReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/UnknownMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/UnknownMktdataPayload.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/UnknownMdpsessionmgmtPayload.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/UnknownClientTcpMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/messages/UnknownServerTcpMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/Factory.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/UdpPacket.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/ClientTcpPacket.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.8/ServerTcpPacket.cpp
)
target_include_directories(classes_cme_globex_mdp3_sbe_v1.8 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_cme_globex_mdp3_sbe_v1.8 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_cme_globex_mdp3_sbe_v1.8 STATIC
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/TemplateId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/SchemaId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/SecurityUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdSecurityTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/EventType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/LegSide.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/SecurityTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/HaltReason.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/SecurityTradingEvent.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdEntryTypeBook.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/OrderUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdEntryTypeDailyStatistics.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdEntryTypeStatistics.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/AggressorSide.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdEntryType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/PutOrCall.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/ErrorCodes.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/SubscriptionReqType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdReqIdStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.8/enums/MdReqRejReason.cpp
)
target_include_directories(flyweight_cme_globex_mdp3_sbe_v1.8 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_cme_globex_mdp3_sbe_v1.8 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_cme_globex_mdp3_sbe_v1.9 STATIC
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/TemplateId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/SchemaId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/SecurityUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdSecurityTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/EventType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/LegSide.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/SecurityTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/HaltReason.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/SecurityTradingEvent.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdEntryTypeBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/OrderUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdEntryTypeDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/OpenCloseSettlFlag.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdEntryTypeStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdEntryType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/PutOrCall.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/AggressorSide.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/ErrorCodes.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/SubscriptionReqType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdReqIdStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/enums/MdReqRejReason.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/BinaryPacketHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/MessageHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/bitfields/MatchEventIndicator.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/GroupSize.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/ChannelResetGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/ChannelResetGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ChannelReset.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/AdminHeartbeat.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/AdminLogin.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/AdminLogout.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/MaturityMonthYear.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/bitfields/SettlPriceType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/EventsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/EventsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/FeedTypesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/FeedTypesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/bitfields/InstAttribValue.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/InstAttribGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/InstAttribGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/LotTypeRulesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/LotTypeRulesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdInstrumentDefinitionFutureLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/LegacyLegsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/LegacyLegsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdInstrumentDefinitionSpreadLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SecurityStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/GroupSize8Byte.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshBookOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshBookOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshBookLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshDailyStatisticsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshDailyStatisticsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshDailyStatisticsLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshLimitsBandingGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshLimitsBandingGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshLimitsBandingLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshSessionStatisticsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshSessionStatisticsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshSessionStatisticsLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshVolumeGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshVolumeGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshVolume.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/SnapshotFullRefreshGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/SnapshotFullRefreshGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SnapshotFullRefreshLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/RelatedSymGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/RelatedSymGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/QuoteRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/OptionUnderlyingsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/OptionUnderlyingsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/OptionRelatedInstrumentsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/OptionRelatedInstrumentsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdInstrumentDefinitionOptionLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshTradeSummaryGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshTradeSummaryGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshTradeSummaryOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshTradeSummaryOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshTradeSummaryLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/IncrementalRefreshOrderBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/IncrementalRefreshOrderBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshOrderBookLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/SnapshotFullRefreshOrderBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/SnapshotFullRefreshOrderBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SnapshotFullRefreshOrderBookLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshTradeSummary.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshLimitsBanding.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdIncrementalRefreshSessionStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SnapshotFullRefresh.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SnapshotFullRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdInstrumentDefinitionFuture.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdInstrumentDefinitionOption.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/LegsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/LegsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdInstrumentDefinitionSpread.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MktdataMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/Negotiate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/NegotiationReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/NegotiationResponse.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/Terminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/MarketDataRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/MarketDataRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/MarketDataRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/MarketDataRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MarketDataRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/RequestAckSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/RequestAckSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/RequestAckRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/RequestAckRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/RequestAck.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/RequestReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/SecurityListRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/SecurityListRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/SecurityListRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/SecurityListRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SecurityListRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/SecurityStatusRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/SecurityStatusRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/groups/SecurityStatusRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/SecurityStatusRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SecurityStatusRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/SubscriberHeartbeat.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/MdpsessionmgmtMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/ClientTechnicalHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ClientPayloadNegotiate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ClientPayloadTerminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ClientPayloadMarketDataRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ClientPayloadSecurityListRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ClientPayloadSecurityStatusRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/structs/ServerTechnicalHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadChannelReset.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadAdminLogin.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadAdminLogout.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdInstrumentDefinitionFutureLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdInstrumentDefinitionSpreadLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadSecurityStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshBookLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshDailyStatisticsLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshLimitsBandingLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshSessionStatisticsLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshVolume.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadSnapshotFullRefreshLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadQuoteRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdInstrumentDefinitionOptionLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshTradeSummaryLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshOrderBookLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadSnapshotFullRefreshOrderBookLegacy.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshTradeSummary.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshLimitsBanding.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdIncrementalRefreshSessionStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadSnapshotFullRefresh.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadSnapshotFullRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdInstrumentDefinitionFuture.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdInstrumentDefinitionOption.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadMdInstrumentDefinitionSpread.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadNegotiationReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadNegotiationResponse.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadTerminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadRequestAck.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/ServerPayloadRequestReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/UnknownMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/UnknownMktdataPayload.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/UnknownMdpsessionmgmtPayload.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/UnknownClientTcpMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/messages/UnknownServerTcpMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/Factory.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/UdpPacket.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/ClientTcpPacket.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.9/ServerTcpPacket.cpp
)
target_include_directories(classes_cme_globex_mdp3_sbe_v1.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_cme_globex_mdp3_sbe_v1.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_cme_globex_mdp3_sbe_v1.9 STATIC
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/TemplateId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/SchemaId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/SecurityUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdSecurityTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/EventType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/LegSide.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/SecurityTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/HaltReason.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/SecurityTradingEvent.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdEntryTypeBook.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/OrderUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdEntryTypeDailyStatistics.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdEntryTypeStatistics.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdEntryType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/PutOrCall.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/AggressorSide.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/ErrorCodes.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/SubscriptionReqType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdReqIdStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.9/enums/MdReqRejReason.cpp
)
target_include_directories(flyweight_cme_globex_mdp3_sbe_v1.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_cme_globex_mdp3_sbe_v1.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_cme_globex_mdp3_sbe_v1.13 STATIC
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/TemplateId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/SchemaId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/SecurityTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/HaltReason.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/SecurityTradingEvent.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdEntryTypeBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/OrderUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/AggressorSide.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdEntryTypeDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/OpenCloseSettlFlag.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdEntryTypeStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdSecurityTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdEntryType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/SecurityUpdateAction.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/EventType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/PutOrCall.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/LegSide.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/SecurityAltIdSource.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/RepoSubType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MoneyOrPar.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/UnderlyingSecurityAltIdSource.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/WorkupTradingStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/Side.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/AggressorIndicator.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdStreamId.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/ErrorCodes.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/SubscriptionReqType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdReqIdStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/enums/MdReqRejReason.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/BinaryPacketHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/MessageHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/bitfields/MatchEventIndicator.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/GroupSize.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/ChannelResetGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/ChannelResetGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ChannelReset.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/AdminHeartbeat.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/AdminLogin.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/AdminLogout.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SecurityStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshVolumeGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshVolumeGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshVolume.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/RelatedSymGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/RelatedSymGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/QuoteRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/GroupSize8Byte.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshBookOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshBookOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshOrderBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshOrderBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshTradeSummaryGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshTradeSummaryGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshTradeSummaryOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshTradeSummaryOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshTradeSummary.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/bitfields/SettlPriceType.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshDailyStatisticsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshDailyStatisticsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshLimitsBandingGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshLimitsBandingGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshLimitsBanding.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshSessionStatisticsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshSessionStatisticsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshSessionStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SnapshotFullRefreshGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SnapshotFullRefreshGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SnapshotFullRefresh.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SnapshotFullRefreshOrderBookGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SnapshotFullRefreshOrderBookGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SnapshotFullRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/MaturityMonthYear.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/EventsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/EventsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/FeedTypesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/FeedTypesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/bitfields/InstAttribValue.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/InstAttribGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/InstAttribGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/LotTypeRulesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/LotTypeRulesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdInstrumentDefinitionFuture.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/OptionUnderlyingsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/OptionUnderlyingsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/OptionRelatedInstrumentsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/OptionRelatedInstrumentsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdInstrumentDefinitionOption.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/LegsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/LegsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdInstrumentDefinitionSpread.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdInstrumentDefinitionFixedIncome.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/RepoUnderlyingsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/RepoUnderlyingsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/RepoRelatedInstrumentsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/RepoRelatedInstrumentsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/BrokenDatesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/BrokenDatesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdInstrumentDefinitionRepo.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SnapshotRefreshTopOrdersGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SnapshotRefreshTopOrdersGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SnapshotRefreshTopOrders.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SecurityStatusWorkupGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SecurityStatusWorkupGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SecurityStatusWorkup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SnapshotFullRefreshTcpGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SnapshotFullRefreshTcpGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SnapshotFullRefreshTcp.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/CollateralMarketValueGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/CollateralMarketValueGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/CollateralMarketValue.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/FxLotTypeRulesGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/FxLotTypeRulesGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/TradingSessionsGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/TradingSessionsGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdInstrumentDefinitionFx.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshBookLongGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshBookLongGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshBookLongOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshBookLongOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshBookLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshTradeSummaryLongGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshTradeSummaryLongGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshTradeSummaryLongOrderIdGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshTradeSummaryLongOrderIdGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshTradeSummaryLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshVolumeLongGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshVolumeLongGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshVolumeLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/IncrementalRefreshSessionStatisticsLongGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/IncrementalRefreshSessionStatisticsLongGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdIncrementalRefreshSessionStatisticsLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SnapshotfullRefreshTcpLongGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SnapshotfullRefreshTcpLongGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SnapshotFullRefreshTcpLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SnapshotFullRefreshLongGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SnapshotFullRefreshLongGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SnapshotFullRefreshLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MktdataMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/Negotiate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/NegotiationReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/NegotiationResponse.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/Terminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/MarketDataRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/MarketDataRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/MarketDataRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/MarketDataRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MarketDataRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/RequestAckSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/RequestAckSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/RequestAckRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/RequestAckRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/RequestAck.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/RequestReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SecurityListRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SecurityListRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SecurityListRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SecurityListRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SecurityListRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SecurityStatusRequestSecurityGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SecurityStatusRequestSecurityGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/groups/SecurityStatusRequestRelatedSymbolGroup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/SecurityStatusRequestRelatedSymbolGroups.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SecurityStatusRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/SubscriberHeartbeat.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/MdpsessionmgmtMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/ClientTechnicalHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ClientPayloadNegotiate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ClientPayloadTerminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ClientPayloadMarketDataRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ClientPayloadSecurityListRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ClientPayloadSecurityStatusRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/structs/ServerTechnicalHeader.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadChannelReset.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadAdminLogin.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadAdminLogout.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSecurityStatus.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshVolume.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadQuoteRequest.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshTradeSummary.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshDailyStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshLimitsBanding.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshSessionStatistics.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSnapshotFullRefresh.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSnapshotFullRefreshOrderBook.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdInstrumentDefinitionFuture.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdInstrumentDefinitionOption.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdInstrumentDefinitionSpread.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdInstrumentDefinitionFixedIncome.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdInstrumentDefinitionRepo.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSnapshotRefreshTopOrders.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSecurityStatusWorkup.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSnapshotFullRefreshTcp.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadCollateralMarketValue.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdInstrumentDefinitionFx.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshBookLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshTradeSummaryLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshVolumeLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadMdIncrementalRefreshSessionStatisticsLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSnapshotFullRefreshTcpLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadSnapshotFullRefreshLongQty.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadNegotiationReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadNegotiationResponse.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadTerminate.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadRequestAck.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/ServerPayloadRequestReject.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/UnknownMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/UnknownMktdataPayload.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/UnknownMdpsessionmgmtPayload.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/UnknownClientTcpMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/messages/UnknownServerTcpMessage.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/Factory.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/UdpPacket.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/ClientTcpPacket.cpp
  cpp/classes/cme/globex/mdp3/sbe/v1.13/ServerTcpPacket.cpp
)
target_include_directories(classes_cme_globex_mdp3_sbe_v1.13 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_cme_globex_mdp3_sbe_v1.13 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_cme_globex_mdp3_sbe_v1.13 STATIC
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/TemplateId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/SchemaId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/SecurityTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/HaltReason.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/SecurityTradingEvent.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdEntryTypeBook.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/OrderUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/AggressorSide.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdEntryTypeDailyStatistics.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/OpenCloseSettlFlag.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdEntryTypeStatistics.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdSecurityTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdEntryType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/SecurityUpdateAction.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/EventType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/PutOrCall.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/LegSide.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/SecurityAltIdSource.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/RepoSubType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MoneyOrPar.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/UnderlyingSecurityAltIdSource.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/WorkupTradingStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/Side.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/AggressorIndicator.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdStreamId.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/ErrorCodes.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/SubscriptionReqType.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdReqIdStatus.cpp
  cpp/flyweight/cme/globex/mdp3/sbe/v1.13/enums/MdReqRejReason.cpp
)
target_include_directories(flyweight_cme_globex_mdp3_sbe_v1.13 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_cme_globex_mdp3_sbe_v1.13 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_eurex_t7_eobi_fbe_v13.0 STATIC
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TemplateId.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/CompletionIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/ApplSeqResetIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/ProductComplex.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/ImpliedMarketIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/LastFragment.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/LegSecurityType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/LegSide.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/PutOrCall.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/ExerciseStyle.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SettlMethod.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/PotentialSecurityTradingEvent.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/BidOrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/OfferOrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityTradingStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/Side.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/CrossRequestType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/InputSource.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/AggressorSide.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TradeCondition.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/OrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/AlgorithmicTradeIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/HhiIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MarketCondition.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/FastMarketIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityTradingEvent.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SoldOutIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TesSecurityStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MdOriginType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MdEntryType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MultiLegReportingType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MultiLegPriceModel.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/InstrumentScopeProductComplex.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityMassStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityMassTradingStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MassMarketCondition.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/SecurityMassTradingEvent.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MassSoldOutIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TesSecurityMassStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/PrevPriceHhiIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TradingSessionId.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TradingSessionSubId.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TradSesStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/TesTradSesStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MatchType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/enums/MatchSubType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/structs/EobiHeader.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/structs/PacketHeader.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/structs/MessageHeaderComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/groups/InstrmtLegGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/AddComplexInstrument.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/AddFlexibleInstrument.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/structs/RelatedInstrumentGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/AddScaledSimpleInstrument.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/AuctionBbo.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/AuctionClearingPrice.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/CrossRequest.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/structs/RemainingOrderDetailsComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/ExecutionSummary.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/FullOrderExecution.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/Heartbeat.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/InstrumentStateChange.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/groups/MdInstrumentEntryGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/InstrumentSummary.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/groups/SecMassStatGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/MassInstrumentStateChange.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/structs/OrderDetailsComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/OrderAdd.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/OrderDelete.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/OrderMassDelete.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/OrderModify.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/OrderModifySamePrio.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/PartialOrderExecution.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/ProductStateChange.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/ProductSummary.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/QuoteRequest.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/SnapshotOrder.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/TesTradeReport.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/TopOfBook.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/TradeReport.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/groups/MdTradeEntryGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/TradeReversal.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/messages/UnknownMessage.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/Factory.cpp
  cpp/classes/eurex/t7/eobi/fbe/v13.0/Packet.cpp
)
target_include_directories(classes_eurex_t7_eobi_fbe_v13.0 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_eurex_t7_eobi_fbe_v13.0 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_eurex_t7_eobi_fbe_v13.0 STATIC
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TemplateId.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/CompletionIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/ApplSeqResetIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/ProductComplex.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/ImpliedMarketIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/LastFragment.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/LegSecurityType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/LegSide.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/PutOrCall.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/ExerciseStyle.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SettlMethod.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/PotentialSecurityTradingEvent.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/BidOrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/OfferOrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityTradingStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/Side.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/CrossRequestType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/InputSource.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/AggressorSide.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TradeCondition.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/OrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/AlgorithmicTradeIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/HhiIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MarketCondition.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/FastMarketIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityTradingEvent.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SoldOutIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TesSecurityStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MdOriginType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MdEntryType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MultiLegReportingType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MultiLegPriceModel.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/InstrumentScopeProductComplex.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityMassStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityMassTradingStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MassMarketCondition.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/SecurityMassTradingEvent.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MassSoldOutIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TesSecurityMassStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/PrevPriceHhiIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TradingSessionId.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TradingSessionSubId.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TradSesStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/TesTradSesStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MatchType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v13.0/enums/MatchSubType.cpp
)
target_include_directories(flyweight_eurex_t7_eobi_fbe_v13.0 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_eurex_t7_eobi_fbe_v13.0 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_eurex_t7_eobi_fbe_v15.0 STATIC
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TemplateId.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/CompletionIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/ApplSeqResetIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/ProductComplex.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/ImpliedMarketIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/LastFragment.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/LegSecurityType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/LegSide.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/RelatedPriceType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TradingStyle.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/PutOrCall.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/ExerciseStyle.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SettlMethod.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/PotentialSecurityTradingEvent.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/BidOrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/OfferOrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityTradingStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/Side.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/CrossRequestType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/InputSource.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/AggressorSide.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TradeCondition.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/OrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/AlgorithmicTradeIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/HhiIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MarketCondition.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/FastMarketIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityTradingEvent.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SoldOutIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TesSecurityStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MdOriginType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MdEntryType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TrdType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MultiLegReportingType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MultiLegPriceModel.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/InstrumentScopeProductComplex.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityMassStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityMassTradingStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MassMarketCondition.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/SecurityMassTradingEvent.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MassSoldOutIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TesSecurityMassStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/PrevPriceHhiIndicator.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TradingSessionId.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TradingSessionSubId.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TradSesStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/TesTradSesStatus.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MatchType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/enums/MatchSubType.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/structs/EobiHeader.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/structs/PacketHeader.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/structs/MessageHeaderComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/groups/InstrmtLegGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/AddComplexInstrument.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/AddFlexibleInstrument.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/structs/RelatedInstrumentGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/AddScaledSimpleInstrument.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/AuctionBbo.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/AuctionClearingPrice.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/CrossRequest.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/structs/RemainingOrderDetailsComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/ExecutionSummary.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/FullOrderExecution.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/Heartbeat.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/InstrumentStateChange.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/groups/MdInstrumentEntryGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/InstrumentSummary.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/groups/SecMassStatGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/MassInstrumentStateChange.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/structs/OrderDetailsComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/OrderAdd.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/OrderDelete.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/OrderMassDelete.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/OrderModify.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/OrderModifySamePrio.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/PartialOrderExecution.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/ProductStateChange.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/ProductSummary.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/QuoteRequest.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/SnapshotOrder.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/TesTradeReport.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/TopOfBook.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/TradeReport.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/groups/MdTradeEntryGrpComp.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/TradeReversal.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/messages/UnknownMessage.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/Factory.cpp
  cpp/classes/eurex/t7/eobi/fbe/v15.0/Packet.cpp
)
target_include_directories(classes_eurex_t7_eobi_fbe_v15.0 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_eurex_t7_eobi_fbe_v15.0 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_eurex_t7_eobi_fbe_v15.0 STATIC
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TemplateId.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/CompletionIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/ApplSeqResetIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/ProductComplex.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/ImpliedMarketIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/LastFragment.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/LegSecurityType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/LegSide.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/RelatedPriceType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TradingStyle.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/PutOrCall.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/ExerciseStyle.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SettlMethod.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/PotentialSecurityTradingEvent.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/BidOrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/OfferOrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityTradingStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/Side.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/CrossRequestType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/InputSource.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/AggressorSide.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TradeCondition.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/OrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/AlgorithmicTradeIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/HhiIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MarketCondition.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/FastMarketIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityTradingEvent.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SoldOutIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TesSecurityStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MdOriginType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MdEntryType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TrdType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MultiLegReportingType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MultiLegPriceModel.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/InstrumentScopeProductComplex.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityMassStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityMassTradingStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MassMarketCondition.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/SecurityMassTradingEvent.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MassSoldOutIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TesSecurityMassStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/PrevPriceHhiIndicator.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TradingSessionId.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TradingSessionSubId.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TradSesStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/TesTradSesStatus.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MatchType.cpp
  cpp/flyweight/eurex/t7/eobi/fbe/v15.0/enums/MatchSubType.cpp
)
target_include_directories(flyweight_eurex_t7_eobi_fbe_v15.0 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_eurex_t7_eobi_fbe_v15.0 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deep_iextp_v1.06 STATIC
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/Factory.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deep_iextp_v1.06 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_deep_iextp_v1.06 STATIC
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/EventFlags.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/PriceType.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/AuctionType.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.06/enums/ImbalanceSide.cpp
)
target_include_directories(flyweight_iex_iexequities_deep_iextp_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_deep_iextp_v1.06 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deep_iextp_v1.08 STATIC
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/Factory.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.08 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deep_iextp_v1.08 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_deep_iextp_v1.08 STATIC
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/EventFlags.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/PriceType.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/AuctionType.cpp
  cpp/flyweight/iex/iexequities/deep/iextp/v1.08/enums/ImbalanceSide.cpp
)
target_include_directories(flyweight_iex_iexequities_deep_iextp_v1.08 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_deep_iextp_v1.08 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deep_snap_v1.6 STATIC
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/Factory.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/Stream.cpp
)
target_include_directories(classes_iex_iexequities_deep_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deep_snap_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_deep_snap_v1.6 STATIC
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/EventFlags.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/PriceType.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/AuctionType.cpp
  cpp/flyweight/iex/iexequities/deep/snap/v1.6/enums/ImbalanceSide.cpp
)
target_include_directories(flyweight_iex_iexequities_deep_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_deep_snap_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deepplus_iextp_v1.01 STATIC
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.01 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deepplus_iextp_v1.01 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_deepplus_iextp_v1.01 STATIC
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.01/enums/Side.cpp
)
target_include_directories(flyweight_iex_iexequities_deepplus_iextp_v1.01 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_deepplus_iextp_v1.01 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deepplus_iextp_v1.05 STATIC
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.05 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deepplus_iextp_v1.05 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_deepplus_iextp_v1.05 STATIC
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/deepplus/iextp/v1.05/enums/Side.cpp
)
target_include_directories(flyweight_iex_iexequities_deepplus_iextp_v1.05 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_deepplus_iextp_v1.05 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deepplus_snap_v1.06 STATIC
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/Stream.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_snap_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deepplus_snap_v1.06 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_deepplus_snap_v1.06 STATIC
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/RejectReasonCode.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/IexTpMessageType.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/deepplus/snap/v1.06/enums/Side.cpp
)
target_include_directories(flyweight_iex_iexequities_deepplus_snap_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_deepplus_snap_v1.06 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_iextp_v1.56 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.56 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_iextp_v1.56 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_tops_iextp_v1.56 STATIC
  cpp/flyweight/iex/iexequities/tops/iextp/v1.56/enums/MessageType.cpp
)
target_include_directories(flyweight_iex_iexequities_tops_iextp_v1.56 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_tops_iextp_v1.56 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_iextp_v1.64 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.64 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_iextp_v1.64 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_tops_iextp_v1.64 STATIC
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/SecurityEvent.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/PriceType.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/AuctionType.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.64/enums/ImbalanceSide.cpp
)
target_include_directories(flyweight_iex_iexequities_tops_iextp_v1.64 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_tops_iextp_v1.64 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_iextp_v1.66 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.66 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_iextp_v1.66 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_tops_iextp_v1.66 STATIC
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/PriceType.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/AuctionType.cpp
  cpp/flyweight/iex/iexequities/tops/iextp/v1.66/enums/ImbalanceSide.cpp
)
target_include_directories(flyweight_iex_iexequities_tops_iextp_v1.66 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_tops_iextp_v1.66 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_snap_v1.6 STATIC
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/Factory.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/Stream.cpp
)
target_include_directories(classes_iex_iexequities_tops_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_snap_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_iex_iexequities_tops_snap_v1.6 STATIC
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/MessageType.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/SystemEvent.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/LuldTier.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/TradingStatus.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/Detail.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/PriceType.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/AuctionType.cpp
  cpp/flyweight/iex/iexequities/tops/snap/v1.6/enums/ImbalanceSide.cpp
)
target_include_directories(flyweight_iex_iexequities_tops_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_iex_iexequities_tops_snap_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_jpx_osederivatives_geniuminet_itch_v5.0.6 STATIC
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/MessageType.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/FinancialProduct.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/PutOrCall.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/LegSide.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/EventCode.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/Side.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/LotType.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/OccurredAtCross.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/Printable.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/structs/PacketHeader.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/structs/MessageHeader.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/SecondsMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/OrderBookDirectory.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/CombinationOrderbookLeg.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/TickSizeTableEntry.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/SystemEventMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/OrderBookStateMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/bitfields/OrderAttributes.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/AddOrderNoMpid.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/AddOrderWithMpid.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/OrderExecutedMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/OrderReplaceMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/OrderDeleteMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/TradeMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/EquilibriumPriceUpdate.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/UnknownMessage.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/Factory.cpp
  cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/Packet.cpp
)
target_include_directories(classes_jpx_osederivatives_geniuminet_itch_v5.0.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_jpx_osederivatives_geniuminet_itch_v5.0.6 STATIC
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/MessageType.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/FinancialProduct.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/PutOrCall.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/LegSide.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/EventCode.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/Side.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/LotType.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/OccurredAtCross.cpp
  cpp/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/enums/Printable.cpp
)
target_include_directories(flyweight_jpx_osederivatives_geniuminet_itch_v5.0.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_jpx_tseequities_marketbyorder_flex_v1.1 STATIC
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/MessageType.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/MarketStatus.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ShortSellingStatus.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/PricingMethod.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/TriggeredSide.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/Side.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/OrderCondition.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ModificationFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/AdoptedPricingMethod.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ResetStartEndFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/TestModeFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/CommunicationStartEndFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/PacketType.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ResultCode.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/structs/PacketHeader.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/structs/MessageHeader.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/SecondsTimestampMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/TradingStatusMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/ExecutionSummaryMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/AddOrderMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/OrderExecutedMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/OrderDeleteMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/ResetMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/CommunicationControlMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/structs/TcpPacketHeader.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/LoginRequestRetransmissionMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/LoginRequestSnapshotMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/LoginResultAcceptedMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/LoginResultRejectedMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/MessageResponseMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/EndOfMessageMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/UnknownMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/UnknownTcpMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/Factory.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/UdpPacket.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/TcpPacket.cpp
)
target_include_directories(classes_jpx_tseequities_marketbyorder_flex_v1.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_jpx_tseequities_marketbyorder_flex_v1.1 STATIC
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/MessageType.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/MarketStatus.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/ShortSellingStatus.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/PricingMethod.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/TriggeredSide.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/Side.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/OrderCondition.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/ModificationFlag.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/AdoptedPricingMethod.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/ResetStartEndFlag.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/TestModeFlag.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/CommunicationStartEndFlag.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/PacketType.cpp
  cpp/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/enums/ResultCode.cpp
)
target_include_directories(flyweight_jpx_tseequities_marketbyorder_flex_v1.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_lseg_lse_level2mbo_gtp_v26.2 STATIC
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/MessageType.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/EventCode.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/SourceVenue.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/TradingStatus.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/SessionChangeReason.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/OrderBookType.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/Side.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/TradeType.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/AuctionType.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/HiddenExecutionIndicator.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/TradeQualifier.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/StatisticType.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/AuctionInfo.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/enums/OpeningClosingPriceIndicator.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/structs/UnitHeader.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/structs/MessageHeader.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/SystemEventMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/bitfields/AllowedBookTypes.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/InstrumentDirectoryMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/InstrumentStatusMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/AddOrderMboMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/AddOrderShortMboMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/OrderBookClearMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/bitfields/TradeFlags.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/TradeMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/StatisticsMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/StatisticsUpdateMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/messages/UnknownMessage.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/Factory.cpp
  cpp/classes/lseg/lse/level2mbo/gtp/v26.2/Packet.cpp
)
target_include_directories(classes_lseg_lse_level2mbo_gtp_v26.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_lseg_lse_level2mbo_gtp_v26.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_lseg_lse_level2mbo_gtp_v26.2 STATIC
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/MessageType.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/EventCode.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/SourceVenue.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/TradingStatus.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/SessionChangeReason.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/OrderBookType.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/Side.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/TradeType.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/AuctionType.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/HiddenExecutionIndicator.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/TradeQualifier.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/StatisticType.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/AuctionInfo.cpp
  cpp/flyweight/lseg/lse/level2mbo/gtp/v26.2/enums/OpeningClosingPriceIndicator.cpp
)
target_include_directories(flyweight_lseg_lse_level2mbo_gtp_v26.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_lseg_lse_level2mbo_gtp_v26.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_lseg_millennium_level2_mitch_v11.9 STATIC
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/MessageType.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/EventCode.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/SymbolStatus.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/TradingStatus.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/SessionChangeReason.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/BookType.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/Side.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/Printable.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/CrossType.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/SubBook.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/AuctionType.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/StatisticType.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/enums/OpenClosePriceIndicator.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/structs/UnitHeader.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/structs/MessageHeader.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/TimeMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/SystemEventMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/SymbolDirectoryMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/SymbolStatusFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/SymbolStatusMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/AddOrderFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/AddOrderMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/AddAttributedOrderFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/AddAttributedOrderMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/OrderDeletedFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/OrderDeletedMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/OrderModifiedFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/OrderModifiedMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/OrderBookClearFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/OrderBookClearMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/OrderExecutedMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/OrderExecutedWithPriceSizeMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/PtModFlags.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/TradeMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/AuctionTradeMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/AuctionInfoMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/bitfields/StatisticsReserved.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/StatisticsMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/TopOfBookMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/messages/UnknownMessage.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/Factory.cpp
  cpp/classes/lseg/millennium/level2/mitch/v11.9/Packet.cpp
)
target_include_directories(classes_lseg_millennium_level2_mitch_v11.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_lseg_millennium_level2_mitch_v11.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_lseg_millennium_level2_mitch_v11.9 STATIC
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/MessageType.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/EventCode.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/SymbolStatus.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/TradingStatus.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/SessionChangeReason.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/BookType.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/Side.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/Printable.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/CrossType.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/SubBook.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/AuctionType.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/StatisticType.cpp
  cpp/flyweight/lseg/millennium/level2/mitch/v11.9/enums/OpenClosePriceIndicator.cpp
)
target_include_directories(flyweight_lseg_millennium_level2_mitch_v11.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_lseg_millennium_level2_mitch_v11.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_memx_memxequities_memoirdepthfeed_sbe_v1.3 STATIC
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/MessageType.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/TemplateId.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/IsTestSymbol.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/ShortSaleRestriction.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/SecurityTradingStatus.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/SecurityTradingStatusReason.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/TradingSession.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/Side.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/structs/CommonHeader.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/structs/SbeHeader.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/InstrumentDirectoryMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/RegShoRestrictionMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/SecurityTradingStatusMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/TradingSessionStatusMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/OrderAddedMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/OrderDeletedMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/OrderReducedMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/OrderExecutedMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/TradeMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/BrokenTradeMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/CorrectedTradeMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/ClearBookMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/SnapshotCompleteMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/structs/SbeMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/groups/SequencedMessageMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/SequencedMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/UnknownMessage.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/UnknownPayload.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/Factory.cpp
  cpp/classes/memx/memxequities/memoirdepthfeed/sbe/v1.3/Packet.cpp
)
target_include_directories(classes_memx_memxequities_memoirdepthfeed_sbe_v1.3 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_memx_memxequities_memoirdepthfeed_sbe_v1.3 STATIC
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/MessageType.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/TemplateId.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/IsTestSymbol.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/ShortSaleRestriction.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/SecurityTradingStatus.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/SecurityTradingStatusReason.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/TradingSession.cpp
  cpp/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/enums/Side.cpp
)
target_include_directories(flyweight_memx_memxequities_memoirdepthfeed_sbe_v1.3 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nsmequities_totalview_itch_v5.0.2017 STATIC
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ClientPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ServerPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/RejectReasonCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/EventCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MarketCategory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/FinancialStatusIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/RoundLotsOnly.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/IssueClassification.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/Authenticity.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ShortSaleThresholdIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/IpoFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/LuldReferencePriceTier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/EtpFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/InverseIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/TradingState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/RegShoAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/PrimaryMarketMaker.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MarketMakerMode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MarketParticipantState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/BreachedLevel.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/IpoQuotationReleaseQualifier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/BuySellIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/Printable.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/CrossType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ImbalanceDirection.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/PriceVariationIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/InterestFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MessageType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/structs/ClientPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/DebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/LoginRequestPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/UnsequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/structs/ServerPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/ServerPayloadDebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/LoginAcceptedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/LoginRejectedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/StockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/StockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/MarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/MwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/MwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/IpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/LuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/AddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/AddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/OrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/OrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/OrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/OrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/NonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/CrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/BrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/NetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/RetailInterestMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/SequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadSystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadStockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadStockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadMarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadMwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadMwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadIpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadLuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadAddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadAddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadOrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadOrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadOrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadOrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadOrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadNonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadBrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadNetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/PayloadRetailInterestMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/UnknownServerMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/UnknownSequencedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/messages/UnknownPacketMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/Factory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/ClientPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/ServerPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2017/Packet.cpp
)
target_include_directories(classes_nasdaq_nsmequities_totalview_itch_v5.0.2017 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2017 STATIC
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ClientPacketType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ServerPacketType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/RejectReasonCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/EventCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MarketCategory.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/FinancialStatusIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/RoundLotsOnly.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/IssueClassification.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/Authenticity.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ShortSaleThresholdIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/IpoFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/LuldReferencePriceTier.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/EtpFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/InverseIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/TradingState.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/RegShoAction.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/PrimaryMarketMaker.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MarketMakerMode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MarketParticipantState.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/BreachedLevel.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/IpoQuotationReleaseQualifier.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/BuySellIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/Printable.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/CrossType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/ImbalanceDirection.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/PriceVariationIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/InterestFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2017/enums/MessageType.cpp
)
target_include_directories(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2017 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 STATIC
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ClientPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ServerPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RejectReasonCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/EventCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketCategory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/FinancialStatusIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RoundLotsOnly.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IssueClassification.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/Authenticity.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ShortSaleThresholdIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IpoFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/LuldReferencePriceTier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/EtpFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/InverseIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/TradingState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RegShoAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/PrimaryMarketMaker.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketMakerMode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketParticipantState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/BreachedLevel.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IpoQuotationReleaseQualifier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/OperationalHaltAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/BuySellIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/Printable.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/CrossType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ImbalanceDirection.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/PriceVariationIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/InterestFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/OpenEligibilityStatus.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MessageType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/ClientPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/DebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LoginRequestPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnsequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/ServerPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/ServerPayloadDebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LoginAcceptedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LoginRejectedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/StockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/StockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/MarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/MwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/MwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/IpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/AddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/AddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/NonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/CrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/BrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/NetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/RetailPriceImprovementIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/DirectListingWithCapitalRaisePriceDiscoveryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/SequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadSystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadStockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadStockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadMarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadMwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadMwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadIpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadLuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadAddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadAddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadNonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadBrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadNetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadRetailPriceImprovementIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownServerMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownSequencedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownPacketMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/Factory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/ClientPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/ServerPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/Packet.cpp
)
target_include_directories(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2023 STATIC
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ClientPacketType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ServerPacketType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RejectReasonCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/EventCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketCategory.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/FinancialStatusIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RoundLotsOnly.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IssueClassification.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/Authenticity.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ShortSaleThresholdIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IpoFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/LuldReferencePriceTier.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/EtpFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/InverseIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/TradingState.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RegShoAction.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/PrimaryMarketMaker.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketMakerMode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketParticipantState.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/BreachedLevel.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IpoQuotationReleaseQualifier.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/OperationalHaltAction.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/BuySellIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/Printable.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/CrossType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ImbalanceDirection.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/PriceVariationIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/InterestFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/OpenEligibilityStatus.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MessageType.cpp
)
target_include_directories(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2023 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nsmequities_totalview_itch_v5.0.2026 STATIC
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ClientPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ServerPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/RejectReasonCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/SequencedMessageType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/EventCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketCategory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/FinancialStatusIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/RoundLotsOnly.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/IssueClassification.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/Authenticity.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ShortSaleThresholdIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/IpoFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/LuldReferencePriceTier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/EtpFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/InverseIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/TradingState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/RegShoAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/PrimaryMarketMaker.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketMakerMode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketParticipantState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/BreachedLevel.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/IpoQuotationReleaseQualifier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/OperationalHaltAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/BuySellIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/Printable.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/CrossType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ImbalanceDirection.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/PriceVariationIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/InterestFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/OpenEligibilityStatus.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MessageType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/structs/ClientPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/DebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/LoginRequestPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/UnsequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/structs/ServerPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/ServerPayloadDebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/LoginAcceptedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/LoginRejectedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/StockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/StockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/MarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/MwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/MwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/IpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/LuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/OperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/AddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/AddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/OrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/OrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/OrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/OrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/NonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/CrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/BrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/NetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/RetailPriceImprovementIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/DirectListingWithCapitalRaisePriceDiscoveryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/SequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadSystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadStockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadStockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadMarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadMwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadMwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadIpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadLuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadOperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadAddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadAddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadOrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadOrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadOrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadOrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadOrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadNonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadBrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadNetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadRetailPriceImprovementIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/UnknownServerMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/UnknownSequencedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/messages/UnknownPacketMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/Factory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/ClientPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/ServerPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2026/Packet.cpp
)
target_include_directories(classes_nasdaq_nsmequities_totalview_itch_v5.0.2026 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2026 STATIC
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ClientPacketType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ServerPacketType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/RejectReasonCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/SequencedMessageType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/EventCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketCategory.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/FinancialStatusIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/RoundLotsOnly.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/IssueClassification.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/Authenticity.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ShortSaleThresholdIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/IpoFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/LuldReferencePriceTier.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/EtpFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/InverseIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/TradingState.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/RegShoAction.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/PrimaryMarketMaker.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketMakerMode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketParticipantState.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/BreachedLevel.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/IpoQuotationReleaseQualifier.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MarketCode.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/OperationalHaltAction.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/BuySellIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/Printable.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/CrossType.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/ImbalanceDirection.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/PriceVariationIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/InterestFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/OpenEligibilityStatus.cpp
  cpp/flyweight/nasdaq/nsmequities/totalview/itch/v5.0.2026/enums/MessageType.cpp
)
target_include_directories(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2026 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nsmequities_qbbo_itch_v2.1 STATIC
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/MessageType.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/EventCode.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/MarketCategory.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/FinancialStatusIndicator.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/RoundLotsOnly.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/IssueClassification.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/Authenticity.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/ShortSaleThresholdIndicator.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/IpoFlag.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/LuldReferencePriceTier.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/EtpFlag.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/InverseIndicator.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/SecurityClass.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/CurrentTradingState.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/RegShoAction.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/BreachedLevel.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/MarketCode.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/OperationalHaltAction.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/InterestFlag.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/enums/IpoQuotationReleaseQualifier.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/StockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/StockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/RegShoRestrictionMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/MwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/MwcbBreachMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/OperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/BboQuotationMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/PriceImprovementMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/IpoQuotingPeriodUpdateMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/Factory.cpp
  cpp/classes/nasdaq/nsmequities/qbbo/itch/v2.1/Packet.cpp
)
target_include_directories(classes_nasdaq_nsmequities_qbbo_itch_v2.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_nsmequities_qbbo_itch_v2.1 STATIC
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/MessageType.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/EventCode.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/MarketCategory.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/FinancialStatusIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/RoundLotsOnly.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/IssueClassification.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/Authenticity.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/ShortSaleThresholdIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/IpoFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/LuldReferencePriceTier.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/EtpFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/InverseIndicator.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/SecurityClass.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/CurrentTradingState.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/RegShoAction.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/BreachedLevel.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/MarketCode.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/OperationalHaltAction.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/InterestFlag.cpp
  cpp/flyweight/nasdaq/nsmequities/qbbo/itch/v2.1/enums/IpoQuotationReleaseQualifier.cpp
)
target_include_directories(flyweight_nasdaq_nsmequities_qbbo_itch_v2.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nomoptions_itto_itch_v4.0.2025 STATIC
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ClientPacketType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ServerPacketType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/RejectReasonCode.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/SequencedMessageType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/EventCode.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/OptionType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/OptionsClosingType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/Tradable.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/Mpv.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/CurrentTradingState.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/OpenState.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/MarketSide.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/Printable.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ChangeReason.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/BuySellIndicator.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/CrossType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/AuctionType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ImbalanceDirection.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/CustomerFirmIndicator.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/MessageType.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/structs/ClientPacketHeader.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/DebugPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/LoginRequestPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UnsequencedDataPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/structs/ServerPacketHeader.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/ServerPayloadDebugPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/LoginAcceptedPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/LoginRejectedPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/OptionsDirectoryMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/TradingActionMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SecurityOpenMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/AddOrderMessageShortMessageForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/AddOrderMessageLongFormMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/AddQuoteMessageShortFormMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/AddQuoteMessageLongFormMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SingleSideExecutedMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SingleSideExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/OrderCancelMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SingleSideReplaceMessageShortForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SingleSideReplaceMessageLongForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SingleSideDeleteMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SingleSideChangeMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/QuoteReplaceMessageShortForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/QuoteReplaceMessageLongForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/QuoteDeleteMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/OptionsTradeMessagesNonAuction.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/OptionsCrossTradeMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/BrokenTradeOrderExecutedMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/NoiiMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/EndOfReplaySequenceMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/SequencedDataPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSystemEventMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadOptionsDirectoryMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadTradingActionMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSecurityOpenMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadAddOrderMessageShortMessageForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadAddOrderMessageLongFormMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadAddQuoteMessageShortFormMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadAddQuoteMessageLongFormMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSingleSideExecutedMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSingleSideExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadOrderCancelMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSingleSideReplaceMessageShortForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSingleSideReplaceMessageLongForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSingleSideDeleteMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadSingleSideChangeMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadQuoteReplaceMessageShortForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadQuoteReplaceMessageLongForm.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadQuoteDeleteMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadOptionsTradeMessagesNonAuction.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadOptionsCrossTradeMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadBrokenTradeOrderExecutedMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UdpPayloadNoiiMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UnknownServerMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UnknownSequencedMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/UnknownPacketMessage.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/Factory.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/ClientPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/ServerPacket.cpp
  cpp/classes/nasdaq/nomoptions/itto/itch/v4.0.2025/Packet.cpp
)
target_include_directories(classes_nasdaq_nomoptions_itto_itch_v4.0.2025 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_nomoptions_itto_itch_v4.0.2025 STATIC
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ClientPacketType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ServerPacketType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/RejectReasonCode.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/SequencedMessageType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/EventCode.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/OptionType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/OptionsClosingType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/Tradable.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/Mpv.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/CurrentTradingState.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/OpenState.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/MarketSide.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/Printable.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ChangeReason.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/BuySellIndicator.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/CrossType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/AuctionType.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/ImbalanceDirection.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/CustomerFirmIndicator.cpp
  cpp/flyweight/nasdaq/nomoptions/itto/itch/v4.0.2025/enums/MessageType.cpp
)
target_include_directories(flyweight_nasdaq_nomoptions_itto_itch_v4.0.2025 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_phlxoptions_topofmarket_itch_v3.4 STATIC
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/ClientPacketType.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/ServerPacketType.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/RejectReasonCode.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/SequencedMessageType.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/EventCode.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/OptionType.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/OptionClosingType.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/Tradable.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/Mpv.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/CurrentTradingState.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/OpenState.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/QuoteCondition.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/MessageType.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/structs/ClientPacketHeader.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/DebugPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/LoginRequestPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/UnsequencedDataPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/structs/ServerPacketHeader.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/ServerPayloadDebugPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/LoginAcceptedPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/LoginRejectedPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/TimestampMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/OptionsDirectoryMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/TradingActionMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/SecurityOpenClosedMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/ShortBestBidAndAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/LongBestBidAndAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/ShortBestAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/ShortBestBidUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/LongBestAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/LongBestBidUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/TradeReportMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/BrokenTradeReportMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/EndOfReplaySequenceMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/SequencedDataPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/structs/PacketHeader.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/structs/MessageHeader.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadTimestampMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadSystemEventMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadOptionsDirectoryMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadTradingActionMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadSecurityOpenClosedMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadShortBestBidAndAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadLongBestBidAndAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadShortBestAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadShortBestBidUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadLongBestAskUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadLongBestBidUpdateMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadTradeReportMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/PayloadBrokenTradeReportMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/UnknownServerMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/UnknownSequencedMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/UnknownPacketMessage.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/Factory.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/ClientPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/ServerPacket.cpp
  cpp/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/Packet.cpp
)
target_include_directories(classes_nasdaq_phlxoptions_topofmarket_itch_v3.4 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_phlxoptions_topofmarket_itch_v3.4 STATIC
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/ClientPacketType.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/ServerPacketType.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/RejectReasonCode.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/SequencedMessageType.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/EventCode.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/OptionType.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/OptionClosingType.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/Tradable.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/Mpv.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/CurrentTradingState.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/OpenState.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/QuoteCondition.cpp
  cpp/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/enums/MessageType.cpp
)
target_include_directories(flyweight_nasdaq_phlxoptions_topofmarket_itch_v3.4 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nordicequities_totalview_itch_v3.04.x STATIC
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/MessageType.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/EventCode.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/SymbolState.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/Extension.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/FinancialProduct.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/PriceNotation.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/BuySellIndicator.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/Printable.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/TradeType.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/CrossType.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/ImbalanceDirection.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/CrossLevel.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/AggressingSide.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderBookTradingActionMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField1.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField2.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField3.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField4.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField5.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField6.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField7.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/bitfields/NoteCodesBitField8.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderBookDirectoryMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/AddOrderMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/AddOrderMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderExecutedMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderCancelMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderDeleteMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderBookFlushMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/OrderReplaceMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/TradeMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/CrossTradeMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/BrokenTradeMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/NoiiMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/MoiiMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/ExecutionSummaryMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/Factory.cpp
  cpp/classes/nasdaq/nordicequities/totalview/itch/v3.04.x/Packet.cpp
)
target_include_directories(classes_nasdaq_nordicequities_totalview_itch_v3.04.x PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nasdaq_nordicequities_totalview_itch_v3.04.x STATIC
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/MessageType.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/EventCode.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/SymbolState.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/Extension.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/FinancialProduct.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/PriceNotation.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/BuySellIndicator.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/Printable.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/TradeType.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/CrossType.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/ImbalanceDirection.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/CrossLevel.cpp
  cpp/flyweight/nasdaq/nordicequities/totalview/itch/v3.04.x/enums/AggressingSide.cpp
)
target_include_directories(flyweight_nasdaq_nordicequities_totalview_itch_v3.04.x PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nyse_arcaequities_integratedfeed_pillar_v2.5.g STATIC
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/DeliveryFlag.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/MessageType.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/MarketId.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/ExchangeCode.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SecurityType.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/PriceResolution.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/RoundLot.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SecurityStatus.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/HaltCondition.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SsrTriggeringExchangeId.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SsrState.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/MarketState.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/Side.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/PrintableFlag.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond1.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond2.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond3.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond4.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/AuctionType.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/ImbalanceSide.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/AuctionStatus.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/FreezeStatus.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/UnpairedSide.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/CrossType.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/RpiIndicator.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/structs/SendTime.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/structs/PacketHeader.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/structs/MessageHeader.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/SequenceNumberResetMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/SourceTimeReferenceMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/SymbolIndexMappingMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/SymbolClearMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/SecurityStatusMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/AddOrderMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/ModifyOrderMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/DeleteOrderMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/OrderExecutionMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/ReplaceOrderMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/ImbalanceMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/AddOrderRefreshMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/NonDisplayedTradeMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/CrossTradeMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/TradeCancelMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/CrossCorrectionMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/RetailPriceImprovementMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/UnknownMessage.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/Factory.cpp
  cpp/classes/nyse/arcaequities/integratedfeed/pillar/v2.5.g/Packet.cpp
)
target_include_directories(classes_nyse_arcaequities_integratedfeed_pillar_v2.5.g PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nyse_arcaequities_integratedfeed_pillar_v2.5.g STATIC
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/DeliveryFlag.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/MessageType.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/MarketId.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/ExchangeCode.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SecurityType.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/PriceResolution.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/RoundLot.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SecurityStatus.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/HaltCondition.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SsrTriggeringExchangeId.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/SsrState.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/MarketState.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/Side.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/PrintableFlag.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond1.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond2.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond3.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/TradeCond4.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/AuctionType.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/ImbalanceSide.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/AuctionStatus.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/FreezeStatus.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/UnpairedSide.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/CrossType.cpp
  cpp/flyweight/nyse/arcaequities/integratedfeed/pillar/v2.5.g/enums/RpiIndicator.cpp
)
target_include_directories(flyweight_nyse_arcaequities_integratedfeed_pillar_v2.5.g PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nyse_arcaoptions_deepfeed_pillar_v1.2.m STATIC
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/DeliveryFlag.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/MessageType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/MarketId.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/ExchangeCode.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PriceScaleCode.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SecurityType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PriceResolution.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RoundLot.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SecurityStatus.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/HaltCondition.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SsrTriggeringExchangeId.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SsrState.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/MarketState.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SeriesType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PutOrCall.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/ClosingOnlyIndicator.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SeriesStatus.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/OptionsStatusHaltCondition.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/LegSide.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/LegSecurityType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RetransmitMethod.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Status.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Side.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/CustIndicator.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PrintableFlag.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/TradeCond1.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/AuctionType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/ImbalanceSide.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/AuctionStatus.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RfqSide.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Type.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Capacity.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RfqStatus.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/NonDisplayedTradeTradeCond1.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PriceType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/CrossType.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/structs/SendTime.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/structs/PacketHeader.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/structs/MessageHeader.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/SequenceNumberResetMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/SourceTimeReferenceMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/SymbolIndexMappingMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/SymbolClearMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/SecurityStatusMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OutrightSeriesIndexMappingMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsStatusMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/groups/ComplexSeriesIndexMappingLeg.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/ComplexSeriesIndexMappingMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/RetransmissionRequestMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/structs/FullRefreshHeader.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/RefreshHeaderMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/RefreshRequestMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/SymbolIndexMappingRequestMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/MessageUnavailableMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/RequestResponseMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/HeartbeatResponseMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsAddOrderMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsModifyOrderMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsDeleteOrderMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsOrderExecutionMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsReplaceOrderMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsImbalanceMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsAddOrderRefreshMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsSeriesRfqMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsNonDisplayedTradeMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsCrossTradeMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsTradeCancelMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/OptionsOutrightSeriesSummaryMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/messages/UnknownMessage.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/Factory.cpp
  cpp/classes/nyse/arcaoptions/deepfeed/pillar/v1.2.m/Packet.cpp
)
target_include_directories(classes_nyse_arcaoptions_deepfeed_pillar_v1.2.m PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nyse_arcaoptions_deepfeed_pillar_v1.2.m STATIC
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/DeliveryFlag.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/MessageType.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/MarketId.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/ExchangeCode.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PriceScaleCode.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SecurityType.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PriceResolution.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RoundLot.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SecurityStatus.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/HaltCondition.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SsrTriggeringExchangeId.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SsrState.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/MarketState.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SeriesType.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PutOrCall.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/ClosingOnlyIndicator.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/SeriesStatus.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/OptionsStatusHaltCondition.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/LegSide.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/LegSecurityType.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RetransmitMethod.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Status.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Side.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/CustIndicator.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PrintableFlag.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/TradeCond1.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/AuctionType.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/ImbalanceSide.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/AuctionStatus.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RfqSide.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Type.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/Capacity.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/RfqStatus.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/NonDisplayedTradeTradeCond1.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/PriceType.cpp
  cpp/flyweight/nyse/arcaoptions/deepfeed/pillar/v1.2.m/enums/CrossType.cpp
)
target_include_directories(flyweight_nyse_arcaoptions_deepfeed_pillar_v1.2.m PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nyse_nyseequities_integratedfeed_xdp_v2.3.a STATIC
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/DeliveryFlag.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/MessageType.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/MarketId.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/ExchangeCode.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SecurityType.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/PriceResolution.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/RoundLot.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/Status.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/RetransmitMethod.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SecurityStatus.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/HaltCondition.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SsrTriggeringExchangeId.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SsrState.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/MarketState.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/Side.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/PositionChange.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/PrintableFlag.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/RpiIndicator.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/CrossType.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/AuctionType.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/ImbalanceSide.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/AuctionStatus.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/FreezeStatus.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/UnpairedSide.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SignificantImbalance.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/structs/SendTime.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/structs/PacketHeader.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/structs/MessageHeader.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/SequenceNumberResetMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/SourceTimeReferenceMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/SymbolIndexMappingMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/RetransmissionRequestMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/RequestResponseMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/HeartbeatResponseMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/SymbolIndexMappingRequestMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/RefreshRequestMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/MessageUnavailableMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/SymbolClearMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/SecurityStatusMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/structs/FullRefreshHeader.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/RefreshHeaderMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/AddOrderMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/ModifyOrderMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/ReplaceOrderMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/DeleteOrderMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/OrderExecutionMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/NonDisplayedTradeMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/TradeCancelMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/RetailPriceImprovementMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/CrossTradeMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/CrossCorrectionMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/ImbalanceMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/AddOrderRefreshMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/StockSummaryMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/messages/UnknownMessage.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/Factory.cpp
  cpp/classes/nyse/nyseequities/integratedfeed/xdp/v2.3.a/Packet.cpp
)
target_include_directories(classes_nyse_nyseequities_integratedfeed_xdp_v2.3.a PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_nyse_nyseequities_integratedfeed_xdp_v2.3.a STATIC
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/DeliveryFlag.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/MessageType.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/MarketId.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/ExchangeCode.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SecurityType.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/PriceResolution.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/RoundLot.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/Status.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/RetransmitMethod.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SecurityStatus.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/HaltCondition.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SsrTriggeringExchangeId.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SsrState.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/MarketState.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/Side.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/PositionChange.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/PrintableFlag.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/RpiIndicator.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/CrossType.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/AuctionType.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/ImbalanceSide.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/AuctionStatus.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/FreezeStatus.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/UnpairedSide.cpp
  cpp/flyweight/nyse/nyseequities/integratedfeed/xdp/v2.3.a/enums/SignificantImbalance.cpp
)
target_include_directories(flyweight_nyse_nyseequities_integratedfeed_xdp_v2.3.a PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_siac_opra_output_obi_v6.2 STATIC
  cpp/classes/siac/opra/output/obi/v6.2/enums/DataFeedIndicator.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/RetransmissionIndicator.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/SessionIndicator.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/ParticipantId.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/MessageCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/AdministrativeMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/ControlMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/EquityAndIndexLastSaleMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/ExpirationMonth.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/StrikePriceDenominatorCode.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/PremiumPriceDenominatorCode.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/OpenInterestMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/EquityAndIndexEndOfDaySummaryMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/UnderlyingPriceDenominatorCode.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/LongEquityAndIndexQuoteMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/BboIndicator.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/BestBidParticipantId.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/BestBidDenominatorCode.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/BestOfferParticipantId.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/BestOfferDenominatorCode.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/ShortEquityAndIndexQuoteMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/UnderlyingValueMessageType.cpp
  cpp/classes/siac/opra/output/obi/v6.2/enums/IndexValueDenominatorCode.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/BlockTimestamp.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/BlockHeader.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/MessageHeader.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/AdministrativeMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/AdministrativeCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/ControlMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/ControlCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/ExpirationBlock.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/EquityAndIndexLastSaleMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/EquityAndIndexLastSaleCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/OpenInterestMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/OpenInterestCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/EquityAndIndexEndOfDaySummaryMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/EquityAndIndexEndOfDaySummaryCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/BestBidAppendage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/BestOfferAppendage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/structs/BestBidAndOfferAppendage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/LongEquityAndIndexQuoteMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/LongEquityAndIndexQuoteCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/ShortEquityAndIndexQuoteMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/ShortEquityAndIndexQuoteCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnderlyingValueLastSaleMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnderlyingValueBidAndOfferMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnderlyingValueCategory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownMessage.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownAdministrativeMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownControlMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownEquityAndIndexLastSaleMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownOpenInterestMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownEquityAndIndexEndOfDaySummaryMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownLongEquityAndIndexQuoteMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownShortEquityAndIndexQuoteMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/messages/UnknownUnderlyingValueMessagePayload.cpp
  cpp/classes/siac/opra/output/obi/v6.2/Factory.cpp
  cpp/classes/siac/opra/output/obi/v6.2/Packet.cpp
)
target_include_directories(classes_siac_opra_output_obi_v6.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_siac_opra_output_obi_v6.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_siac_opra_output_obi_v6.2 STATIC
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/DataFeedIndicator.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/RetransmissionIndicator.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/SessionIndicator.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/ParticipantId.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/MessageCategory.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/AdministrativeMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/ControlMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/EquityAndIndexLastSaleMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/ExpirationMonth.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/StrikePriceDenominatorCode.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/PremiumPriceDenominatorCode.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/OpenInterestMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/EquityAndIndexEndOfDaySummaryMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/UnderlyingPriceDenominatorCode.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/LongEquityAndIndexQuoteMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/BboIndicator.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/BestBidParticipantId.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/BestBidDenominatorCode.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/BestOfferParticipantId.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/BestOfferDenominatorCode.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/ShortEquityAndIndexQuoteMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/UnderlyingValueMessageType.cpp
  cpp/flyweight/siac/opra/output/obi/v6.2/enums/IndexValueDenominatorCode.cpp
)
target_include_directories(flyweight_siac_opra_output_obi_v6.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_siac_opra_output_obi_v6.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_siac_cts_output_cta_v2.11.b STATIC
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/MessageCategory.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/AdministrativeMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/ParticipantId.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/PrimaryListingMarketParticipantId.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/MinimumPriceIncrementIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/LuldTier.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Test.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Ipo.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/FinancialStatusIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/ShortSaleRestrictionIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/HaltReason.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/InstrumentType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/ControlMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/IndicesMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/MarketStatusMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/MarketWideCircuitBreakerLevelIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/PriorDayMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/TradeReportingFacilityId.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Category1.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Category2.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Category3.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Category4.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/StopStockIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/TradeThroughExemptIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/CancelErrorAction.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/SummaryMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/Tick.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/TradeMessageType.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/HeldTradeIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/ConsolidatedHighLowLastIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/ParticipantOpenHighLowLastIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/SaleCondition1.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/SaleConditionCategory.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/SecurityStatus.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/enums/LimitUpLimitDownLuldIndicator.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/SipBlockTimestamp.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/BlockHeader.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/Timestamp1.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/StartOfEndOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/EndOfEndOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/StartOfStartOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/EndOfStartOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/SymbolReferenceDataMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/AdministrativeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/StartOfDayMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ResetBlockSequenceNumberMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/DisasterRecoveryDataCenterActivationMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/LineIntegrityMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/EndOfDayMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ControlMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/IndexMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/BidAndOfferIndexMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/IndicesMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/MarketWideCircuitBreakerDeclineLevelStatusMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/MarketWideCircuitBreakerStatusMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/groups/ApproximateVolumeParticipant.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ApproximateAdjustedVolumeMarketCenterMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/groups/Participant.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalApproximateAdjustedVolumeMarketCenterMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ApproximateTradesAndTotalDollarValueMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/CrossingSessionSummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/MarketStatusMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/CorrectedPriorDayTradeDateAndTime.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/OriginalPriorDayTradeDateAndTime.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/PriorDayTradeCorrectionMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/SaleCondition4.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/PriorDayTradeDateAndTime.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/PriorDayTradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/PriorDayTradeCancelErrorMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalPriorDayTradeCorrectionMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalPriorDayTradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalPriorDayTradeCancelErrorMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/PriorDayMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ConsolidatedStartOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ParticipantStartOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ConsolidatedEndOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalConsolidatedEndOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ParticipantEndOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalParticipantEndOfDaySummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/SummaryMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/AuctionStatusMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/structs/Timestamp2.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/TradeCorrectionMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/LongTradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/ShortTradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/TradeCancelErrorMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalTradeCorrectionMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalLongTradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/TradingStatusMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalShortTradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/FractionalTradeCancelErrorMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/TradeMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownMessage.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownAdministrativeMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownControlMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownIndicesMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownMarketStatusMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownPriorDayMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownSummaryMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/messages/UnknownTradeMessagePayload.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/Factory.cpp
  cpp/classes/siac/cts/output/cta/v2.11.b/Packet.cpp
)
target_include_directories(classes_siac_cts_output_cta_v2.11.b PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_siac_cts_output_cta_v2.11.b PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_siac_cts_output_cta_v2.11.b STATIC
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/MessageCategory.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/AdministrativeMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/ParticipantId.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/PrimaryListingMarketParticipantId.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/MinimumPriceIncrementIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/LuldTier.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Test.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Ipo.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/FinancialStatusIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/ShortSaleRestrictionIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/HaltReason.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/InstrumentType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/ControlMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/IndicesMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/MarketStatusMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/MarketWideCircuitBreakerLevelIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/PriorDayMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/TradeReportingFacilityId.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Category1.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Category2.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Category3.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Category4.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/StopStockIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/TradeThroughExemptIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/CancelErrorAction.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/SummaryMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/Tick.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/TradeMessageType.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/HeldTradeIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/ConsolidatedHighLowLastIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/ParticipantOpenHighLowLastIndicator.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/SaleCondition1.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/SaleConditionCategory.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/SecurityStatus.cpp
  cpp/flyweight/siac/cts/output/cta/v2.11.b/enums/LimitUpLimitDownLuldIndicator.cpp
)
target_include_directories(flyweight_siac_cts_output_cta_v2.11.b PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_siac_cts_output_cta_v2.11.b PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_siac_cqs_output_cta_v2.10.a STATIC
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/MessageCategory.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/AdministrativeMessageType.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/ParticipantId.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/PrimaryListingMarketParticipantId.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/LuldTier.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/Test.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/Ipo.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/FinancialStatusIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/ShortSaleRestrictionIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/InstrumentType.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/ControlMessageType.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/MarketStatusMessageType.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/MarketWideCircuitBreakerLevelIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/QuoteMessageType.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/QuoteCondition.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/SecurityStatusIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/RetailInterestIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/SettlementCondition.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/MarketCondition.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/FinraBboIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/SipGeneratedMessageIdentifier.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/LimitUpLimitDownLuldIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/NationalBboLuldIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/NationalBboIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/enums/FinraBboLuldIndicator.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/SipBlockTimestamp.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/BlockHeader.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/Timestamp1.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/SymbolReferenceDataMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/AdministrativeMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/StartOfDayMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/FinraCloseMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/ResetBlockSequenceNumberMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/FinraOpenMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/DisasterRecoveryDataCenterActivationMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/LineIntegrityMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/EndOfDayMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/ControlMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/MarketWideCircuitBreakerDeclineLevelStatusMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/MarketWideCircuitBreakerStatusMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/MarketStatusMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/AuctionStatusMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/Timestamp2.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/NationalBestBidLongAppendage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/NationalBestOfferLongAppendage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/NationalBestBidAndOfferLongAppendage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/NationalBestBidShortAppendage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/NationalBestOfferShortAppendage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/structs/NationalBestBidAndOfferShortAppendage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/LongQuoteMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/ShortQuoteMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/SpecialLongQuoteMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/QuoteMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/UnknownMessage.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/UnknownAdministrativeMessagePayload.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/UnknownControlMessagePayload.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/UnknownMarketStatusMessagePayload.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/messages/UnknownQuoteMessagePayload.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/Factory.cpp
  cpp/classes/siac/cqs/output/cta/v2.10.a/Packet.cpp
)
target_include_directories(classes_siac_cqs_output_cta_v2.10.a PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_siac_cqs_output_cta_v2.10.a PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(flyweight_siac_cqs_output_cta_v2.10.a STATIC
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/MessageCategory.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/AdministrativeMessageType.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/ParticipantId.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/PrimaryListingMarketParticipantId.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/LuldTier.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/Test.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/Ipo.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/FinancialStatusIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/ShortSaleRestrictionIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/InstrumentType.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/ControlMessageType.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/MarketStatusMessageType.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/MarketWideCircuitBreakerLevelIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/QuoteMessageType.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/QuoteCondition.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/SecurityStatusIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/RetailInterestIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/SettlementCondition.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/MarketCondition.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/FinraBboIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/SipGeneratedMessageIdentifier.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/LimitUpLimitDownLuldIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/NationalBboLuldIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/NationalBboIndicator.cpp
  cpp/flyweight/siac/cqs/output/cta/v2.10.a/enums/FinraBboLuldIndicator.cpp
)
target_include_directories(flyweight_siac_cqs_output_cta_v2.10.a PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(flyweight_siac_cqs_output_cta_v2.10.a PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
# Programs under executables/ — one per protocol. Each reads the parser published under
# cpp/, included by a repository-root-relative path, so there is only ever one copy of a
# protocol's parser in the tree.
add_executable(statistics_asx_asxderivatives_ntp_itch_v1.05 executables/statistics/asx/asxderivatives/ntp/itch/v1.05/main.cpp)
target_include_directories(statistics_asx_asxderivatives_ntp_itch_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/asx/asxderivatives/ntp/itch/v1.05)
add_executable(extractor_asx_asxderivatives_ntp_itch_v1.05 executables/extractor/asx/asxderivatives/ntp/itch/v1.05/main.cpp)
target_include_directories(extractor_asx_asxderivatives_ntp_itch_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/asx/asxderivatives/ntp/itch/v1.05)
add_executable(dump_asx_asxderivatives_ntp_itch_v1.05 executables/dump/asx/asxderivatives/ntp/itch/v1.05/main.cpp)
target_include_directories(dump_asx_asxderivatives_ntp_itch_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/asx/asxderivatives/ntp/itch/v1.05)
target_link_libraries(dump_asx_asxderivatives_ntp_itch_v1.05 PRIVATE classes_asx_asxderivatives_ntp_itch_v1.05)
add_executable(verify_asx_asxderivatives_ntp_itch_v1.05 executables/verify/asx/asxderivatives/ntp/itch/v1.05/main.cpp)
target_include_directories(verify_asx_asxderivatives_ntp_itch_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/asx/asxderivatives/ntp/itch/v1.05)
target_link_libraries(verify_asx_asxderivatives_ntp_itch_v1.05 PRIVATE classes_asx_asxderivatives_ntp_itch_v1.05)
add_executable(benchmark_asx_asxderivatives_ntp_itch_v1.05 executables/benchmark/asx/asxderivatives/ntp/itch/v1.05/main.cpp)
target_include_directories(benchmark_asx_asxderivatives_ntp_itch_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/asx/asxderivatives/ntp/itch/v1.05)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.6)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.6)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.6)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.6)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.6)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.6)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.6)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.7)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.7)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.7)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.7)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.7)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.7)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.7)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.8)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.8)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.8)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.8)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.8)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.8)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.8)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.9)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.9)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.9)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.9)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.9)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.9)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v1.9)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.1)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.1)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.1)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.1)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.1)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.1)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v2.1)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.2)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.2)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.2)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.2)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.2)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.2)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v2.2)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.3)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.3)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.3)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.3)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.3)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.3)
add_executable(benchmark_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(benchmark_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/b3/b3derivatives/binaryumdf/sbe/v2.3)
add_executable(statistics_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 executables/statistics/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/main.cpp)
target_include_directories(statistics_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29)
add_executable(extractor_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 executables/extractor/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/main.cpp)
target_include_directories(extractor_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29)
add_executable(dump_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 executables/dump/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/main.cpp)
target_include_directories(dump_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29)
target_link_libraries(dump_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE classes_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29)
add_executable(verify_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 executables/verify/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/main.cpp)
target_include_directories(verify_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29)
target_link_libraries(verify_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE classes_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29)
add_executable(benchmark_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 executables/benchmark/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29/main.cpp)
target_include_directories(benchmark_cboe_bzxequities_multicastdepthofbook_pitch_v2.41.29 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/cboe/bzxequities/multicastdepthofbook/pitch/v2.41.29)
add_executable(statistics_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 executables/statistics/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/main.cpp)
target_include_directories(statistics_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80)
add_executable(extractor_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 executables/extractor/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/main.cpp)
target_include_directories(extractor_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80)
add_executable(dump_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 executables/dump/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/main.cpp)
target_include_directories(dump_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80)
target_link_libraries(dump_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE classes_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80)
add_executable(verify_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 executables/verify/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/main.cpp)
target_include_directories(verify_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80)
target_link_libraries(verify_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE classes_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80)
add_executable(benchmark_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 executables/benchmark/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/main.cpp)
target_include_directories(benchmark_cboe_edgxoptions_multicastdepthofbook_pitch_v2.41.80 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80)
add_executable(statistics_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 executables/statistics/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/main.cpp)
target_include_directories(statistics_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22)
add_executable(extractor_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 executables/extractor/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/main.cpp)
target_include_directories(extractor_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22)
add_executable(dump_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 executables/dump/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/main.cpp)
target_include_directories(dump_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22)
target_link_libraries(dump_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE classes_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22)
add_executable(verify_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 executables/verify/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/main.cpp)
target_include_directories(verify_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22)
target_link_libraries(verify_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE classes_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22)
add_executable(benchmark_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 executables/benchmark/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/main.cpp)
target_include_directories(benchmark_cboe_cfefutures_multicastdepthofbook_pitch_v1.2.22 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22)
add_executable(statistics_cme_globex_mdp3_sbe_v1.8 executables/statistics/cme/globex/mdp3/sbe/v1.8/main.cpp)
target_include_directories(statistics_cme_globex_mdp3_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/cme/globex/mdp3/sbe/v1.8)
add_executable(extractor_cme_globex_mdp3_sbe_v1.8 executables/extractor/cme/globex/mdp3/sbe/v1.8/main.cpp)
target_include_directories(extractor_cme_globex_mdp3_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/cme/globex/mdp3/sbe/v1.8)
add_executable(dump_cme_globex_mdp3_sbe_v1.8 executables/dump/cme/globex/mdp3/sbe/v1.8/main.cpp)
target_include_directories(dump_cme_globex_mdp3_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/cme/globex/mdp3/sbe/v1.8)
target_link_libraries(dump_cme_globex_mdp3_sbe_v1.8 PRIVATE classes_cme_globex_mdp3_sbe_v1.8)
add_executable(verify_cme_globex_mdp3_sbe_v1.8 executables/verify/cme/globex/mdp3/sbe/v1.8/main.cpp)
target_include_directories(verify_cme_globex_mdp3_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/cme/globex/mdp3/sbe/v1.8)
target_link_libraries(verify_cme_globex_mdp3_sbe_v1.8 PRIVATE classes_cme_globex_mdp3_sbe_v1.8)
add_executable(benchmark_cme_globex_mdp3_sbe_v1.8 executables/benchmark/cme/globex/mdp3/sbe/v1.8/main.cpp)
target_include_directories(benchmark_cme_globex_mdp3_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/cme/globex/mdp3/sbe/v1.8)
add_executable(statistics_cme_globex_mdp3_sbe_v1.9 executables/statistics/cme/globex/mdp3/sbe/v1.9/main.cpp)
target_include_directories(statistics_cme_globex_mdp3_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/cme/globex/mdp3/sbe/v1.9)
add_executable(extractor_cme_globex_mdp3_sbe_v1.9 executables/extractor/cme/globex/mdp3/sbe/v1.9/main.cpp)
target_include_directories(extractor_cme_globex_mdp3_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/cme/globex/mdp3/sbe/v1.9)
add_executable(dump_cme_globex_mdp3_sbe_v1.9 executables/dump/cme/globex/mdp3/sbe/v1.9/main.cpp)
target_include_directories(dump_cme_globex_mdp3_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/cme/globex/mdp3/sbe/v1.9)
target_link_libraries(dump_cme_globex_mdp3_sbe_v1.9 PRIVATE classes_cme_globex_mdp3_sbe_v1.9)
add_executable(verify_cme_globex_mdp3_sbe_v1.9 executables/verify/cme/globex/mdp3/sbe/v1.9/main.cpp)
target_include_directories(verify_cme_globex_mdp3_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/cme/globex/mdp3/sbe/v1.9)
target_link_libraries(verify_cme_globex_mdp3_sbe_v1.9 PRIVATE classes_cme_globex_mdp3_sbe_v1.9)
add_executable(benchmark_cme_globex_mdp3_sbe_v1.9 executables/benchmark/cme/globex/mdp3/sbe/v1.9/main.cpp)
target_include_directories(benchmark_cme_globex_mdp3_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/cme/globex/mdp3/sbe/v1.9)
add_executable(statistics_cme_globex_mdp3_sbe_v1.13 executables/statistics/cme/globex/mdp3/sbe/v1.13/main.cpp)
target_include_directories(statistics_cme_globex_mdp3_sbe_v1.13 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/cme/globex/mdp3/sbe/v1.13)
add_executable(extractor_cme_globex_mdp3_sbe_v1.13 executables/extractor/cme/globex/mdp3/sbe/v1.13/main.cpp)
target_include_directories(extractor_cme_globex_mdp3_sbe_v1.13 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/cme/globex/mdp3/sbe/v1.13)
add_executable(dump_cme_globex_mdp3_sbe_v1.13 executables/dump/cme/globex/mdp3/sbe/v1.13/main.cpp)
target_include_directories(dump_cme_globex_mdp3_sbe_v1.13 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/cme/globex/mdp3/sbe/v1.13)
target_link_libraries(dump_cme_globex_mdp3_sbe_v1.13 PRIVATE classes_cme_globex_mdp3_sbe_v1.13)
add_executable(verify_cme_globex_mdp3_sbe_v1.13 executables/verify/cme/globex/mdp3/sbe/v1.13/main.cpp)
target_include_directories(verify_cme_globex_mdp3_sbe_v1.13 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/cme/globex/mdp3/sbe/v1.13)
target_link_libraries(verify_cme_globex_mdp3_sbe_v1.13 PRIVATE classes_cme_globex_mdp3_sbe_v1.13)
add_executable(benchmark_cme_globex_mdp3_sbe_v1.13 executables/benchmark/cme/globex/mdp3/sbe/v1.13/main.cpp)
target_include_directories(benchmark_cme_globex_mdp3_sbe_v1.13 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/cme/globex/mdp3/sbe/v1.13)
add_executable(statistics_eurex_t7_eobi_fbe_v13.0 executables/statistics/eurex/t7/eobi/fbe/v13.0/main.cpp)
target_include_directories(statistics_eurex_t7_eobi_fbe_v13.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/eurex/t7/eobi/fbe/v13.0)
add_executable(extractor_eurex_t7_eobi_fbe_v13.0 executables/extractor/eurex/t7/eobi/fbe/v13.0/main.cpp)
target_include_directories(extractor_eurex_t7_eobi_fbe_v13.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/eurex/t7/eobi/fbe/v13.0)
add_executable(dump_eurex_t7_eobi_fbe_v13.0 executables/dump/eurex/t7/eobi/fbe/v13.0/main.cpp)
target_include_directories(dump_eurex_t7_eobi_fbe_v13.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/eurex/t7/eobi/fbe/v13.0)
target_link_libraries(dump_eurex_t7_eobi_fbe_v13.0 PRIVATE classes_eurex_t7_eobi_fbe_v13.0)
add_executable(verify_eurex_t7_eobi_fbe_v13.0 executables/verify/eurex/t7/eobi/fbe/v13.0/main.cpp)
target_include_directories(verify_eurex_t7_eobi_fbe_v13.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/eurex/t7/eobi/fbe/v13.0)
target_link_libraries(verify_eurex_t7_eobi_fbe_v13.0 PRIVATE classes_eurex_t7_eobi_fbe_v13.0)
add_executable(benchmark_eurex_t7_eobi_fbe_v13.0 executables/benchmark/eurex/t7/eobi/fbe/v13.0/main.cpp)
target_include_directories(benchmark_eurex_t7_eobi_fbe_v13.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/eurex/t7/eobi/fbe/v13.0)
add_executable(statistics_eurex_t7_eobi_fbe_v15.0 executables/statistics/eurex/t7/eobi/fbe/v15.0/main.cpp)
target_include_directories(statistics_eurex_t7_eobi_fbe_v15.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/eurex/t7/eobi/fbe/v15.0)
add_executable(extractor_eurex_t7_eobi_fbe_v15.0 executables/extractor/eurex/t7/eobi/fbe/v15.0/main.cpp)
target_include_directories(extractor_eurex_t7_eobi_fbe_v15.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/eurex/t7/eobi/fbe/v15.0)
add_executable(dump_eurex_t7_eobi_fbe_v15.0 executables/dump/eurex/t7/eobi/fbe/v15.0/main.cpp)
target_include_directories(dump_eurex_t7_eobi_fbe_v15.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/eurex/t7/eobi/fbe/v15.0)
target_link_libraries(dump_eurex_t7_eobi_fbe_v15.0 PRIVATE classes_eurex_t7_eobi_fbe_v15.0)
add_executable(verify_eurex_t7_eobi_fbe_v15.0 executables/verify/eurex/t7/eobi/fbe/v15.0/main.cpp)
target_include_directories(verify_eurex_t7_eobi_fbe_v15.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/eurex/t7/eobi/fbe/v15.0)
target_link_libraries(verify_eurex_t7_eobi_fbe_v15.0 PRIVATE classes_eurex_t7_eobi_fbe_v15.0)
add_executable(benchmark_eurex_t7_eobi_fbe_v15.0 executables/benchmark/eurex/t7/eobi/fbe/v15.0/main.cpp)
target_include_directories(benchmark_eurex_t7_eobi_fbe_v15.0 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/eurex/t7/eobi/fbe/v15.0)
add_executable(statistics_iex_iexequities_deep_iextp_v1.06 executables/statistics/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.06)
add_executable(extractor_iex_iexequities_deep_iextp_v1.06 executables/extractor/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.06)
add_executable(dump_iex_iexequities_deep_iextp_v1.06 executables/dump/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.06)
target_link_libraries(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(verify_iex_iexequities_deep_iextp_v1.06 executables/verify/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(verify_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deep/iextp/v1.06)
target_link_libraries(verify_iex_iexequities_deep_iextp_v1.06 PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(benchmark_iex_iexequities_deep_iextp_v1.06 executables/benchmark/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(benchmark_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/deep/iextp/v1.06)
add_executable(statistics_iex_iexequities_deep_iextp_v1.08 executables/statistics/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.08)
add_executable(extractor_iex_iexequities_deep_iextp_v1.08 executables/extractor/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.08)
add_executable(dump_iex_iexequities_deep_iextp_v1.08 executables/dump/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.08)
target_link_libraries(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(verify_iex_iexequities_deep_iextp_v1.08 executables/verify/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(verify_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deep/iextp/v1.08)
target_link_libraries(verify_iex_iexequities_deep_iextp_v1.08 PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(benchmark_iex_iexequities_deep_iextp_v1.08 executables/benchmark/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(benchmark_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/deep/iextp/v1.08)
add_executable(statistics_iex_iexequities_deep_snap_v1.6 executables/statistics/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/snap/v1.6)
add_executable(extractor_iex_iexequities_deep_snap_v1.6 executables/extractor/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/snap/v1.6)
add_executable(dump_iex_iexequities_deep_snap_v1.6 executables/dump/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/snap/v1.6)
target_link_libraries(dump_iex_iexequities_deep_snap_v1.6 PRIVATE classes_iex_iexequities_deep_snap_v1.6)
add_executable(verify_iex_iexequities_deep_snap_v1.6 executables/verify/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(verify_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deep/snap/v1.6)
target_link_libraries(verify_iex_iexequities_deep_snap_v1.6 PRIVATE classes_iex_iexequities_deep_snap_v1.6)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.01 executables/statistics/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.01)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.01 executables/extractor/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.01)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.01 executables/dump/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.01)
target_link_libraries(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(verify_iex_iexequities_deepplus_iextp_v1.01 executables/verify/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(verify_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deepplus/iextp/v1.01)
target_link_libraries(verify_iex_iexequities_deepplus_iextp_v1.01 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(benchmark_iex_iexequities_deepplus_iextp_v1.01 executables/benchmark/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(benchmark_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/deepplus/iextp/v1.01)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.05 executables/statistics/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.05)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.05 executables/extractor/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.05)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.05 executables/dump/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.05)
target_link_libraries(dump_iex_iexequities_deepplus_iextp_v1.05 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.05)
add_executable(verify_iex_iexequities_deepplus_iextp_v1.05 executables/verify/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(verify_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deepplus/iextp/v1.05)
target_link_libraries(verify_iex_iexequities_deepplus_iextp_v1.05 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.05)
add_executable(benchmark_iex_iexequities_deepplus_iextp_v1.05 executables/benchmark/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(benchmark_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/deepplus/iextp/v1.05)
add_executable(statistics_iex_iexequities_deepplus_snap_v1.06 executables/statistics/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/snap/v1.06)
add_executable(extractor_iex_iexequities_deepplus_snap_v1.06 executables/extractor/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/snap/v1.06)
add_executable(dump_iex_iexequities_deepplus_snap_v1.06 executables/dump/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/snap/v1.06)
target_link_libraries(dump_iex_iexequities_deepplus_snap_v1.06 PRIVATE classes_iex_iexequities_deepplus_snap_v1.06)
add_executable(verify_iex_iexequities_deepplus_snap_v1.06 executables/verify/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(verify_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deepplus/snap/v1.06)
target_link_libraries(verify_iex_iexequities_deepplus_snap_v1.06 PRIVATE classes_iex_iexequities_deepplus_snap_v1.06)
add_executable(statistics_iex_iexequities_tops_iextp_v1.56 executables/statistics/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.56)
add_executable(extractor_iex_iexequities_tops_iextp_v1.56 executables/extractor/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.56)
add_executable(dump_iex_iexequities_tops_iextp_v1.56 executables/dump/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.56)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(verify_iex_iexequities_tops_iextp_v1.56 executables/verify/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(verify_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/iextp/v1.56)
target_link_libraries(verify_iex_iexequities_tops_iextp_v1.56 PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(benchmark_iex_iexequities_tops_iextp_v1.56 executables/benchmark/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(benchmark_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/tops/iextp/v1.56)
add_executable(statistics_iex_iexequities_tops_iextp_v1.64 executables/statistics/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.64)
add_executable(extractor_iex_iexequities_tops_iextp_v1.64 executables/extractor/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.64)
add_executable(dump_iex_iexequities_tops_iextp_v1.64 executables/dump/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.64)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(verify_iex_iexequities_tops_iextp_v1.64 executables/verify/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(verify_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/iextp/v1.64)
target_link_libraries(verify_iex_iexequities_tops_iextp_v1.64 PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(benchmark_iex_iexequities_tops_iextp_v1.64 executables/benchmark/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(benchmark_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/tops/iextp/v1.64)
add_executable(statistics_iex_iexequities_tops_iextp_v1.66 executables/statistics/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.66)
add_executable(extractor_iex_iexequities_tops_iextp_v1.66 executables/extractor/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.66)
add_executable(dump_iex_iexequities_tops_iextp_v1.66 executables/dump/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.66)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(verify_iex_iexequities_tops_iextp_v1.66 executables/verify/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(verify_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/iextp/v1.66)
target_link_libraries(verify_iex_iexequities_tops_iextp_v1.66 PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(benchmark_iex_iexequities_tops_iextp_v1.66 executables/benchmark/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(benchmark_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/iex/iexequities/tops/iextp/v1.66)
add_executable(statistics_iex_iexequities_tops_snap_v1.6 executables/statistics/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/snap/v1.6)
add_executable(extractor_iex_iexequities_tops_snap_v1.6 executables/extractor/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/snap/v1.6)
add_executable(dump_iex_iexequities_tops_snap_v1.6 executables/dump/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/snap/v1.6)
target_link_libraries(dump_iex_iexequities_tops_snap_v1.6 PRIVATE classes_iex_iexequities_tops_snap_v1.6)
add_executable(verify_iex_iexequities_tops_snap_v1.6 executables/verify/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(verify_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/snap/v1.6)
target_link_libraries(verify_iex_iexequities_tops_snap_v1.6 PRIVATE classes_iex_iexequities_tops_snap_v1.6)
add_executable(statistics_jpx_osederivatives_geniuminet_itch_v5.0.6 executables/statistics/jpx/osederivatives/geniuminet/itch/v5.0.6/main.cpp)
target_include_directories(statistics_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/jpx/osederivatives/geniuminet/itch/v5.0.6)
add_executable(extractor_jpx_osederivatives_geniuminet_itch_v5.0.6 executables/extractor/jpx/osederivatives/geniuminet/itch/v5.0.6/main.cpp)
target_include_directories(extractor_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/jpx/osederivatives/geniuminet/itch/v5.0.6)
add_executable(dump_jpx_osederivatives_geniuminet_itch_v5.0.6 executables/dump/jpx/osederivatives/geniuminet/itch/v5.0.6/main.cpp)
target_include_directories(dump_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/jpx/osederivatives/geniuminet/itch/v5.0.6)
target_link_libraries(dump_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE classes_jpx_osederivatives_geniuminet_itch_v5.0.6)
add_executable(verify_jpx_osederivatives_geniuminet_itch_v5.0.6 executables/verify/jpx/osederivatives/geniuminet/itch/v5.0.6/main.cpp)
target_include_directories(verify_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/jpx/osederivatives/geniuminet/itch/v5.0.6)
target_link_libraries(verify_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE classes_jpx_osederivatives_geniuminet_itch_v5.0.6)
add_executable(benchmark_jpx_osederivatives_geniuminet_itch_v5.0.6 executables/benchmark/jpx/osederivatives/geniuminet/itch/v5.0.6/main.cpp)
target_include_directories(benchmark_jpx_osederivatives_geniuminet_itch_v5.0.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/jpx/osederivatives/geniuminet/itch/v5.0.6)
add_executable(statistics_jpx_tseequities_marketbyorder_flex_v1.1 executables/statistics/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(statistics_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/jpx/tseequities/marketbyorder/flex/v1.1)
add_executable(extractor_jpx_tseequities_marketbyorder_flex_v1.1 executables/extractor/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(extractor_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/jpx/tseequities/marketbyorder/flex/v1.1)
add_executable(dump_jpx_tseequities_marketbyorder_flex_v1.1 executables/dump/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(dump_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/jpx/tseequities/marketbyorder/flex/v1.1)
target_link_libraries(dump_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE classes_jpx_tseequities_marketbyorder_flex_v1.1)
add_executable(verify_jpx_tseequities_marketbyorder_flex_v1.1 executables/verify/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(verify_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/jpx/tseequities/marketbyorder/flex/v1.1)
target_link_libraries(verify_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE classes_jpx_tseequities_marketbyorder_flex_v1.1)
add_executable(benchmark_jpx_tseequities_marketbyorder_flex_v1.1 executables/benchmark/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(benchmark_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/jpx/tseequities/marketbyorder/flex/v1.1)
add_executable(statistics_lseg_lse_level2mbo_gtp_v26.2 executables/statistics/lseg/lse/level2mbo/gtp/v26.2/main.cpp)
target_include_directories(statistics_lseg_lse_level2mbo_gtp_v26.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/lseg/lse/level2mbo/gtp/v26.2)
add_executable(extractor_lseg_lse_level2mbo_gtp_v26.2 executables/extractor/lseg/lse/level2mbo/gtp/v26.2/main.cpp)
target_include_directories(extractor_lseg_lse_level2mbo_gtp_v26.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/lseg/lse/level2mbo/gtp/v26.2)
add_executable(dump_lseg_lse_level2mbo_gtp_v26.2 executables/dump/lseg/lse/level2mbo/gtp/v26.2/main.cpp)
target_include_directories(dump_lseg_lse_level2mbo_gtp_v26.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/lseg/lse/level2mbo/gtp/v26.2)
target_link_libraries(dump_lseg_lse_level2mbo_gtp_v26.2 PRIVATE classes_lseg_lse_level2mbo_gtp_v26.2)
add_executable(verify_lseg_lse_level2mbo_gtp_v26.2 executables/verify/lseg/lse/level2mbo/gtp/v26.2/main.cpp)
target_include_directories(verify_lseg_lse_level2mbo_gtp_v26.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/lseg/lse/level2mbo/gtp/v26.2)
target_link_libraries(verify_lseg_lse_level2mbo_gtp_v26.2 PRIVATE classes_lseg_lse_level2mbo_gtp_v26.2)
add_executable(benchmark_lseg_lse_level2mbo_gtp_v26.2 executables/benchmark/lseg/lse/level2mbo/gtp/v26.2/main.cpp)
target_include_directories(benchmark_lseg_lse_level2mbo_gtp_v26.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/lseg/lse/level2mbo/gtp/v26.2)
add_executable(statistics_lseg_millennium_level2_mitch_v11.9 executables/statistics/lseg/millennium/level2/mitch/v11.9/main.cpp)
target_include_directories(statistics_lseg_millennium_level2_mitch_v11.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/lseg/millennium/level2/mitch/v11.9)
add_executable(extractor_lseg_millennium_level2_mitch_v11.9 executables/extractor/lseg/millennium/level2/mitch/v11.9/main.cpp)
target_include_directories(extractor_lseg_millennium_level2_mitch_v11.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/lseg/millennium/level2/mitch/v11.9)
add_executable(dump_lseg_millennium_level2_mitch_v11.9 executables/dump/lseg/millennium/level2/mitch/v11.9/main.cpp)
target_include_directories(dump_lseg_millennium_level2_mitch_v11.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/lseg/millennium/level2/mitch/v11.9)
target_link_libraries(dump_lseg_millennium_level2_mitch_v11.9 PRIVATE classes_lseg_millennium_level2_mitch_v11.9)
add_executable(verify_lseg_millennium_level2_mitch_v11.9 executables/verify/lseg/millennium/level2/mitch/v11.9/main.cpp)
target_include_directories(verify_lseg_millennium_level2_mitch_v11.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/lseg/millennium/level2/mitch/v11.9)
target_link_libraries(verify_lseg_millennium_level2_mitch_v11.9 PRIVATE classes_lseg_millennium_level2_mitch_v11.9)
add_executable(benchmark_lseg_millennium_level2_mitch_v11.9 executables/benchmark/lseg/millennium/level2/mitch/v11.9/main.cpp)
target_include_directories(benchmark_lseg_millennium_level2_mitch_v11.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/lseg/millennium/level2/mitch/v11.9)
add_executable(statistics_memx_memxequities_memoirdepthfeed_sbe_v1.3 executables/statistics/memx/memxequities/memoirdepthfeed/sbe/v1.3/main.cpp)
target_include_directories(statistics_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/memx/memxequities/memoirdepthfeed/sbe/v1.3)
add_executable(extractor_memx_memxequities_memoirdepthfeed_sbe_v1.3 executables/extractor/memx/memxequities/memoirdepthfeed/sbe/v1.3/main.cpp)
target_include_directories(extractor_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/memx/memxequities/memoirdepthfeed/sbe/v1.3)
add_executable(dump_memx_memxequities_memoirdepthfeed_sbe_v1.3 executables/dump/memx/memxequities/memoirdepthfeed/sbe/v1.3/main.cpp)
target_include_directories(dump_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/memx/memxequities/memoirdepthfeed/sbe/v1.3)
target_link_libraries(dump_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE classes_memx_memxequities_memoirdepthfeed_sbe_v1.3)
add_executable(verify_memx_memxequities_memoirdepthfeed_sbe_v1.3 executables/verify/memx/memxequities/memoirdepthfeed/sbe/v1.3/main.cpp)
target_include_directories(verify_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/memx/memxequities/memoirdepthfeed/sbe/v1.3)
target_link_libraries(verify_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE classes_memx_memxequities_memoirdepthfeed_sbe_v1.3)
add_executable(benchmark_memx_memxequities_memoirdepthfeed_sbe_v1.3 executables/benchmark/memx/memxequities/memoirdepthfeed/sbe/v1.3/main.cpp)
target_include_directories(benchmark_memx_memxequities_memoirdepthfeed_sbe_v1.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/memx/memxequities/memoirdepthfeed/sbe/v1.3)
add_executable(statistics_miax_pearlequities_depthofmarket_mach_v1.3.d executables/statistics/miax/pearlequities/depthofmarket/mach/v1.3.d/main.cpp)
target_include_directories(statistics_miax_pearlequities_depthofmarket_mach_v1.3.d PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/miax/pearlequities/depthofmarket/mach/v1.3.d)
add_executable(extractor_miax_pearlequities_depthofmarket_mach_v1.3.d executables/extractor/miax/pearlequities/depthofmarket/mach/v1.3.d/main.cpp)
target_include_directories(extractor_miax_pearlequities_depthofmarket_mach_v1.3.d PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/miax/pearlequities/depthofmarket/mach/v1.3.d)
add_executable(benchmark_miax_pearlequities_depthofmarket_mach_v1.3.d executables/benchmark/miax/pearlequities/depthofmarket/mach/v1.3.d/main.cpp)
target_include_directories(benchmark_miax_pearlequities_depthofmarket_mach_v1.3.d PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/miax/pearlequities/depthofmarket/mach/v1.3.d)
add_executable(statistics_miax_miaxoptions_topofmarket_mach_v2.5 executables/statistics/miax/miaxoptions/topofmarket/mach/v2.5/main.cpp)
target_include_directories(statistics_miax_miaxoptions_topofmarket_mach_v2.5 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/miax/miaxoptions/topofmarket/mach/v2.5)
add_executable(extractor_miax_miaxoptions_topofmarket_mach_v2.5 executables/extractor/miax/miaxoptions/topofmarket/mach/v2.5/main.cpp)
target_include_directories(extractor_miax_miaxoptions_topofmarket_mach_v2.5 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/miax/miaxoptions/topofmarket/mach/v2.5)
add_executable(benchmark_miax_miaxoptions_topofmarket_mach_v2.5 executables/benchmark/miax/miaxoptions/topofmarket/mach/v2.5/main.cpp)
target_include_directories(benchmark_miax_miaxoptions_topofmarket_mach_v2.5 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/miax/miaxoptions/topofmarket/mach/v2.5)
add_executable(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2017 executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2017/main.cpp)
target_include_directories(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2017)
add_executable(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2017 executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2017/main.cpp)
target_include_directories(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2017)
add_executable(dump_nasdaq_nsmequities_totalview_itch_v5.0.2017 executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2017/main.cpp)
target_include_directories(dump_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2017)
target_link_libraries(dump_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2017)
add_executable(verify_nasdaq_nsmequities_totalview_itch_v5.0.2017 executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2017/main.cpp)
target_include_directories(verify_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2017)
target_link_libraries(verify_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2017)
add_executable(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2017 executables/benchmark/nasdaq/nsmequities/totalview/itch/v5.0.2017/main.cpp)
target_include_directories(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2017 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/nsmequities/totalview/itch/v5.0.2017)
add_executable(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2023)
add_executable(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2023)
add_executable(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2023)
target_link_libraries(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2023)
add_executable(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2023)
target_link_libraries(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2023)
add_executable(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/benchmark/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/nsmequities/totalview/itch/v5.0.2023)
add_executable(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2026 executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2026/main.cpp)
target_include_directories(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2026)
add_executable(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2026 executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2026/main.cpp)
target_include_directories(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2026)
add_executable(dump_nasdaq_nsmequities_totalview_itch_v5.0.2026 executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2026/main.cpp)
target_include_directories(dump_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2026)
target_link_libraries(dump_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2026)
add_executable(verify_nasdaq_nsmequities_totalview_itch_v5.0.2026 executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2026/main.cpp)
target_include_directories(verify_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2026)
target_link_libraries(verify_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2026)
add_executable(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2026 executables/benchmark/nasdaq/nsmequities/totalview/itch/v5.0.2026/main.cpp)
target_include_directories(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2026 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/nsmequities/totalview/itch/v5.0.2026)
add_executable(statistics_nasdaq_nsmequities_qbbo_itch_v2.1 executables/statistics/nasdaq/nsmequities/qbbo/itch/v2.1/main.cpp)
target_include_directories(statistics_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nsmequities/qbbo/itch/v2.1)
add_executable(extractor_nasdaq_nsmequities_qbbo_itch_v2.1 executables/extractor/nasdaq/nsmequities/qbbo/itch/v2.1/main.cpp)
target_include_directories(extractor_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nsmequities/qbbo/itch/v2.1)
add_executable(dump_nasdaq_nsmequities_qbbo_itch_v2.1 executables/dump/nasdaq/nsmequities/qbbo/itch/v2.1/main.cpp)
target_include_directories(dump_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nsmequities/qbbo/itch/v2.1)
target_link_libraries(dump_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE classes_nasdaq_nsmequities_qbbo_itch_v2.1)
add_executable(verify_nasdaq_nsmequities_qbbo_itch_v2.1 executables/verify/nasdaq/nsmequities/qbbo/itch/v2.1/main.cpp)
target_include_directories(verify_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nsmequities/qbbo/itch/v2.1)
target_link_libraries(verify_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE classes_nasdaq_nsmequities_qbbo_itch_v2.1)
add_executable(benchmark_nasdaq_nsmequities_qbbo_itch_v2.1 executables/benchmark/nasdaq/nsmequities/qbbo/itch/v2.1/main.cpp)
target_include_directories(benchmark_nasdaq_nsmequities_qbbo_itch_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/nsmequities/qbbo/itch/v2.1)
add_executable(statistics_nasdaq_nomoptions_itto_itch_v4.0.2025 executables/statistics/nasdaq/nomoptions/itto/itch/v4.0.2025/main.cpp)
target_include_directories(statistics_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nomoptions/itto/itch/v4.0.2025)
add_executable(extractor_nasdaq_nomoptions_itto_itch_v4.0.2025 executables/extractor/nasdaq/nomoptions/itto/itch/v4.0.2025/main.cpp)
target_include_directories(extractor_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nomoptions/itto/itch/v4.0.2025)
add_executable(dump_nasdaq_nomoptions_itto_itch_v4.0.2025 executables/dump/nasdaq/nomoptions/itto/itch/v4.0.2025/main.cpp)
target_include_directories(dump_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nomoptions/itto/itch/v4.0.2025)
target_link_libraries(dump_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE classes_nasdaq_nomoptions_itto_itch_v4.0.2025)
add_executable(verify_nasdaq_nomoptions_itto_itch_v4.0.2025 executables/verify/nasdaq/nomoptions/itto/itch/v4.0.2025/main.cpp)
target_include_directories(verify_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nomoptions/itto/itch/v4.0.2025)
target_link_libraries(verify_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE classes_nasdaq_nomoptions_itto_itch_v4.0.2025)
add_executable(benchmark_nasdaq_nomoptions_itto_itch_v4.0.2025 executables/benchmark/nasdaq/nomoptions/itto/itch/v4.0.2025/main.cpp)
target_include_directories(benchmark_nasdaq_nomoptions_itto_itch_v4.0.2025 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/nomoptions/itto/itch/v4.0.2025)
add_executable(statistics_nasdaq_phlxoptions_topofmarket_itch_v3.4 executables/statistics/nasdaq/phlxoptions/topofmarket/itch/v3.4/main.cpp)
target_include_directories(statistics_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/phlxoptions/topofmarket/itch/v3.4)
add_executable(extractor_nasdaq_phlxoptions_topofmarket_itch_v3.4 executables/extractor/nasdaq/phlxoptions/topofmarket/itch/v3.4/main.cpp)
target_include_directories(extractor_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/phlxoptions/topofmarket/itch/v3.4)
add_executable(dump_nasdaq_phlxoptions_topofmarket_itch_v3.4 executables/dump/nasdaq/phlxoptions/topofmarket/itch/v3.4/main.cpp)
target_include_directories(dump_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/phlxoptions/topofmarket/itch/v3.4)
target_link_libraries(dump_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE classes_nasdaq_phlxoptions_topofmarket_itch_v3.4)
add_executable(verify_nasdaq_phlxoptions_topofmarket_itch_v3.4 executables/verify/nasdaq/phlxoptions/topofmarket/itch/v3.4/main.cpp)
target_include_directories(verify_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/phlxoptions/topofmarket/itch/v3.4)
target_link_libraries(verify_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE classes_nasdaq_phlxoptions_topofmarket_itch_v3.4)
add_executable(benchmark_nasdaq_phlxoptions_topofmarket_itch_v3.4 executables/benchmark/nasdaq/phlxoptions/topofmarket/itch/v3.4/main.cpp)
target_include_directories(benchmark_nasdaq_phlxoptions_topofmarket_itch_v3.4 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/phlxoptions/topofmarket/itch/v3.4)
add_executable(statistics_nasdaq_nordicequities_totalview_itch_v3.04.x executables/statistics/nasdaq/nordicequities/totalview/itch/v3.04.x/main.cpp)
target_include_directories(statistics_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nordicequities/totalview/itch/v3.04.x)
add_executable(extractor_nasdaq_nordicequities_totalview_itch_v3.04.x executables/extractor/nasdaq/nordicequities/totalview/itch/v3.04.x/main.cpp)
target_include_directories(extractor_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nordicequities/totalview/itch/v3.04.x)
add_executable(dump_nasdaq_nordicequities_totalview_itch_v3.04.x executables/dump/nasdaq/nordicequities/totalview/itch/v3.04.x/main.cpp)
target_include_directories(dump_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nordicequities/totalview/itch/v3.04.x)
target_link_libraries(dump_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE classes_nasdaq_nordicequities_totalview_itch_v3.04.x)
add_executable(verify_nasdaq_nordicequities_totalview_itch_v3.04.x executables/verify/nasdaq/nordicequities/totalview/itch/v3.04.x/main.cpp)
target_include_directories(verify_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nordicequities/totalview/itch/v3.04.x)
target_link_libraries(verify_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE classes_nasdaq_nordicequities_totalview_itch_v3.04.x)
add_executable(benchmark_nasdaq_nordicequities_totalview_itch_v3.04.x executables/benchmark/nasdaq/nordicequities/totalview/itch/v3.04.x/main.cpp)
target_include_directories(benchmark_nasdaq_nordicequities_totalview_itch_v3.04.x PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nasdaq/nordicequities/totalview/itch/v3.04.x)
add_executable(statistics_nyse_arcaequities_integratedfeed_pillar_v2.5.g executables/statistics/nyse/arcaequities/integratedfeed/pillar/v2.5.g/main.cpp)
target_include_directories(statistics_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nyse/arcaequities/integratedfeed/pillar/v2.5.g)
add_executable(extractor_nyse_arcaequities_integratedfeed_pillar_v2.5.g executables/extractor/nyse/arcaequities/integratedfeed/pillar/v2.5.g/main.cpp)
target_include_directories(extractor_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nyse/arcaequities/integratedfeed/pillar/v2.5.g)
add_executable(dump_nyse_arcaequities_integratedfeed_pillar_v2.5.g executables/dump/nyse/arcaequities/integratedfeed/pillar/v2.5.g/main.cpp)
target_include_directories(dump_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nyse/arcaequities/integratedfeed/pillar/v2.5.g)
target_link_libraries(dump_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE classes_nyse_arcaequities_integratedfeed_pillar_v2.5.g)
add_executable(verify_nyse_arcaequities_integratedfeed_pillar_v2.5.g executables/verify/nyse/arcaequities/integratedfeed/pillar/v2.5.g/main.cpp)
target_include_directories(verify_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nyse/arcaequities/integratedfeed/pillar/v2.5.g)
target_link_libraries(verify_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE classes_nyse_arcaequities_integratedfeed_pillar_v2.5.g)
add_executable(benchmark_nyse_arcaequities_integratedfeed_pillar_v2.5.g executables/benchmark/nyse/arcaequities/integratedfeed/pillar/v2.5.g/main.cpp)
target_include_directories(benchmark_nyse_arcaequities_integratedfeed_pillar_v2.5.g PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nyse/arcaequities/integratedfeed/pillar/v2.5.g)
add_executable(statistics_nyse_arcaoptions_deepfeed_pillar_v1.2.m executables/statistics/nyse/arcaoptions/deepfeed/pillar/v1.2.m/main.cpp)
target_include_directories(statistics_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nyse/arcaoptions/deepfeed/pillar/v1.2.m)
add_executable(extractor_nyse_arcaoptions_deepfeed_pillar_v1.2.m executables/extractor/nyse/arcaoptions/deepfeed/pillar/v1.2.m/main.cpp)
target_include_directories(extractor_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nyse/arcaoptions/deepfeed/pillar/v1.2.m)
add_executable(dump_nyse_arcaoptions_deepfeed_pillar_v1.2.m executables/dump/nyse/arcaoptions/deepfeed/pillar/v1.2.m/main.cpp)
target_include_directories(dump_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nyse/arcaoptions/deepfeed/pillar/v1.2.m)
target_link_libraries(dump_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE classes_nyse_arcaoptions_deepfeed_pillar_v1.2.m)
add_executable(verify_nyse_arcaoptions_deepfeed_pillar_v1.2.m executables/verify/nyse/arcaoptions/deepfeed/pillar/v1.2.m/main.cpp)
target_include_directories(verify_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nyse/arcaoptions/deepfeed/pillar/v1.2.m)
target_link_libraries(verify_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE classes_nyse_arcaoptions_deepfeed_pillar_v1.2.m)
add_executable(benchmark_nyse_arcaoptions_deepfeed_pillar_v1.2.m executables/benchmark/nyse/arcaoptions/deepfeed/pillar/v1.2.m/main.cpp)
target_include_directories(benchmark_nyse_arcaoptions_deepfeed_pillar_v1.2.m PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nyse/arcaoptions/deepfeed/pillar/v1.2.m)
add_executable(statistics_nyse_nyseequities_integratedfeed_xdp_v2.3.a executables/statistics/nyse/nyseequities/integratedfeed/xdp/v2.3.a/main.cpp)
target_include_directories(statistics_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nyse/nyseequities/integratedfeed/xdp/v2.3.a)
add_executable(extractor_nyse_nyseequities_integratedfeed_xdp_v2.3.a executables/extractor/nyse/nyseequities/integratedfeed/xdp/v2.3.a/main.cpp)
target_include_directories(extractor_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nyse/nyseequities/integratedfeed/xdp/v2.3.a)
add_executable(dump_nyse_nyseequities_integratedfeed_xdp_v2.3.a executables/dump/nyse/nyseequities/integratedfeed/xdp/v2.3.a/main.cpp)
target_include_directories(dump_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nyse/nyseequities/integratedfeed/xdp/v2.3.a)
target_link_libraries(dump_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE classes_nyse_nyseequities_integratedfeed_xdp_v2.3.a)
add_executable(verify_nyse_nyseequities_integratedfeed_xdp_v2.3.a executables/verify/nyse/nyseequities/integratedfeed/xdp/v2.3.a/main.cpp)
target_include_directories(verify_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nyse/nyseequities/integratedfeed/xdp/v2.3.a)
target_link_libraries(verify_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE classes_nyse_nyseequities_integratedfeed_xdp_v2.3.a)
add_executable(benchmark_nyse_nyseequities_integratedfeed_xdp_v2.3.a executables/benchmark/nyse/nyseequities/integratedfeed/xdp/v2.3.a/main.cpp)
target_include_directories(benchmark_nyse_nyseequities_integratedfeed_xdp_v2.3.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/nyse/nyseequities/integratedfeed/xdp/v2.3.a)
add_executable(statistics_siac_opra_output_obi_v6.2 executables/statistics/siac/opra/output/obi/v6.2/main.cpp)
target_include_directories(statistics_siac_opra_output_obi_v6.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/siac/opra/output/obi/v6.2)
add_executable(extractor_siac_opra_output_obi_v6.2 executables/extractor/siac/opra/output/obi/v6.2/main.cpp)
target_include_directories(extractor_siac_opra_output_obi_v6.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/siac/opra/output/obi/v6.2)
add_executable(dump_siac_opra_output_obi_v6.2 executables/dump/siac/opra/output/obi/v6.2/main.cpp)
target_include_directories(dump_siac_opra_output_obi_v6.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/siac/opra/output/obi/v6.2)
target_link_libraries(dump_siac_opra_output_obi_v6.2 PRIVATE classes_siac_opra_output_obi_v6.2)
add_executable(verify_siac_opra_output_obi_v6.2 executables/verify/siac/opra/output/obi/v6.2/main.cpp)
target_include_directories(verify_siac_opra_output_obi_v6.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/siac/opra/output/obi/v6.2)
target_link_libraries(verify_siac_opra_output_obi_v6.2 PRIVATE classes_siac_opra_output_obi_v6.2)
add_executable(benchmark_siac_opra_output_obi_v6.2 executables/benchmark/siac/opra/output/obi/v6.2/main.cpp)
target_include_directories(benchmark_siac_opra_output_obi_v6.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/siac/opra/output/obi/v6.2)
add_executable(statistics_siac_cts_output_cta_v2.11.b executables/statistics/siac/cts/output/cta/v2.11.b/main.cpp)
target_include_directories(statistics_siac_cts_output_cta_v2.11.b PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/siac/cts/output/cta/v2.11.b)
add_executable(extractor_siac_cts_output_cta_v2.11.b executables/extractor/siac/cts/output/cta/v2.11.b/main.cpp)
target_include_directories(extractor_siac_cts_output_cta_v2.11.b PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/siac/cts/output/cta/v2.11.b)
add_executable(dump_siac_cts_output_cta_v2.11.b executables/dump/siac/cts/output/cta/v2.11.b/main.cpp)
target_include_directories(dump_siac_cts_output_cta_v2.11.b PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/siac/cts/output/cta/v2.11.b)
target_link_libraries(dump_siac_cts_output_cta_v2.11.b PRIVATE classes_siac_cts_output_cta_v2.11.b)
add_executable(verify_siac_cts_output_cta_v2.11.b executables/verify/siac/cts/output/cta/v2.11.b/main.cpp)
target_include_directories(verify_siac_cts_output_cta_v2.11.b PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/siac/cts/output/cta/v2.11.b)
target_link_libraries(verify_siac_cts_output_cta_v2.11.b PRIVATE classes_siac_cts_output_cta_v2.11.b)
add_executable(benchmark_siac_cts_output_cta_v2.11.b executables/benchmark/siac/cts/output/cta/v2.11.b/main.cpp)
target_include_directories(benchmark_siac_cts_output_cta_v2.11.b PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/siac/cts/output/cta/v2.11.b)
add_executable(statistics_siac_cqs_output_cta_v2.10.a executables/statistics/siac/cqs/output/cta/v2.10.a/main.cpp)
target_include_directories(statistics_siac_cqs_output_cta_v2.10.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/siac/cqs/output/cta/v2.10.a)
add_executable(extractor_siac_cqs_output_cta_v2.10.a executables/extractor/siac/cqs/output/cta/v2.10.a/main.cpp)
target_include_directories(extractor_siac_cqs_output_cta_v2.10.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/siac/cqs/output/cta/v2.10.a)
add_executable(dump_siac_cqs_output_cta_v2.10.a executables/dump/siac/cqs/output/cta/v2.10.a/main.cpp)
target_include_directories(dump_siac_cqs_output_cta_v2.10.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/siac/cqs/output/cta/v2.10.a)
target_link_libraries(dump_siac_cqs_output_cta_v2.10.a PRIVATE classes_siac_cqs_output_cta_v2.10.a)
add_executable(verify_siac_cqs_output_cta_v2.10.a executables/verify/siac/cqs/output/cta/v2.10.a/main.cpp)
target_include_directories(verify_siac_cqs_output_cta_v2.10.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/siac/cqs/output/cta/v2.10.a)
target_link_libraries(verify_siac_cqs_output_cta_v2.10.a PRIVATE classes_siac_cqs_output_cta_v2.10.a)
add_executable(benchmark_siac_cqs_output_cta_v2.10.a executables/benchmark/siac/cqs/output/cta/v2.10.a/main.cpp)
target_include_directories(benchmark_siac_cqs_output_cta_v2.10.a PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/benchmark/siac/cqs/output/cta/v2.10.a)
# Corpus-driven tests, one family per format under tests/, each through the surface that
# format's program uses: modern through the packet iterator, advanced through the session
# layer, classes through the Packet's decode and encode. The test programs are built by
# every build, so a clean build compiles them the way it compiles checks/ — a generated
# test that does not build is a generator fault and shows up without a capture in sight.
add_executable(modern_iex_iexequities_deep_iextp_v1.06_test tests/modern/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(modern_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deep_iextp_v1.06_test tests/advanced/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(advanced_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deep_iextp_v1.06_test tests/classes/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deep_iextp_v1.06_test PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(modern_iex_iexequities_deep_iextp_v1.08_test tests/modern/iex_iexequities_deep_iextp_v1.08.cpp)
target_include_directories(modern_iex_iexequities_deep_iextp_v1.08_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deep_iextp_v1.08_test tests/advanced/iex_iexequities_deep_iextp_v1.08.cpp)
target_include_directories(advanced_iex_iexequities_deep_iextp_v1.08_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deep_iextp_v1.08_test tests/classes/iex_iexequities_deep_iextp_v1.08.cpp)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.08_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deep_iextp_v1.08_test PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(modern_iex_iexequities_deepplus_iextp_v1.01_test tests/modern/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(modern_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deepplus_iextp_v1.01_test tests/advanced/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(advanced_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deepplus_iextp_v1.01_test tests/classes/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(modern_iex_iexequities_deepplus_iextp_v1.05_test tests/modern/iex_iexequities_deepplus_iextp_v1.05.cpp)
target_include_directories(modern_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deepplus_iextp_v1.05_test tests/advanced/iex_iexequities_deepplus_iextp_v1.05.cpp)
target_include_directories(advanced_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deepplus_iextp_v1.05_test tests/classes/iex_iexequities_deepplus_iextp_v1.05.cpp)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE classes_iex_iexequities_deepplus_iextp_v1.05)
add_executable(modern_iex_iexequities_tops_iextp_v1.56_test tests/modern/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.56_test tests/advanced/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.56_test tests/classes/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.56_test PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(modern_iex_iexequities_tops_iextp_v1.64_test tests/modern/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.64_test tests/advanced/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.64_test tests/classes/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.64_test PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(modern_iex_iexequities_tops_iextp_v1.66_test tests/modern/iex_iexequities_tops_iextp_v1.66.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.66_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.66_test tests/advanced/iex_iexequities_tops_iextp_v1.66.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.66_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.66_test tests/classes/iex_iexequities_tops_iextp_v1.66.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.66_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.66_test PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(modern_jpx_tseequities_marketbyorder_flex_v1.1_test tests/modern/jpx_tseequities_marketbyorder_flex_v1.1.cpp)
target_include_directories(modern_jpx_tseequities_marketbyorder_flex_v1.1_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_jpx_tseequities_marketbyorder_flex_v1.1_test tests/classes/jpx_tseequities_marketbyorder_flex_v1.1.cpp)
target_include_directories(classes_jpx_tseequities_marketbyorder_flex_v1.1_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_jpx_tseequities_marketbyorder_flex_v1.1_test PRIVATE classes_jpx_tseequities_marketbyorder_flex_v1.1)
add_executable(modern_nasdaq_nsmequities_totalview_itch_v5.0.2023_test tests/modern/nasdaq_nsmequities_totalview_itch_v5.0.2023.cpp)
target_include_directories(modern_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023_test tests/advanced/nasdaq_nsmequities_totalview_itch_v5.0.2023.cpp)
target_include_directories(advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test tests/classes/nasdaq_nsmequities_totalview_itch_v5.0.2023.cpp)
target_include_directories(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2023)

# Running them reads the captures each protocol declares, and each program is run on its
# protocol's first declared capture. Point OMI_PACKETS_DIR at the corpus checkout:
#
#   cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/packets
#   cmake --build build --parallel && ctest --test-dir build
set(OMI_PACKETS_DIR "" CACHE PATH "Packet corpus checkout holding the capture samples")

if(OMI_PACKETS_DIR)
  enable_testing()

  add_test(NAME modern_iex_iexequities_deep_iextp_v1.06 COMMAND modern_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(modern_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deep_iextp_v1.06 COMMAND advanced_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(advanced_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deep_iextp_v1.06 COMMAND classes_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(classes_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deep_iextp_v1.08 COMMAND modern_iex_iexequities_deep_iextp_v1.08_test)
  set_tests_properties(modern_iex_iexequities_deep_iextp_v1.08 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deep_iextp_v1.08 COMMAND advanced_iex_iexequities_deep_iextp_v1.08_test)
  set_tests_properties(advanced_iex_iexequities_deep_iextp_v1.08 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deep_iextp_v1.08 COMMAND classes_iex_iexequities_deep_iextp_v1.08_test)
  set_tests_properties(classes_iex_iexequities_deep_iextp_v1.08 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deepplus_iextp_v1.01 COMMAND modern_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(modern_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deepplus_iextp_v1.01 COMMAND advanced_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(advanced_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deepplus_iextp_v1.01 COMMAND classes_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(classes_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deepplus_iextp_v1.05 COMMAND modern_iex_iexequities_deepplus_iextp_v1.05_test)
  set_tests_properties(modern_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deepplus_iextp_v1.05 COMMAND advanced_iex_iexequities_deepplus_iextp_v1.05_test)
  set_tests_properties(advanced_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deepplus_iextp_v1.05 COMMAND classes_iex_iexequities_deepplus_iextp_v1.05_test)
  set_tests_properties(classes_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.56 COMMAND modern_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.56 COMMAND advanced_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.56 COMMAND classes_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.64 COMMAND modern_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.64 COMMAND advanced_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.64 COMMAND classes_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.66 COMMAND modern_iex_iexequities_tops_iextp_v1.66_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.66 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.66 COMMAND advanced_iex_iexequities_tops_iextp_v1.66_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.66 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.66 COMMAND classes_iex_iexequities_tops_iextp_v1.66_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.66 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND modern_jpx_tseequities_marketbyorder_flex_v1.1_test)
  set_tests_properties(modern_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND classes_jpx_tseequities_marketbyorder_flex_v1.1_test)
  set_tests_properties(classes_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND modern_nasdaq_nsmequities_totalview_itch_v5.0.2023_test)
  set_tests_properties(modern_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023_test)
  set_tests_properties(advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test)
  set_tests_properties(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME statistics_iex_iexequities_deep_iextp_v1.06 COMMAND statistics_iex_iexequities_deep_iextp_v1.06 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.06_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deep_iextp_v1.06)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.06_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deep_iextp_v1.06_samples)
  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.06 COMMAND extractor_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deep_iextp_v1.06)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deep_iextp_v1.06_samples)

  add_test(NAME dump_iex_iexequities_deep_iextp_v1.06 COMMAND dump_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_deep_iextp_v1.06 COMMAND verify_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_deep_iextp_v1.06 COMMAND benchmark_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_iex_iexequities_deep_iextp_v1.08 COMMAND statistics_iex_iexequities_deep_iextp_v1.08 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.08_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deep_iextp_v1.08)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.08_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deep_iextp_v1.08_samples)
  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.08 COMMAND extractor_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deep_iextp_v1.08)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deep_iextp_v1.08_samples)

  add_test(NAME dump_iex_iexequities_deep_iextp_v1.08 COMMAND dump_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_deep_iextp_v1.08 COMMAND verify_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_deep_iextp_v1.08 COMMAND benchmark_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_iex_iexequities_deepplus_iextp_v1.01 COMMAND statistics_iex_iexequities_deepplus_iextp_v1.01 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap)
  set_tests_properties(statistics_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "TradeBreakMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.01_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deepplus_iextp_v1.01)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.01_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deepplus_iextp_v1.01_samples)
  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.01 COMMAND extractor_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deepplus_iextp_v1.01)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deepplus_iextp_v1.01_samples)

  add_test(NAME dump_iex_iexequities_deepplus_iextp_v1.01 COMMAND dump_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap)
  set_tests_properties(dump_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "TradeBreakMessage")

  add_test(NAME verify_iex_iexequities_deepplus_iextp_v1.01 COMMAND verify_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap)
  set_tests_properties(verify_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_deepplus_iextp_v1.01 COMMAND benchmark_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_iex_iexequities_deepplus_iextp_v1.05 COMMAND statistics_iex_iexequities_deepplus_iextp_v1.05 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.05_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deepplus_iextp_v1.05)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.05_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deepplus_iextp_v1.05_samples)
  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.05 COMMAND extractor_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deepplus_iextp_v1.05)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deepplus_iextp_v1.05_samples)

  add_test(NAME dump_iex_iexequities_deepplus_iextp_v1.05 COMMAND dump_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderMessage")

  add_test(NAME verify_iex_iexequities_deepplus_iextp_v1.05 COMMAND verify_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap)
  set_tests_properties(verify_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_deepplus_iextp_v1.05 COMMAND benchmark_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.56 COMMAND statistics_iex_iexequities_tops_iextp_v1.56 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.56_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.56)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.56_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.56_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.56 COMMAND extractor_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.56)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.56_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.56 COMMAND dump_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage")

  add_test(NAME verify_iex_iexequities_tops_iextp_v1.56 COMMAND verify_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(verify_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_tops_iextp_v1.56 COMMAND benchmark_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.64 COMMAND statistics_iex_iexequities_tops_iextp_v1.64 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.64_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.64)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.64_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.64_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.64 COMMAND extractor_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.64)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.64_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.64 COMMAND dump_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_tops_iextp_v1.64 COMMAND verify_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_tops_iextp_v1.64 COMMAND benchmark_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.66 COMMAND statistics_iex_iexequities_tops_iextp_v1.66 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.66_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.66)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.66_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.66_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.66 COMMAND extractor_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.66)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.66_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.66 COMMAND dump_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_tops_iextp_v1.66 COMMAND verify_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_iex_iexequities_tops_iextp_v1.66 COMMAND benchmark_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap 1)
  set_tests_properties(benchmark_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND statistics_jpx_tseequities_marketbyorder_flex_v1.1 -i ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap)
  set_tests_properties(statistics_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "CommunicationControlMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_jpx_tseequities_marketbyorder_flex_v1.1_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_jpx_tseequities_marketbyorder_flex_v1.1)
  set_tests_properties(extractor_jpx_tseequities_marketbyorder_flex_v1.1_directory PROPERTIES FIXTURES_SETUP extractor_jpx_tseequities_marketbyorder_flex_v1.1_samples)
  add_test(NAME extractor_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND extractor_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap ${CMAKE_BINARY_DIR}/samples/jpx_tseequities_marketbyorder_flex_v1.1)
  set_tests_properties(extractor_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_jpx_tseequities_marketbyorder_flex_v1.1_samples)

  add_test(NAME dump_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND dump_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap)
  set_tests_properties(dump_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "CommunicationControlMessage")

  add_test(NAME verify_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND verify_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap)
  set_tests_properties(verify_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND benchmark_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap 1)
  set_tests_properties(benchmark_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")

  add_test(NAME statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 -i ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap)
  set_tests_properties(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderNoMpidAttributionMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023)
  set_tests_properties(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_directory PROPERTIES FIXTURES_SETUP extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_samples)
  add_test(NAME extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap ${CMAKE_BINARY_DIR}/samples/nasdaq_nsmequities_totalview_itch_v5.0.2023)
  set_tests_properties(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_samples)

  add_test(NAME dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap)
  set_tests_properties(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderNoMpidAttributionMessage")

  add_test(NAME verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap)
  set_tests_properties(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap 1)
  set_tests_properties(benchmark_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION ", 0 did not parse")
endif()
