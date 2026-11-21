package com.opents.game;

import java.io.*;
import java.nio.file.*;
import java.security.*;
import java.util.*;
import java.util.zip.CRC32;
import org.tukaani.xz.LZMAInputStream;

final class FreewareExtractor {
    interface Progress { void update(String message) throws IOException; }

    static void verify(File archive, FreewarePackage pack, Progress progress) throws IOException {
        if (archive.length() != pack.bytes) throw new IOException("Incomplete " + pack.label + " download.");
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            try (InputStream input = new FileInputStream(archive)) {
                byte[] buffer = new byte[65536]; int length;
                while ((length = input.read(buffer)) != -1) {
                    progress.update("Checking " + pack.label + "...");
                    digest.update(buffer, 0, length);
                }
            }
            StringBuilder hash = new StringBuilder();
            for (byte value : digest.digest()) hash.append(String.format(Locale.ROOT, "%02x", value & 255));
            if (!pack.sha256.equals(hash.toString())) throw new IOException("Source package changed or failed verification: " + pack.label);
        } catch (NoSuchAlgorithmException e) { throw new IOException(e); }
    }

    static void extract(File archive, File stage, FreewarePackage pack, Progress progress) throws IOException {
        verify(archive, pack, progress);
        try (InputStream file = new BufferedInputStream(new FileInputStream(archive))) {
            discard(file, pack.streamOffset, progress);
            try (LZMAInputStream input = new LZMAInputStream(new LimitedInput(file, pack.packedBytes),
                    -1L, (byte)pack.properties, pack.dictionary)) {
                long position = 0;
                byte[] buffer = new byte[65536];
                for (FreewarePackage.Entry entry : pack.entries) {
                    if (!entry.name.equals(GameFilePolicy.destinationName(entry.name)) || entry.offset < position
                        || entry.bytes <= 0 || entry.bytes > GameFilePolicy.MAX_BYTES)
                        throw new IOException("Invalid extraction manifest.");
                    discard(input, entry.offset - position, progress);
                    progress.update("Unpacking " + entry.name + "...");
                    File temp = File.createTempFile(".unpack-", ".tmp", stage);
                    try {
                        CRC32 crc = new CRC32(); long remaining = entry.bytes;
                        try (FileOutputStream output = new FileOutputStream(temp)) {
                            while (remaining > 0) {
                                progress.update("Unpacking " + entry.name + ": " + ((entry.bytes - remaining) * 100 / entry.bytes) + "%");
                                int length = input.read(buffer, 0, (int)Math.min(buffer.length, remaining));
                                if (length < 0) throw new EOFException("Truncated " + entry.name);
                                output.write(buffer, 0, length); crc.update(buffer, 0, length); remaining -= length;
                            }
                            output.getFD().sync();
                        }
                        if (crc.getValue() != entry.crc) throw new IOException("Unpacked file failed verification: " + entry.name);
                        Files.move(temp.toPath(), new File(stage, entry.name).toPath(), StandardCopyOption.REPLACE_EXISTING);
                    } finally { temp.delete(); }
                    position = entry.offset + entry.bytes;
                }
            }
        }
    }

    private static void discard(InputStream input, long bytes, Progress progress) throws IOException {
        byte[] buffer = new byte[65536];
        while (bytes > 0) {
            progress.update("Reading compressed game data...");
            int length = input.read(buffer, 0, (int)Math.min(buffer.length, bytes));
            if (length < 0) throw new EOFException("Truncated compressed data.");
            bytes -= length;
        }
    }

    private static final class LimitedInput extends FilterInputStream {
        long remaining;
        LimitedInput(InputStream input, long remaining) { super(input); this.remaining = remaining; }
        @Override public int read() throws IOException {
            if (remaining == 0) return -1;
            int value = in.read(); if (value >= 0) remaining--; return value;
        }
        @Override public int read(byte[] bytes, int offset, int length) throws IOException {
            if (remaining == 0) return -1;
            int count = in.read(bytes, offset, (int)Math.min(length, remaining));
            if (count > 0) remaining -= count; return count;
        }
    }
}
