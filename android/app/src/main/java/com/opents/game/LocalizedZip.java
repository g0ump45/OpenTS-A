package com.opents.game;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.zip.*;

final class LocalizedZip {
    static void install(File work, File stage, String language, FreewareExtractor.Progress progress) throws IOException {
        FreewarePackage pack = LocalizedZipManifest.get(language);
        File complete = new File(work, pack.sha256 + ".complete");
        if (complete.isFile()) return;
        File source = new File(work, pack.name + ".part");
        long needed = Math.max(0, pack.bytes - source.length());
        for (FreewarePackage.Entry entry : pack.entries) needed += entry.bytes;
        if (work.getUsableSpace() < needed + 128L * 1024 * 1024)
            throw new IOException("Not enough storage for " + pack.label + ". Free space and retry.");
        FreewareDownloader.download(pack, source, progress);
        try {
            FreewareExtractor.verify(source, pack, progress);
            extract(source, stage, pack.entries, progress);
        } catch (IOException error) {
            if (source.length() == pack.bytes && error.getMessage() != null
                && error.getMessage().startsWith("Source package changed")) source.delete();
            throw error;
        }
        if (!complete.createNewFile()) throw new IOException("Cannot record language setup.");
        source.delete();
    }

    static void extract(File source, File stage, FreewarePackage.Entry[] entries,
                        FreewareExtractor.Progress progress) throws IOException {
        Map<String, FreewarePackage.Entry> expected = new HashMap<>();
        for (FreewarePackage.Entry entry : entries) {
            if (!entry.name.equals(GameFilePolicy.destinationName(entry.name)) || entry.bytes <= 0
                || entry.bytes > GameFilePolicy.MAX_BYTES || expected.put(entry.name, entry) != null)
                throw new IOException("Invalid language manifest.");
        }
        Set<String> seen = new HashSet<>();
        try (ZipFile zip = new ZipFile(source)) {
            if (zip.size() > 10000) throw new IOException("Too many language archive entries.");
            Enumeration<? extends ZipEntry> listing = zip.entries();
            while (listing.hasMoreElements()) {
                ZipEntry item = listing.nextElement();
                FreewarePackage.Entry entry = expected.get(item.getName());
                if (entry == null || item.isDirectory() || !seen.add(item.getName())
                    || item.getSize() != entry.bytes || item.getCrc() != entry.crc)
                    throw new IOException("Unexpected language archive entry: " + item.getName());
                File temp = File.createTempFile(".language-", ".tmp", stage);
                try {
                    CRC32 crc = new CRC32();
                    long copied = 0;
                    try (InputStream input = zip.getInputStream(item); FileOutputStream output = new FileOutputStream(temp)) {
                        byte[] buffer = new byte[65536];
                        int length;
                        while ((length = input.read(buffer)) != -1) {
                            progress.update("Unpacking " + entry.name + ": " + copied * 100 / entry.bytes + "%");
                            if (length > entry.bytes - copied) throw new IOException("Oversized language file.");
                            output.write(buffer, 0, length); crc.update(buffer, 0, length); copied += length;
                        }
                        output.getFD().sync();
                    }
                    if (copied != entry.bytes || crc.getValue() != entry.crc)
                        throw new IOException("Language file failed verification: " + entry.name);
                    Files.move(temp.toPath(), new File(stage, entry.name).toPath(), StandardCopyOption.REPLACE_EXISTING);
                } finally { temp.delete(); }
            }
        }
        if (seen.size() != expected.size()) throw new IOException("Missing language archive files.");
    }
}
