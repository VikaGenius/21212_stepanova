package torrent;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Map;

import com.dampcake.bencode.*;


public class TorrentParser {
    private BencodeInputStream bInputStream = null;
    public Map<String, Object> info = null;

    TorrentParser(InputStream input) {
        bInputStream = new BencodeInputStream(input, StandardCharsets.ISO_8859_1);
        try {
            Map<String, Object> dataTorrentFile = bInputStream.readDictionary();
            @SuppressWarnings("unchecked")
            Map<String, Object> infoMap = (Map<String, Object>)dataTorrentFile.get("info");
            info = infoMap;
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
    
    byte[] GetHashInfo() throws FileNotFoundException {
        Bencode bencode = new Bencode(StandardCharsets.ISO_8859_1);
        byte[] infoInBytes = bencode.encode(info);
        byte[] hash = null;
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            hash = md.digest(infoInBytes);
        } catch (NoSuchAlgorithmException e) {
            System.err.println(e.getMessage());
        }
        return hash;
    }

    //получаем хэш кусочка самого файла
    byte[] GetHashPiece(File file, int lenPiece, int index) {
        byte[] hash = null;
        try (RandomAccessFile fileHandler = new RandomAccessFile(file, "r")) {
            byte[] piece = new byte[lenPiece];
            fileHandler.seek((long)index * (long)lenPiece);
            int readBytes = 0;
            if ((readBytes = fileHandler.read(piece)) < 0) {
                return new byte[20];
            }
            piece = Arrays.copyOfRange(piece, 0, readBytes);
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            hash = md.digest(piece);
        } catch (NoSuchAlgorithmException | IOException e) {
            System.err.println(e.getMessage());
        }
        return hash;
    }

    byte[] GetPieces() {
        return info.get("pieces").toString().getBytes(StandardCharsets.ISO_8859_1);
    }

    int GetAmountPieces() {
        return info.get("pieces").toString().getBytes(StandardCharsets.ISO_8859_1).length / 20;
    }

    long GetFileLen() {
        return Long.parseLong(info.get("length").toString());
    }

    int GetPieceLength() {
        return Integer.parseInt(info.get("piece length").toString());
    }
    
    String GetFileName() {
        return info.get("name").toString();
    }
}

