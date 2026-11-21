package com.opents.game;

import java.io.*;
import java.nio.file.*;
import java.security.*;
import java.util.*;
import java.util.zip.CRC32;
import org.tukaani.xz.*;

public class FreewareExtractorTest {
    private static void require(boolean value, String message) {
        if (!value) throw new AssertionError(message);
    }
    private static String hash(byte[] bytes) throws Exception {
        StringBuilder text = new StringBuilder();
        for (byte value : MessageDigest.getInstance("SHA-256").digest(bytes))
            text.append(String.format(Locale.ROOT, "%02x", value & 255));
        return text.toString();
    }
    private static void rejects(File input, File stage, FreewarePackage pack, FreewareExtractor.Progress progress) throws Exception {
        try { FreewareExtractor.extract(input, stage, pack, progress); throw new AssertionError("Expected rejection"); }
        catch (IOException expected) { }
    }
    public static void main(String[] args) throws Exception {
        Path root = Files.createTempDirectory("opents-freeware-test-");
        File stage = Files.createDirectory(root.resolve("stage")).toFile();
        File input = root.resolve("fixture.bin").toFile();
        byte[] first = "Synthetic game data for extraction checks".getBytes("UTF-8");
        byte[] second = "Second synthetic file".getBytes("UTF-8");
        byte[] prefix = "Skipped bytes".getBytes("UTF-8");
        ByteArrayOutputStream packed = new ByteArrayOutputStream();
        LZMA2Options options = new LZMA2Options(); options.setDictSize(1 << 20);
        try (LZMAOutputStream output = new LZMAOutputStream(packed, options, true)) {
            output.write(prefix); output.write(first); output.write(second);
        }
        byte[] container = new byte[17 + packed.size()];
        System.arraycopy(packed.toByteArray(), 0, container, 17, packed.size());
        Files.write(input.toPath(), container);
        CRC32 crc1 = new CRC32(); crc1.update(first);
        CRC32 crc2 = new CRC32(); crc2.update(second);
        FreewarePackage.Entry one = new FreewarePackage.Entry("TIBSUN.MIX", prefix.length, first.length, crc1.getValue());
        FreewarePackage.Entry two = new FreewarePackage.Entry("SCORES.MIX", prefix.length + first.length, second.length, crc2.getValue());
        FreewarePackage pack = new FreewarePackage("fixture.bin", "Synthetic fixture", "https://example.invalid/fixture", container.length,
            hash(container), 17, packed.size(), 93, 1 << 20, new FreewarePackage.Entry[]{one, two});
        FreewareExtractor.extract(input, stage, pack, message -> {});
        require(Arrays.equals(first, Files.readAllBytes(new File(stage, "TIBSUN.MIX").toPath())), "first file differs");
        require(Arrays.equals(second, Files.readAllBytes(new File(stage, "SCORES.MIX").toPath())), "second file differs");
        byte[] changed = container.clone(); changed[changed.length - 1] ^= 1; Files.write(input.toPath(), changed);
        rejects(input, stage, pack, message -> {});
        require(Arrays.equals(first, Files.readAllBytes(new File(stage, "TIBSUN.MIX").toPath())), "verification replaced existing file");
        Files.write(input.toPath(), Arrays.copyOf(container, container.length - 1));
        rejects(input, stage, pack, message -> {});
        Files.write(input.toPath(), container);
        FreewarePackage wrongCrc = new FreewarePackage(pack.name, pack.label, pack.url, pack.bytes, pack.sha256,
            pack.streamOffset, pack.packedBytes, pack.properties, pack.dictionary,
            new FreewarePackage.Entry[]{new FreewarePackage.Entry("TIBSUN.MIX", one.offset, one.bytes, one.crc ^ 1)});
        rejects(input, stage, wrongCrc, message -> {});
        require(Arrays.equals(first, Files.readAllBytes(new File(stage, "TIBSUN.MIX").toPath())), "CRC rejection replaced existing file");
        FreewarePackage unsafe = new FreewarePackage(pack.name, pack.label, pack.url, pack.bytes, pack.sha256,
            pack.streamOffset, pack.packedBytes, pack.properties, pack.dictionary,
            new FreewarePackage.Entry[]{new FreewarePackage.Entry("SUN.INI", one.offset, one.bytes, one.crc)});
        rejects(input, stage, unsafe, message -> {});
        require(!new File(stage, "SUN.INI").exists(), "settings file created");
        rejects(input, stage, pack, message -> { throw new InterruptedIOException("Cancelled"); });
        require(Arrays.equals(first, Files.readAllBytes(new File(stage, "TIBSUN.MIX").toPath())), "cancellation replaced existing file");
        for (File file : stage.listFiles()) require(!file.getName().startsWith(".unpack-"), "temporary file leaked");
        try (java.util.stream.Stream<Path> paths = Files.walk(root)) {
            for (Path path : paths.sorted(Comparator.reverseOrder()).toArray(Path[]::new)) Files.delete(path);
        }
        System.out.println("PASS synthetic extraction, offsets, SHA-256, CRC, truncation, settings protection and cancellation");
    }
}
