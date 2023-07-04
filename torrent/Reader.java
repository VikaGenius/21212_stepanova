package torrent;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Reader {
    public byte[] Read(SocketChannel channel, int amountOfBytes) throws IOException {
        ByteBuffer dataBuf = ByteBuffer.allocate(amountOfBytes);
        int bytesRead = 0;
        while (dataBuf.hasRemaining()) {
            bytesRead = channel.read(dataBuf);
        }
        if (bytesRead < 0) {
            throw new IOException("Socket in is closed");
        }
        return dataBuf.array();
    }

    public byte[] ReadMessage(SocketChannel channel) throws IOException {
        ByteBuffer buf = ByteBuffer.wrap(Read(channel, 4));
        int lenMessage = buf.getInt(0);
        return Read(channel, lenMessage);
    }

    public byte[] Readmessage(SocketChannel channel) throws IOException {
        ByteBuffer buf = ByteBuffer.wrap(Read(channel, 4));
        int lenMessage = buf.getInt(0);

        if (lenMessage == HandshakeMessage.FirstInt()) {
            ByteBuffer buffer = ByteBuffer.allocate(68);
            buffer.put(buf);
            int bytesRead = 0;
            while (buffer.hasRemaining()) {
                bytesRead = channel.read(buffer);
            }
            if (bytesRead < 0) {
                throw new IOException("Socket in is closed");
            }
            return buffer.array();
        }

        
        byte[] mess = Read(channel, lenMessage);
        return mess;
    }
}
