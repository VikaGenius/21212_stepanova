package torrent;

import java.nio.ByteBuffer;

public class Request {
    static int codeRequestMessage = 6;

    byte[] GetRequest(int index, int begin, int len) {
        ByteBuffer req = ByteBuffer.allocate(17);
        req.putInt(13);
        req.put((byte)codeRequestMessage);
        req.putInt(index);
        req.putInt(begin);
        req.putInt(len);
        return req.array();
    }

    int CheckRequest(byte[] request) {
        ByteBuffer buf = ByteBuffer.wrap(request);
        int index = buf.getInt(1);
        //int len = buf.getInt(13);
        return index;

    }

}
