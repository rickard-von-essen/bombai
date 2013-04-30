import java.util.HashMap;
import java.util.Map;

/**
 * A simple command is one not requiring any additional parameters.
 */
public enum SimpleCommand implements Command {
   MOVE_LEFT("left"),
   MOVE_RIGHT("right"),
   MOVE_UP("up"),
   MOVE_DOWN("down"),
   PASS("pass");

   private final String representation;

   private static final Map<String, SimpleCommand> fromRepresentationMap = new HashMap<String, SimpleCommand>();
   static {
      for(SimpleCommand command : SimpleCommand.values()) {
         fromRepresentationMap.put(command.getRepresentation(), command);
      }
   }
   
   SimpleCommand(String representation) {
      this.representation = representation;
   }
   
   public String getRepresentation() {
      return representation;
   }
   
   public static SimpleCommand fromRepresentation(String representation) {
      return fromRepresentationMap.get(representation);
   }
   
}
