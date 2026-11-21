package com.opents.game;

final class FreewarePackage {
    final String name, label, url, sha256;
    final long bytes, streamOffset, packedBytes;
    final int properties, dictionary;
    final Entry[] entries;

    FreewarePackage(String name, String label, String url, long bytes, String sha256,
                    long streamOffset, long packedBytes, int properties, int dictionary, Entry[] entries) {
        this.name = name; this.label = label; this.url = url; this.bytes = bytes;
        this.sha256 = sha256; this.streamOffset = streamOffset; this.packedBytes = packedBytes;
        this.properties = properties; this.dictionary = dictionary; this.entries = entries;
    }

    static final class Entry {
        final String name;
        final long offset, bytes, crc;
        Entry(String name, long offset, long bytes, long crc) {
            this.name = name; this.offset = offset; this.bytes = bytes; this.crc = crc;
        }
    }
}
