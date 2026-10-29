# Advanced C++ Parsers

Packed structs laid over the wire bytes: a message is `parse`d in place and read through its
fields, with `static_assert`s fixing every offset and size at compile time.

Each protocol has its own directory, named for its identifier with the version as the last
segment — `Iex.IexEquities.Tops.IexTp.v1.64` becomes `iex/iexequities/tops/iextp/v1.64` —
matching the C++ namespace the code declares.

Within a protocol:

- `types/` — one header per field type, each wrapping the wire bytes with a `get()` accessor
- `structs/` — the packet and message headers those fields compose into
- `messages/` — one header per message, plus `Definitions.hpp` (aggregate), `dispatch.hpp`
  (a template dispatch over the message type) and `Format.hpp` (`operator<<` per message)
- `cache/` — support headers the generated code relies on
- `TypesAll.hpp` — every type in one include

## Protocols (98)

- `Asx.AsxDerivatives.Ntp.Itch.v1.05`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v1.6`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v1.7`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v1.8`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v1.9`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v2.1`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v2.2`
- `B3.B3Derivatives.BinaryUmdf.Sbe.v2.3`
- `B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.0`
- `B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1`
- `B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3`
- `Bse.BseIndia.Eobi.Fbe.v1.4`
- `Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29`
- `Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80`
- `Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22`
- `Cboe.ByxEquities.MulticastDepthOfBook.Pitch.v2.41.29`
- `Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4`
- `Cboe.C1Options.Complex.Pitch.v2.1.18`
- `Cboe.C1Options.MulticastDepthOfBook.Pitch.v2.39.4`
- `Cboe.C1Options.MarketDataFeed.Csm.v1.4.2`
- `Cboe.EdgaEquities.MulticastDepthOfBook.Pitch.v2.41.29`
- `Cboe.EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29`
- `CixAts.CixAspen.MarketDataFeed.Aspen.v1.4`
- `Cme.Globex.Mdp3.Sbe.v1.8`
- `Cme.Globex.Mdp3.Sbe.v1.9`
- `Cme.Globex.Mdp3.Sbe.v1.13`
- `Cme.Globex.Mdp3.Sbe.v1.5`
- `Eurex.T7.Eobi.Fbe.v13.0`
- `Eurex.T7.Eobi.Fbe.v15.0`
- `Eurex.T7.Eobi.Fbe.v3.0`
- `Eurex.T7.Eobi.Fbe.v6.0`
- `Iex.IexEquities.Deep.IexTp.v1.06`
- `Iex.IexEquities.Deep.IexTp.v1.08`
- `Iex.IexEquities.Deep.Snap.v1.6`
- `Iex.IexEquities.DeepPlus.IexTp.v1.01`
- `Iex.IexEquities.DeepPlus.IexTp.v1.05`
- `Iex.IexEquities.DeepPlus.Snap.v1.06`
- `Iex.IexEquities.Tops.IexTp.v1.56`
- `Iex.IexEquities.Tops.IexTp.v1.64`
- `Iex.IexEquities.Tops.IexTp.v1.66`
- `Iex.IexEquities.Tops.Snap.v1.6`
- `Jnx.JnxEquities.Pts.Itch.v1.6`
- `Jnx.JnxEquities.Pts.Itch.v1.7`
- `Jnx.JnxEquities.Pts.Ouch.v1.11`
- `Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6`
- `Jpx.TseEquities.MarketByOrder.Flex.v1.1`
- `Lseg.Lse.Level2Mbo.Gtp.v26.2`
- `Lseg.Millennium.Level2.Mitch.v11.9`
- `Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3`
- `Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d`
- `Miax.MiaxOptions.TopOfMarket.Mach.v2.5`
- `Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1`
- `Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b`
- `Nasdaq.NsmEquities.TotalView.Itch.v5.0.2017`
- `Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023`
- `Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026`
- `Nasdaq.NsmEquities.Qbbo.Itch.v2.1`
- `Nasdaq.NomOptions.Itto.Itch.v4.0.2025`
- `Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4`
- `Nasdaq.NordicEquities.TotalView.Itch.v3.04.X`
- `Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1`
- `Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0`
- `Nasdaq.NsmEquities.NlsPlus.Itch.v3.0`
- `Nasdaq.NsmEquities.TotalView.Itch.v4.0`
- `Nasdaq.NtxEquities.TotalView.Itch.v5.0`
- `Nasdaq.PsxEquities.TotalView.Itch.v5.0`
- `Nyse.ArcaEquities.IntegratedFeed.Pillar.v2.5.g`
- `Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m`
- `Nyse.NyseEquities.IntegratedFeed.Xdp.v2.3.a`
- `Nyse.AmexEquities.IntegratedFeed.Pillar.v2.5.g`
- `Nyse.AmexEquities.IntegratedFeed.Xdp.v2.1.g`
- `Nyse.AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g`
- `Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a`
- `Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a`
- `Nyse.ArcaEquities.Bbo.Xdp.v2.4.c`
- `Nyse.ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g`
- `Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c`
- `Nyse.NationalEquities.Bbo.Pillar.v2.5.d`
- `Nyse.NationalEquities.Trades.Pillar.v2.6`
- `Nyse.NyseEquities.Bbo.Pillar.v2.5.b`
- `Nyse.NyseEquities.Bbo.Xdp.v2.4.g`
- `Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.1.f`
- `Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a`
- `Nyse.NyseEquities.IntegratedFeed.Pillar.v2.5.g`
- `Nyse.NyseEquities.IntegratedFeed.Xdp.v2.1.g`
- `Nyse.NyseEquities.IntegratedFeedRefresh.Pillar.v2.5.g`
- `Nyse.NyseEquities.IntegratedFeedRetransmission.Pillar.v2.5.g`
- `Nyse.TexasEquities.IntegratedFeed.Pillar.v2.5.g`
- `Nyse.TexasEquities.IntegratedFeedRefresh.Pillar.v2.5.g`
- `OtcMarkets.LinkAts.Multicast.Link.v4.3`
- `Siac.Opra.Output.Obi.v6.2`
- `Siac.Cts.Output.Cta.v2.11.b`
- `Siac.Cqs.Output.Cta.v2.10.a`
- `Siac.Cqs.Output.Cta.v1.91`
- `Siac.Cts.Output.Cta.v1.91`
- `Siac.Cts.Output.Cta.v2.10`
- `Siac.Cts.Output.Cta.v2.9`
- `Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10`

Regenerated by `Generate.Cpp.Protocols.Repository`; do not edit by hand.
