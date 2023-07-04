package brainfuck;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Factory {
    public Factory() throws IOException {
        properties = new Properties();
        commandList = new HashMap<>();
        try (InputStream inputStream = ClassLoader.getSystemResourceAsStream("commands.properties")) {
            properties.load(inputStream);
        }
    }
    
    /** We get the class of the command we need to execute. If the class does not exist, but the command exists, we create a new instance. */
    public Command GetCommand(String name) {
        if (commandList.get(name) != null) {
            return commandList.get(name);
        } else {
            try { 
                Class<?> command = Class.forName(properties.getProperty(name));
                Command lego = (Command)command.getDeclaredConstructor().newInstance(); 
                //logger.info("Create new object");
                commandList.put(name, lego);
                return lego; 
            }
            catch (Exception e) {
                System.err.println(e.getMessage());
                return null;
            }
        }
    }

    private Properties properties;
    private Map<String, Command> commandList;
}
