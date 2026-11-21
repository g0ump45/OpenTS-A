package com.opents.game;
import java.io.*;
import java.nio.file.*;
import java.util.zip.*;
public class LocalizedZipTest {
    static void check(boolean value) { if (!value) throw new AssertionError(); }
    static void zip(Path path, String name, byte[] data) throws IOException {
        try (ZipOutputStream out = new ZipOutputStream(Files.newOutputStream(path))) {
            out.putNextEntry(new ZipEntry(name)); out.write(data); out.closeEntry();
        }
    }
    static FreewarePackage.Entry entry(String name, byte[] data) {
        CRC32 crc = new CRC32(); crc.update(data);
        return new FreewarePackage.Entry(name, 0, data.length, crc.getValue());
    }
    static void rejected(Path zip, File stage, FreewarePackage.Entry[] entries) throws Exception {
        try { LocalizedZip.extract(zip.toFile(), stage, entries, text -> {}); throw new AssertionError(); }
        catch (IOException expected) {}
    }
    public static void main(String[] args) throws Exception {
        Path root = Files.createTempDirectory("opents-language-zip");
        File stage = Files.createDirectory(root.resolve("stage")).toFile();
        Path source = root.resolve("fixture.zip"), target = stage.toPath().resolve("SPEECH01.MIX");
        byte[] data = "synthetic speech archive".getBytes("UTF-8");
        FreewarePackage.Entry good = entry("SPEECH01.MIX", data);
        zip(source, good.name, data);
        LocalizedZip.extract(source.toFile(), stage, new FreewarePackage.Entry[]{good}, text -> {});
        check(java.util.Arrays.equals(Files.readAllBytes(target), data));
        Files.writeString(target, "keep");
        rejected(source, stage, new FreewarePackage.Entry[]{new FreewarePackage.Entry(good.name, 0, good.bytes, good.crc ^ 1)});
        rejected(source, stage, new FreewarePackage.Entry[]{new FreewarePackage.Entry(good.name, 0, good.bytes + 1, good.crc)});
        rejected(source, stage, new FreewarePackage.Entry[]{good,good});
        zip(source, "../SPEECH01.MIX", data); rejected(source, stage, new FreewarePackage.Entry[]{good});
        zip(source, "GAME.EXE", data); rejected(source, stage, new FreewarePackage.Entry[]{good});
        zip(source, good.name, data);
        try { LocalizedZip.extract(source.toFile(), stage, new FreewarePackage.Entry[]{good}, text -> { throw new InterruptedIOException(); }); throw new AssertionError(); }
        catch (InterruptedIOException expected) {}
        check(Files.readString(target).equals("keep"));
        try (ZipOutputStream out = new ZipOutputStream(Files.newOutputStream(source))) {}
        rejected(source, stage, new FreewarePackage.Entry[]{good});
        check(Files.readString(target).equals("keep"));
        check(stage.listFiles().length == 1);
        System.out.println("LocalizedZipTest passed");
    }
}
