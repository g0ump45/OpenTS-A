package com.opents.game;

import java.io.*;
import java.net.*;

final class FreewareDownloader {
    static void download(FreewarePackage pack, File target, FreewareExtractor.Progress progress) throws IOException {
        if (target.length() > pack.bytes && !target.delete()) throw new IOException("Cannot reset download.");
        long offset = target.length();
        if (offset == pack.bytes) return;
        URL url = new URL(pack.url);
        HttpURLConnection connection = null;
        try {
            for (int hop = 0; hop <= 8; hop++) {
                if (!"https".equals(url.getProtocol())) throw new IOException("Download requires HTTPS.");
                progress.update("Connecting: " + pack.label + "...");
                connection = (HttpURLConnection)url.openConnection();
                connection.setInstanceFollowRedirects(false);
                connection.setConnectTimeout(30000); connection.setReadTimeout(30000);
                connection.setRequestProperty("User-Agent", "OpenTS-A/1.3 (Android game-file setup)");
                connection.setRequestProperty("Accept-Encoding", "identity");
                if (offset > 0) connection.setRequestProperty("Range", "bytes=" + offset + "-");
                int code = connection.getResponseCode();
                if (code == 301 || code == 302 || code == 303 || code == 307 || code == 308) {
                    String location = connection.getHeaderField("Location");
                    connection.disconnect(); connection = null;
                    if (location == null || hop == 8) throw new IOException("Invalid download redirect.");
                    url = new URL(url, location); continue;
                }
                if (code == 200) offset = 0;
                else if (code != 206 || offset == 0
                    || !(
                        "bytes " + offset + "-" + (pack.bytes - 1) + "/" + pack.bytes).equals(connection.getHeaderField("Content-Range")))
                    throw new IOException("Download server returned HTTP " + code + ". Retry later.");
                long length = connection.getContentLengthLong();
                if (length >= 0 && length != pack.bytes - offset) throw new IOException("Source package size changed: " + pack.label);
                try (InputStream input = connection.getInputStream();
                     FileOutputStream output = new FileOutputStream(target, offset > 0)) {
                    byte[] bytes = new byte[65536]; int count;
                    while ((count = input.read(bytes)) != -1) {
                        progress.update("Downloading " + pack.label + ": " + (offset * 100 / pack.bytes)
                            + "%\n" + (offset / 1000000) + " / " + (pack.bytes / 1000000) + " MB");
                        if (offset + count > pack.bytes) throw new IOException("Source package is larger than expected.");
                        output.write(bytes, 0, count); offset += count;
                    }
                    output.getFD().sync();
                }
                if (offset != pack.bytes) throw new IOException("Download interrupted. Retry to resume.");
                return;
            }
            throw new IOException("Too many download redirects.");
        } finally { if (connection != null) connection.disconnect(); }
    }
}
