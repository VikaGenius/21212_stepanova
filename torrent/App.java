package torrent;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class App {
    public static void main(String[] args) {
        App app = new App();
        app.Start();
    }

    void Start() {
        try {
            ParseData();
            Client client = new Client(peers, torrentFileName);
            Thread clientThread = new Thread(client);
            Server server = new Server(serverPort);
            Thread serverThread = new Thread(server);
            clientThread.start();
            serverThread.start();
            clientThread.join();
            serverThread.join();
        } catch (InterruptedException e) {
                System.err.println(e.getMessage());
        }
    }

    void ParseData() {
        File file = new File("peers.txt");
        try (Scanner sc = new Scanner(file)) {
            torrentFileName = sc.nextLine();
            if (torrentFileName == null) {
                throw new RuntimeException();
            }
            serverPort = Integer.parseInt(sc.nextLine());
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                String[] lines = line.split(":");
                peers.add(new Peer(lines[0], Integer.parseInt(lines[1])));
            }
        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage());
        }
    }

    class Peer {
        String ip;
        int port;
        Peer (String ip, int port) {
            this.ip = ip;
            this.port = port;
        }
    }

    private int serverPort;
    private List<Peer> peers = new ArrayList<>();
    private String torrentFileName;

}
