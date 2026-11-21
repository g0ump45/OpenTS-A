package com.opents.game;
import java.io.IOException;
public class SpanishDownloadLinkTest {
    static void rejects(String page) throws Exception {
        try { SpanishDownloadLink.find(page); throw new AssertionError("Unsafe link accepted"); }
        catch (IOException expected) { }
    }
    public static void main(String[] args) throws Exception {
        String expected = "https://download1514.mediafire.com/test/pack.rar";
        String tag = "<a onclick=\"setTimeout(() => {}, 1000)\"\n id = 'downloadButton' href = '" + expected + "'>";
        if (!SpanishDownloadLink.find(tag).equals(expected)) throw new AssertionError();
        String next = "<a href='//www.mediafire.com/file/5fro3j0hjjw9x4a/traduccion_ts-client.rar/file?dkey=test&amp;r=1' id='downloadButton'>";
        if (!SpanishDownloadLink.find(next).endsWith("?dkey=test&r=1")) throw new AssertionError();
        rejects("<a id='downloadButton' href='http://download1514.mediafire.com/test'>");
        rejects("<a id='downloadButton' href='https://evil.example/test'>");
        rejects("<a id='downloadButton' href='https://www.mediafire.com/file/other/file'>");
        rejects("<a id='downloadButton' href='https://download1514.mediafire.com.evil.example/test'>");
        rejects("<a id='downloadButton' href='https://user@download1514.mediafire.com/test'>");
        rejects("<a href='#'>Missing download</a>");
        if(args.length>0) System.out.println(SpanishDownloadLink.find(java.nio.file.Files.readString(java.nio.file.Path.of(args[0]))));
        System.out.println("Spanish download-link tests passed");
    }
}
