package torrent;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.BitSet;
import java.util.Iterator;
import java.util.Set;

public class Server implements Runnable {
    Server(int port1) {
        port = port1;
   }

   @Override
   public void run() {
        reader = new Reader();
        StartWorking();
   }

   void StartWorking() {
        try (Selector selector = Selector.open();
        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open()) {
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.bind(new InetSocketAddress(port));
            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT, SelectionKey.OP_READ);

            while (true) {
                selector.select();
                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while(iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    iterator.remove();

                    if (!key.isValid()) {
                        continue;
                    }
                    
                    if (key.isAcceptable()) {
                        try { ServerSocketChannel serverChannel = (ServerSocketChannel) key.channel();
                        SocketChannel clientChannel = serverChannel.accept();
                        clientChannel.configureBlocking(false);
                        clientChannel.register(selector, SelectionKey.OP_READ);
                        } catch (IOException e) {
                            System.out.println(e.getMessage());
                            key.cancel();
                        }
                    }
                    if (key.isReadable()) {
                        try { SocketChannel clientChannel = (SocketChannel)key.channel();
                        ReadandWrite(clientChannel);
                        } catch (IOException e) {
                            System.out.println(e.getMessage());
                            key.cancel();
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
   }

   static byte[] GetPeerId () {
      byte[] peerId = new byte[20];
      for (int i = 0; i < 20; i++) {
         peerId[i] = (byte)(i % 10);
      }
      return peerId;
   }

   File GetFile(String fileName) {
      File folder = new File(System.getProperty("user.dir"));
      File[] files = folder.listFiles();
      for (File file: files) {
         if (file.isFile()) {
            if (fileName.equals(file.getName())) {
               return file;
            }
         }
      }
      return null;
   }

   void ReadandWrite(SocketChannel channel) throws IOException {
        byte[] message = reader.Readmessage(channel);
        HandshakeMessage handleHandshake = new HandshakeMessage();
        if (handleHandshake.CheckHandshake(message)) {
            System.out.println("Recived handshake");
            SendHandshakeAndBitfield(handleHandshake, message, channel);
        } else {
            Request request = new Request();
            int index = request.CheckRequest(message);
            SendPiece(channel, index);
            System.out.println("Server sent piece!");
        }
   }

   void SendHandshakeAndBitfield(HandshakeMessage handleHandshake, byte[] message, SocketChannel channel) throws IOException {
        File torrentFile = handleHandshake.GetTorrentFile(message);
        FileInputStream fileInputStream = new FileInputStream(torrentFile);
        TorrentParser parser = new TorrentParser(fileInputStream);
        pieceLen = parser.GetPieceLength();

        int amountOfPieces = parser.GetAmountPieces();
        String fileName = parser.GetFileName();
        file = GetFile(fileName);

        byte[] handshakeByServer = handleHandshake.GetHandshakeMessage(parser.GetHashInfo(), GetPeerId());
        channel.write(ByteBuffer.wrap(handshakeByServer));
        System.out.println("Server send handshake =)");

        Bitfield bf = new Bitfield();
        BitSet bitset = bf.DoBitset(torrentFile, file);
        byte[] bitfieldMessage = bf.GetBitfield(amountOfPieces, bitset);
        channel.write(ByteBuffer.wrap(bitfieldMessage));
        System.out.println("Server send bitfield");
   }

   void SendPiece(SocketChannel channel, int index) throws IOException {
        Piece pi = new Piece();
        byte[] piece = pi.GetPiece(index, pieceLen, file);
        int writeBytes = 0;
        int lenPiece = piece.length;
        while (writeBytes != lenPiece) {
            writeBytes += channel.write(ByteBuffer.wrap(piece, writeBytes, lenPiece - writeBytes));
        }
   }


    private int port;
    private Reader reader;
    private File file;
    private int pieceLen;
}
