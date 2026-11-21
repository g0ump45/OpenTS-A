package com.opents.game;

import java.io.IOException;
import java.net.URL;
import java.util.regex.*;

final class SpanishDownloadLink {
    static String find(String page) throws IOException {
        Matcher anchors = Pattern.compile("<a\\b(?:[^\"'<>]|\"[^\"]*\"|'[^']*')*>", Pattern.CASE_INSENSITIVE).matcher(page);
        while (anchors.find()) {
            String tag = anchors.group();
            if (!Pattern.compile("\\bid\\s*=\\s*[\"']downloadButton[\"']", Pattern.CASE_INSENSITIVE).matcher(tag).find()) continue;
            Matcher href = Pattern.compile("\\bhref\\s*=\\s*[\"']([^\"']+)[\"']", Pattern.CASE_INSENSITIVE).matcher(tag);
            if (!href.find()) break;
            URL url = new URL(new URL(SpanishManifest.PAGE), href.group(1).replace("&amp;", "&"));
            if (!"https".equals(url.getProtocol()) || url.getUserInfo() != null
                || (url.getPort() != -1 && url.getPort() != 443)) throw new IOException("Unexpected Spanish download server.");
            if (direct(url) || (url.getHost().equals("www.mediafire.com")
                && url.getPath().equals(new URL(SpanishManifest.PAGE).getPath()))) return url.toString();
            throw new IOException("Unexpected Spanish download server.");
        }
        throw new IOException("Spanish download link changed. Retry later.");
    }

    static boolean direct(URL url) {
        return url.getHost().matches("download[0-9]+\\.mediafire\\.com");
    }
}
