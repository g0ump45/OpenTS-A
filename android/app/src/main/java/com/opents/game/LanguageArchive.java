package com.opents.game;

import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.regex.*;

final class LanguageArchive {
    private static native void extract(String source, String directory, String[] paths,
        String[] names, long[] lengths, FreewareExtractor.Progress progress) throws IOException;

    private static String page(String address, FreewareExtractor.Progress progress) throws IOException {
        progress.update("Finding Spanish language download...");
        HttpURLConnection connection = (HttpURLConnection)new URL(address).openConnection();
        connection.setConnectTimeout(30000); connection.setReadTimeout(30000);
        connection.setInstanceFollowRedirects(false);
        connection.setRequestProperty("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36");
        try {
            if (connection.getResponseCode() != 200) throw new IOException("Spanish download page is unavailable. Retry later.");
            ByteArrayOutputStream bytes = new ByteArrayOutputStream();
            try (InputStream input = connection.getInputStream()) {
                byte[] buffer = new byte[8192]; int read;
                while ((read = input.read(buffer)) != -1) {
                    progress.update("Finding Spanish language download...");
                    if (bytes.size() + read > 2 * 1024 * 1024) throw new IOException("Spanish download page changed.");
                    bytes.write(buffer, 0, read);
                }
            }
            return bytes.toString(StandardCharsets.UTF_8.name());
        } finally { connection.disconnect(); }
    }

    private static String resolve(FreewareExtractor.Progress progress) throws IOException {
        String address = SpanishManifest.PAGE;
        for (int hop = 0; hop < 3; hop++) {
            address = SpanishDownloadLink.find(page(address, progress));
            if (SpanishDownloadLink.direct(new URL(address))) return address;
        }
        throw new IOException("Spanish download link is unavailable. Retry later.");
    }

    static void install(File work, File stage, FreewareExtractor.Progress progress) throws IOException {
        File complete = new File(work, "spanish-" + SpanishManifest.SHA256 + ".complete");
        if (complete.isFile()) return;
        File source = new File(work, "spanish.rar.part");
        long needed = Math.max(0, SpanishManifest.BYTES - source.length());
        for (SpanishManifest.Entry entry : SpanishManifest.ENTRIES) needed += entry.bytes;
        if (work.getUsableSpace() < needed + 128L * 1024 * 1024) throw new IOException("Not enough storage for Spanish. Allow about 4 GB free and retry.");
        String address = source.length() == SpanishManifest.BYTES ? SpanishManifest.PAGE : resolve(progress);
        FreewarePackage pack = new FreewarePackage("spanish.rar", "Spanish language", address,
            SpanishManifest.BYTES, SpanishManifest.SHA256, 0, 0, 0, 0, new FreewarePackage.Entry[0]);
        FreewareDownloader.download(pack, source, progress);
        try { FreewareExtractor.verify(source, pack, progress); }
        catch (IOException e) {
            if (source.length() == pack.bytes && e.getMessage() != null
                && e.getMessage().startsWith("Source package changed")) source.delete();
            throw e;
        }
        String[] paths = new String[SpanishManifest.ENTRIES.length], names = new String[paths.length];
        long[] lengths = new long[paths.length];
        for (int i = 0; i < paths.length; i++) {
            paths[i] = SpanishManifest.ENTRIES[i].path; names[i] = SpanishManifest.ENTRIES[i].name;
            lengths[i] = SpanishManifest.ENTRIES[i].bytes;
        }
        System.loadLibrary("opents_language_archive");
        extract(source.getAbsolutePath(), stage.getAbsolutePath(), paths, names, lengths, progress);
        if (!complete.createNewFile()) throw new IOException("Cannot record Spanish language setup.");
        source.delete();
    }
}
