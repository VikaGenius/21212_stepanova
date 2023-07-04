package torrent;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.BitSet;

public class Bitfield {
    public static final int BITFIELD_MESSAGE = 5;
    
    byte[] GetBitfield(int amountOfPieces, BitSet bitset) {
        ByteBuffer buffer = ByteBuffer.allocate((amountOfPieces + 7) / 8 + 4 + 1);
        buffer.putInt((amountOfPieces + 7) / 8 + 1);
        buffer.put((byte)BITFIELD_MESSAGE);
        buffer.put(bitset.toByteArray());
        return buffer.array();
    }

    BitSet DoBitset(File torrentFile, File file) {
        BitSet bitset = null;
        try (FileInputStream fileInputStream = new FileInputStream(torrentFile)) {
            TorrentParser parser = new TorrentParser(fileInputStream);
            int amountOfPieces = parser.GetAmountPieces();
            int lenPiece = parser.GetPieceLength();

            bitset = new BitSet(amountOfPieces);

            int hashLen = 20;
            ByteBuffer byteBuf = ByteBuffer.wrap(parser.GetPieces());
            byte[] onePieceInTorrent = null;
            
            for (int i = 0; i < amountOfPieces; i++) {
                onePieceInTorrent = new byte[hashLen];
                byteBuf.get(onePieceInTorrent, 0, hashLen);
                if (Arrays.equals(onePieceInTorrent, parser.GetHashPiece(file, lenPiece, i))) {
                    bitset.set(i);
                }
            }
            
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
        return bitset;
    }
    
}
