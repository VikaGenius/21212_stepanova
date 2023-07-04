package torrent;
// kitty go kitty go kitty go :}
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;

public class Piece {
    public static final int PIECE_MESSAGE = 7;

    byte[] GetPiece(int index, int length, File file) {
        byte[] piece = null;
        try {
            RandomAccessFile file2 = new RandomAccessFile(file, "r");
            piece = new byte[length + 9 + 4];
            ByteBuffer buf = ByteBuffer.wrap(piece);
            buf.putInt(length + 9);
            buf.put((byte)PIECE_MESSAGE);
            buf.putInt(index);
            buf.putInt(1);
            piece = buf.array();

            file2.seek((long)index * (long)length);
            file2.read(piece, 9 + 4, length);

            file2.close();
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }

        return piece;
    }

    int InsertPiece(byte[] piece, File file, long fileLen, int amountOfPieces) {
        ByteBuffer buf = ByteBuffer.wrap(piece);
        int len = piece.length - 9;
        int index = buf.getInt(1);
        try (RandomAccessFile file2 = new RandomAccessFile(file, "rw")) {
            file2.seek((long)index * (long)len);
            if (index == amountOfPieces - 1) {
                len -= (amountOfPieces * len - fileLen);
            }
            file2.write(piece, 9, len);
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
        return index;
    }
}
