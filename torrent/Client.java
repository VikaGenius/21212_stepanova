package torrent;

import torrent.App.Peer;

import java.net.*;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;
import java.util.Set;
import java.util.Iterator;

import java.io.*;

public class Client implements Runnable {

    Client(List<Peer> peers, String name) {
        servers = new ArrayList<>();
        for (Peer peer : peers) {
            servers.add(new Server(peer.ip, peer.port));
        }
        torrentFileName = name;
    }

    @Override
    public void run() {
        try {
            System.out.println("Client start working");
            torrentFile = new File(torrentFileName); 
            parser = new TorrentParser(new FileInputStream(torrentFile));
            reader = new Reader(); 

            //создаем файл, который хотим получить
            String fileName = parser.GetFileName();
            file = new File(fileName);
            file.createNewFile();

            Bitfield bf = new Bitfield();
            bitfield = bf.DoBitset(torrentFile, file);
            System.out.println(bitfield);

            amountOfPieces = parser.GetAmountPieces();

            while (!IsLoadingFinished()) {
                startLoading();
            }
            System.out.println("File downloaded");
            
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    private void startLoading() {
        try  (Selector selector = Selector.open()) {
            while (!IsLoadingFinished()) {
                Connection(selector);
                selector.select();
                
                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    Server currServer = (Server)key.attachment();
                    iterator.remove();

                    if (key.isConnectable()) {
                        SocketChannel channel = (SocketChannel) key.channel();
                        try {
                            if (channel.finishConnect()) {
                                currServer.setStatus(Status.InTouch);
                            } 
                        } catch (IOException e) {
                            key.cancel();
                            channel.close();
                            currServer.setStatus(Status.NotConnected);
                            continue;
                        }
                    }

                    if (currServer.status == Status.NotConnected) {
                        continue;
                    }

                    if (key.isReadable()) {
                        SocketChannel channel = (SocketChannel) key.channel();
                        try {
                            Read(currServer, channel);
                        } catch (IOException e) {
                            key.cancel();
                            channel.close();
                            currServer.setStatus(Status.NotConnected);
                            continue;
                        }
                    }

                    if (key.isWritable()) {
                        SocketChannel channel = (SocketChannel) key.channel();
                        try {
                            Write(currServer, channel);
                        } catch (IOException e) {
                            key.cancel();
                            channel.close();
                            currServer.setStatus(Status.NotConnected);
                            continue;
                        }
                    }
                }
            }

        } catch(IOException e) {
                System.err.println("Wait connection");
                return;
        } 
    }

    void Connection(Selector selector) throws IOException {
        for (Server server : servers) {
            if (server.status != Status.NotConnected) {
                continue;
            }
            SocketChannel channel = SocketChannel.open();
            channel.configureBlocking(false);
            channel.connect(new InetSocketAddress(server.getIP(), server.getPort()));
            channel.register(selector, SelectionKey.OP_CONNECT | SelectionKey.OP_READ | SelectionKey.OP_WRITE, server);
        }
    }

    private boolean IsLoadingFinished() {
        Bitfield bf = new Bitfield();
        bitfield = bf.DoBitset(torrentFile, file);
        return bitfield.nextClearBit(0) >= amountOfPieces;
    }

    static byte[] GetPeerId () {
        byte[] peerId = new byte[20];
        for (int i = 0; i < 20; i++) {
           peerId[i] = (byte)(i % 10);
        }
        return peerId;
    }

    void Write(Server server, SocketChannel channel) throws IOException {
         try {
            switch(server.getStatus()) {
                case NotConnected:
                    break;
                case InTouch:
                    SendHandshake(channel);
                    server.setStatus(Status.SalyamBrat);
                    break;
                case Have:
                    SendRequest(server, channel);
                    break;
                default: 
                    break;
            }
        } catch(IOException e) {
            throw new IOException(e);
        }
    }

    void Read(Server server, SocketChannel channel) throws IOException {
        try {
            switch (server.getStatus()) {
                case SalyamBrat:
                    RecvHandshake(server, channel);
                    server.setStatus(Status.AreDealing);
                    break;
                case AreDealing:
                    RecvBitfield(server, channel);
                    server.setStatus(Status.Have);
                    break;
                case Have:
                    RecvPiece(server, channel);
                        break;
                    default: 
                        break;
            }
        } catch (IOException e) {
            throw new IOException(e);
        }
    }

    void RecvHandshake(Server server, SocketChannel channel) throws IOException {
        byte[] hahandshakeByServer = reader.Read(channel, 68);
        HandshakeMessage handshake = new HandshakeMessage();
        if (handshake.GetTorrentFile(hahandshakeByServer) != null && handshake.CheckHandshake(hahandshakeByServer)) {
            server.setStatus(Status.AreDealing);
        }
    }

    void SendHandshake(SocketChannel channel) throws IOException {
        HandshakeMessage handshake = new HandshakeMessage();
        byte[] message = handshake.GetHandshakeMessage(parser.GetHashInfo(), GetPeerId());
        channel.write(ByteBuffer.wrap(message));
        System.out.println("Client send handshake =)");
    }

    void RecvBitfield(Server server, SocketChannel channel) throws IOException {
        byte[] bitfield = reader.ReadMessage(channel);
        BitSet bitfieldInBits = BitSet.valueOf(bitfield);
        BitSet bitsetByServer = bitfieldInBits.get(8, 8 + parser.GetAmountPieces());
        server.setBitfield(bitsetByServer);
        System.out.println("Client recived bitfield =)");
    }

    void SendRequest(Server server, SocketChannel channel) throws IOException {
        int index = bitfield.nextClearBit(0);  
        if (index >= amountOfPieces) {
            isLoadingFinished = true;
            return;
        }

        for (int i = index; i <= amountOfPieces; i = bitfield.nextClearBit(i + 1)) {
            if (server.getBitfield().get(i)) {
                Request req = new Request();
                byte[] request = req.GetRequest(i, i * parser.GetPieceLength(), parser.GetPieceLength());
                channel.write(ByteBuffer.wrap(request));
                bitfield.set(i);
                server.req = i;
                return;
            }
        }  
    }

    void RecvPiece(Server server, SocketChannel channel) throws IOException {
        byte[] message = reader.ReadMessage(channel);
        Piece pieceManager = new Piece();
        int piece = pieceManager.InsertPiece(message, file, parser.GetFileLen(), parser.GetAmountPieces());
        if (server.req == piece) {
            bitfield.set(piece);
        } else {
            bitfield.clear(server.req);
        }
        System.out.println("The client recived a one piece - " + piece);
    }
    
    private class Server {
        public Server (String ipAddr, int port1) {
            port = port1;
            ip = ipAddr;
        }

        public void setStatus(Status status1) {
            status = status1;
        }

        public Status getStatus() {
            return status;
        }

        public void setBitfield(BitSet bitField) {
            bitfield = bitField;
        }

        public BitSet getBitfield() {
            return bitfield;
        }

        public String getIP() {
            return ip;
        }

        public int getPort(){
            return port;
        }

        private int port;
        private String ip;
        private BitSet bitfield;
        private Status status = Status.NotConnected;
        int req = 0;
    }

    private BitSet bitfield = null;
    private List<Server> servers = null;
    File torrentFile;
    TorrentParser parser;
    Reader reader;
    File file;
    String torrentFileName;
    boolean isLoadingFinished = false;
    private int amountOfPieces = 0;
}

// Copyright idea by Yurik 
enum Status {
    NotConnected, //без связи
    InTouch, //на связи
    SalyamBrat, //жму руку
    AreDealing, //договорились
    Have //имеется
};
