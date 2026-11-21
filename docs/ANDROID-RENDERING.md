# Android rendering checks

Depth and alpha buffer resets clear every requested 16-bit entry, including a
single entry aligned to four bytes. Callers still split runs at the ring-buffer
boundary. Buffer layouts, drawing order and pan offsets are unchanged.

The previous reset left an aligned single-entry run untouched. Region redraws
or ring-boundary splits could retain stale depth or alpha at that entry. The
current fill also avoids 32-bit aliasing and signed overflow while packing
maximum depth values.

Host checks cover both buffer reset methods at both 16-bit alignments, zero,
single-entry, odd and even lengths, and depth/alpha values. Guard entries detect
writes outside the requested run. These checks use synthetic data.

Players have reported bridges disappearing while panning in the first GDI
mission and incorrect unit layering behind structures in the second. The reset
fix is not yet confirmed to resolve those reports. Device testing must check
both missions while panning, with units passing behind structures, before
claiming the reported glitches are resolved.

Android full background rebuilds now advance the bridge redraw counter before
clearing depth and alpha. Scrolling can rebuild the background more than once
within one simulation frame; the bridge draw cache must not skip the new draw
after its previous pixels have been replaced by terrain. This uses the existing
redraw counter and leaves save layouts, simulation and desktop drawing unchanged.

The earlier buffer reset fix did not resolve bridge flashing in the reported
device test. The player confirmed that the bridge cache correction resolves the reported
bridge flashing in v1.3.7. Unit layering behind structures remains unconfirmed.

A synthetic host check exercises the production bridge cache condition and
redraw increment across repeated rebuilds in one simulation frame, including
all 256 initial counter values and wraparound. It passes; it does not render
game assets or establish the result on a device.
