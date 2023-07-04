package torrent;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class HandshakeMessage {
    //<pstrlen><pstr><reserved><info_hash><peer_id>
    byte[] GetHandshakeMessage(byte[] infoHash, byte[] peerId) {
        byte[] staticData = GetStaticData();
        ByteBuffer buf = ByteBuffer.allocate(lenStaticData + 40);
        buf.put(staticData);
        buf.put(infoHash);
        buf.put(peerId);
        return buf.array();
    }

    static byte[] GetStaticData() {
        String pstr = "BitTorrent protocol";
        byte[] pstrBytes = pstr.getBytes();
        int pstrlen = pstrBytes.length;
        final byte[] zero = {0, 0, 0, 0, 0, 0, 0, 0};

        ByteBuffer buf = ByteBuffer.allocate(1 + pstrlen + zero.length);
        buf.put((byte)pstrlen);
        buf.put(pstrBytes);
        buf.put(zero); 
        return buf.array();
    }

    boolean CheckHandshake(byte[] handshake) {
        return Arrays.equals(Arrays.copyOf(handshake, lenStaticData), GetStaticData());
    }
    
    File GetTorrentFile(byte[] handshake) {
        File folder = new File(System.getProperty("user.dir"));

        File[] files = folder.listFiles();
            for (File file: files) {
                if (file.isFile()) {
                    if (file.getName().endsWith(".torrent")) {
                        try {
                            TorrentParser parser = new TorrentParser(new FileInputStream(file));
                            if (Arrays.equals(parser.GetHashInfo(), Arrays.copyOfRange(handshake, lenStaticData, lenStaticData + 20))) {
                                return file;
                            }
                        } catch (FileNotFoundException e) {
                            throw new RuntimeException("Error: cannot open file .torrent");
                        }
                        
                    } 
                }
            }
        return null;
    }

    public static int FirstInt() {
        ByteBuffer buffff = ByteBuffer.wrap(GetStaticData());
        return buffff.getInt(0);
    }
    
    private int lenStaticData = GetStaticData().length;
}
