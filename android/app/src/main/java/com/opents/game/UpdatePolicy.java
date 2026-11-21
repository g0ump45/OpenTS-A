package com.opents.game;

import java.io.IOException;
import java.net.URI;

final class UpdatePolicy {
    static final long MAX_APK = 64L * 1024 * 1024;
    static int compare(String left, String right) throws IOException {
        int[] a = version(left), b = version(right);
        for (int i = 0; i < 3; i++) if (a[i] != b[i]) return Integer.compare(a[i], b[i]);
        boolean previewA = left.contains("-"), previewB = right.contains("-");
        return previewA == previewB ? 0 : previewA ? -1 : 1;
    }
    private static int[] version(String text) throws IOException {
        if (!text.matches("v?[0-9]+\\.[0-9]+(?:\\.[0-9]+)?(?:-[A-Za-z0-9.-]+)?")) throw new IOException("Unsupported release version.");
        String[] parts = text.replaceFirst("^v", "").split("-", 2)[0].split("\\.");
        int[] result = new int[3];
        try { for (int i = 0; i < parts.length; i++) result[i] = Integer.parseInt(parts[i]); }
        catch (NumberFormatException e) { throw new IOException("Unsupported release version."); }
        return result;
    }
    static void asset(String url, long size, String digest) throws IOException {
        URI uri;
        try { uri = URI.create(url); } catch (IllegalArgumentException e) { throw new IOException("Invalid APK address."); }
        if (!"https".equals(uri.getScheme()) || !"github.com".equals(uri.getHost())
            || uri.getUserInfo() != null || uri.getPort() != -1 || uri.getQuery() != null
            || uri.getFragment() != null || !uri.normalize().equals(uri) || !uri.getPath().startsWith("/g0ump45/OpenTS-A/releases/download/")
            || !uri.getPath().endsWith(".apk") || size <= 0 || size > MAX_APK
            || !digest.matches("sha256:[0-9a-f]{64}")) throw new IOException("Release APK metadata is invalid or missing its checksum.");
    }
}
